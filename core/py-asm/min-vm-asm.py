"""
Author: Itiel Lopez - itiel@soyitiel.com
Created: 29/07/2021
Last updated: 06/08/2021
"""

""" 
NOTE:
    You'll probably notice that here we do some things that
    might be considered unncesary in python. Like, why don't 
    we just split the asm file into lines and then we scan it? 
    The thing is, this program is supoused to be exported to C 
    later. We're just using python first to speed development. 
    The goal is to make this assembler part of the VM program 
    available as a command (maybe?).

"""

from enum import Enum, IntEnum, unique
import sys

# a-Z

def ch_is_alph (ch):

    return ( 
        (ch >= 'a' and ch <= 'z') or 
        (ch >= 'A' and ch <= 'Z') 
    ) 

# 0-9 

def ch_is_dig (ch): 

    return ch >= '0' and ch <= '9' 

# 0-9 || a-F 

def ch_is_hex (ch): 
    
    return (
        ch_is_dig(ch) or 
        (ch >= 'a' and ch <= 'f') or 
        (ch >= 'A' and ch <= 'F')
    )

# 0-7

def ch_is_oct (ch):
    
    return ch >= '0' and ch <= '7'

class Token:

    @unique
    class Types (Enum):

        FILE_START = 0
        NAME       = 1
        SIGN       = 2
        NUMBER     = 3
        STRING     = 4
        CHAR       = 5
        COMMENT    = 6
        LINE_BREAK = 7
        FILE_END   = 8

    def __init__ (self, tk_row, tk_col, tk_type, tk_str):

        # TODO: Add char idx and str length

        self.row  = tk_row
        self.col  = tk_col
        self.type = tk_type
        self.str  = tk_str

    def __str__ (self):

        return (
            f'<Token row: {self.row},\tcol: {self.col},\t' 
            f'type: {self.type},\tstr: {repr(self.str)}>'
        )

class Tokenizer:

    @unique 
    class States (Enum):

        START   = 0
        NAME    = 1
        NUMBER  = 2
        OCT_NUM = 3
        HEX_NUM = 4
        SIGN    = 5
        STRING  = 6
        STR_ESC = 7
        CHAR    = 8
        COMMENT = 9

    def _set_data (self, file_name, file_txt):

        if file_name != None:

            self.set_file_name(file_name)

        elif file_txt != None:

            self.set_file_txt(file_txt)

    def set_file_name (self, file_name, load = True):

        if not isinstance(file_name, str):

            raise Exception(
                '\n  Tokenizer.set_file_name():\n'
                '    Argument should be a string'
            )

        self._file_name = file_name
        self._file_txt = None

        if load:        

            with open(file_name, 'r') as asm_file:

                self.set_file_txt(asm_file.read())
            

    def set_file_txt (self, file_txt):

        if not isinstance(file_txt, str):

            raise Exception(
                '\n  Tokenizer.set_file_txt():\n'
                '    Argument should be a string'
            )

        self._file_txt = file_txt

    def __init__ (self, file_name = None, file_txt = None):
        
        self._file_name = None
        self._file_txt  = None

        self._set_data(file_name, file_txt)
        
    def _tokenize_error (self, msg, row, col):

        file_name = (
            repr(self._file_name) if 
            self._file_name != None else 
            '<file>'
        )
        extr  = self._file_txt.split('\n')[row]
        extr  = extr.replace('\t', ' ')
        arrow = (' ' * col) + '^'

        error_msg = (
            f'\n  Error in {file_name} @ '
            f'(row: {row + 1}, col: {col + 1})\n'
            f'    {msg}\n'
            f'      {extr}\n'
            f'      {arrow}'
        )

        raise Exception(error_msg)

    def tokenize (self, file_name = None, file_txt = None):

        self._set_data(file_name, file_txt)

        if self._file_txt == None:

            raise Exception(
                '\n  Tokenizer.tokenize():\n'
                '    No file name or file text was provided.\n'
                '    Try using:\n'
                '      Tokenizer.set_file_name()\n'
                '      Tokenizer.set_file_txt()'
            )
        
        saved_ch    = None
        saved_state = None
        saved_type  = None
        saved_int   = None
        on_sep      = False
        on_break    = False
        lead_zero   = False
        esc_char    = False

        tk_row  = int()
        tk_col  = int()
        tk_type = None
        tk_str  = str()

        tk_tps  = Token.Types
        tkr_sts = Tokenizer.States 
        
        state = tkr_sts.START
        col   = -1

        # Start of file

        yield Token(None, None, tk_tps.FILE_START, None)

        for i, ch in enumerate(self._file_txt):

            col += 1

            if ch == '\n':

                saved_state = tkr_sts.START
                saved_int   = col
                on_break    = True
                on_sep      = True

            if state != tkr_sts.STRING:

                if ch in ' \t':
                    
                    saved_state = tkr_sts.START
                    on_sep      = True

                elif ch in '+-':

                    if state == tkr_sts.SIGN:
                    
                        yield Token(
                            tk_row, saved_int, tk_type, tk_str)
                    
                    saved_state = tkr_sts.SIGN
                    saved_type  = tk_tps.SIGN
                    saved_int   = col
                    on_sep      = True


                elif ch == '"':
                    
                    saved_state = tkr_sts.STRING
                    saved_type  = tk_tps.STRING
                    tk_col      = col
                    on_sep      = True

                elif ch == "'":
                    
                    saved_state = tkr_sts.CHAR
                    saved_type  = tk_tps.CHAR
                    tk_col      = col
                    on_sep      = True

                elif ch == ';':
                    
                    saved_state = tkr_sts.COMMENT
                    saved_type  = tk_tps.COMMENT
                    tk_col      = col
                    on_sep      = True

            # First iteration or after space or tab

            if state == tkr_sts.START:

                if on_sep:

                    on_sep = False

                    state   = saved_state
                    tk_type = saved_type
                    tk_str  = ch

                    if on_break:

                        on_break = False

                        yield Token(
                            tk_row, saved_int, tk_tps.LINE_BREAK, None)

                        tk_row += 1
                        col    = -1

                    continue
                
                tk_str = str()
                
                if ch_is_alph(ch):

                    state   = tkr_sts.NAME
                    tk_col  = col
                    tk_type = tk_tps.NAME
                    tk_str  = ch
                    
                    continue

                if ch_is_dig(ch):

                    state   = tkr_sts.NUMBER
                    tk_col  = col
                    tk_type = tk_tps.NUMBER
                    tk_str  = ch

                    if ch == '0':
                        lead_zero = True
                    
                    continue

                self._tokenize_error('Invalid syntax', tk_row, col)

            # Instruction names
            # (maybe booleans also)

            elif state == tkr_sts.NAME:

                if on_sep:

                    on_sep = False

                    yield Token(tk_row, tk_col, tk_type, tk_str)

                    state   = saved_state
                    tk_type = saved_type
                    tk_str  = ch
                    
                    if on_break:

                        on_break = False

                        yield Token(
                            tk_row, saved_int, tk_tps.LINE_BREAK, None)

                        tk_row += 1
                        col    = -1

                    continue

                # Allow alphanumeric names as long 
                # as the first character is a-Z

                if ch_is_alph(ch) or ch_is_dig(ch):

                    tk_str += ch

                    continue

                self._tokenize_error('Invalid name syntax', tk_row, col)

            # Numbers
            # Only decimal, hex and octal integers
            # At the moment, no float or E notation

            elif state == tkr_sts.NUMBER:

                if on_sep:

                    on_sep = False

                    # TODO: Disallow leading-zero decimal integers.
                    #       Except for zero ("0"), of course

                    lead_zero = False 

                    yield Token(tk_row, tk_col, tk_type, tk_str)
                    
                    state   = saved_state
                    tk_type = saved_type
                    tk_str  = ch

                    if on_break:

                        on_break = False

                        yield Token(
                            tk_row, saved_int, tk_tps.LINE_BREAK, None)

                        tk_row += 1
                        col    = -1

                    continue

                if ch_is_dig(ch):

                    tk_str += ch

                    continue

                if (col - tk_col == 1) and lead_zero:

                    if ch in ['o', 'O']:

                        state  = tkr_sts.OCT_NUM
                        tk_str += ch
                        saved_ch = ch

                        continue

                    if ch in ['x', 'X']:

                        state  = tkr_sts.HEX_NUM
                        tk_str += ch
                        saved_ch = ch

                        continue

                self._tokenize_error(
                    'Invalid number syntax', tk_row, col)

            # Octal number

            elif state == tkr_sts.OCT_NUM:
        
                if on_sep:

                    on_sep = False

                    if not ch_is_oct(saved_ch):

                        self._tokenize_error(
                            'Invalid octal syntax', tk_row, col)

                    lead_zero = False 

                    yield Token(tk_row, tk_col, tk_type, tk_str)
                    
                    state   = saved_state
                    tk_type = saved_type
                    tk_str  = ch

                    if on_break:

                        on_break = False

                        yield Token(
                            tk_row, saved_int, tk_tps.LINE_BREAK, None)

                        tk_row += 1
                        col    = -1

                    continue

                if ch_is_oct(ch):

                    tk_str += ch
                    saved_ch = ch

                    continue

                self._tokenize_error('Invalid octal syntax', tk_row, col)

            # Hexadecimal number

            elif state == tkr_sts.HEX_NUM:
                
                if on_sep:

                    on_sep = False

                    if not ch_is_hex(saved_ch):

                        self._tokenize_error(
                            'Invalid hexadecimal syntax', 
                            tk_row, col
                        )

                    lead_zero = False 

                    yield Token(tk_row, tk_col, tk_type, tk_str)
                    
                    state   = saved_state
                    tk_type = saved_type
                    tk_str  = ch

                    if on_break:

                        on_break = False

                        yield Token(
                            tk_row, saved_int, tk_tps.LINE_BREAK, None)

                        tk_row += 1
                        col    = -1

                    continue

                if ch_is_hex(ch):

                    tk_str += ch
                    saved_ch = ch

                    continue

                self._tokenize_error(
                    'Invalid hexadecimal syntax', tk_row, col)

            # Sign (+-)

            elif state == tkr_sts.SIGN:

                # Here would go other single-char 
                # tokens like ()*$#

                if saved_state != tkr_sts.SIGN:
                    
                    yield Token(tk_row, saved_int, tk_type, tk_str)

                state   = saved_state
                tk_type = saved_type
                tk_str  = ch
                
                if on_break:

                    on_break = False

                    yield Token(
                        tk_row, saved_int, tk_tps.LINE_BREAK, None)

                    tk_row += 1
                    col    = -1

                continue

            # String (starts with ")

            # TODO: It has trouble scanning empty strings ("") 
            #       correctly. Rectify that.

            elif state == tkr_sts.STRING:

                if on_break:

                    self._tokenize_error(
                        'Line break in string literal', 
                        tk_row, col)

                if ch == "\\":

                    esc_char = True
                    continue

                if esc_char:

                    esc_char = False

                    if ch == '\\':
                        tk_str += '\\'
                    elif ch == '"':
                        tk_str += '"'
                    elif ch == "'":
                        tk_str += "'"
                    elif ch == 'n':
                        tk_str += '\n'
                    elif ch == 'r':
                        tk_str += '\r'
                    elif ch == 't':
                        tk_str += '\t'
                    elif ch == 'b':
                        tk_str += '\b'
                    elif ch == 'f':
                        tk_str += '\f'

                    # TODO: Allow for hex and octal rep char
                    
                    else:
                        tk_str += '\\' + ch


                    continue

                else:

                    if col - tk_col == 1:
                    
                        tk_str = ch
                    
                    elif ch != '"':

                        tk_str += ch

                if ch == '"':

                    yield Token(tk_row, tk_col, tk_type, tk_str)

                    state = tkr_sts.START

                    continue

            # Character (starts with ')

            elif state == tkr_sts.CHAR:

                # TODO: Develop this part, duh'

                pass

            elif state == tkr_sts.COMMENT:

                if on_break:

                    on_sep   = False
                    on_break = False

                    yield Token(tk_row, tk_col, tk_type, tk_str)
                
                    yield Token(
                        tk_row, saved_int, tk_tps.LINE_BREAK, None)

                    tk_row += 1
                    col    = -1

                    state   = saved_state
                    tk_type = saved_type

                    continue

                tk_str += ch

        # End of file

        yield Token(None, None, tk_tps.FILE_END, None)

class Parser:

    def __init__ (self, file_name = None, file_txt = None):
        
        self._file_name = None
        self._file_txt  = None
        self.tokens     = None

        self._set_data(file_name, file_txt)

    def _set_data (self, file_name, file_txt):

        if file_name != None:

            self.set_file_name(file_name)

        elif file_txt != None:

            self.set_file_txt(file_txt)

    def set_file_name (self, file_name, load = True):

        if not isinstance(file_name, str):

            raise Exception(
                '\n  Parser.set_file_name():\n'
                '    Argument should be a string'
            )

        self._file_txt = None
        self._file_name = file_name

        if load:

            with open(file_name, 'r') as asm_file:

                self.set_file_txt(asm_file.read())
            

    def set_file_txt (self, file_txt):

        if not isinstance(file_txt, str):

            raise Exception(
                '\n  Parser.set_file_txt():\n'
                '    Argument should be a string'
            )

        self._file_txt = file_txt

    def parse (self, file_name = None, file_txt = None):

        self._set_data(file_name, file_txt)
        
        if self._file_txt == None:

            raise Exception(
                '\n  Parser.parse():\n'
                '    No file name or file text was provided.\n'
                '    Try using:\n'
                '      Parser.set_file_name()\n'
                '      Parser.set_file_txt()'
            )

        # Tokenize all the lines and 
        # store them in a list

        tokenizer = Tokenizer()

        tokenizer.set_file_name(self._file_name, load = False)
        tokenizer.set_file_txt(self._file_txt)

        self.tokens = list()

        for token in tokenizer.tokenize():
            
            print(token)

            self.tokens.append(token)

def main ():

    args = sys.argv[1:]

    file_name = str(args[0])

    # Way No. 1

    # with open(file_name, 'r') as asm_file:
    #     parser = Parser()
    #     parser.set_file_txt(asm_file.read())
    #     parser.parse()

    # Way No. 2

    # with open(file_name, 'r') as asm_file:
    #     parser = Parser(file_txt = asm_file.read())
    #     parser.parse()

    # Way No. 3

    # with open(file_name, 'r') as asm_file:
    #     parser = Parser()
    #     parser.parse(file_txt = asm_file.read())

    # Way No. 4
        
    # parser = Parser()
    # parser.set_file_name(file_name)
    # parser.parse()

    # Way No. 5
        
    # parser = Parser(file_name = file_name)
    # parser.parse()

    # Way No. 6
        
    # parser = Parser()
    # parser.parse(file_name = file_name)

    # Way No. 7
        
    parser = Parser(file_name)
    parser.parse()


if __name__ == '__main__':
    main()