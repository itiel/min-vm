/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#ifndef _ASM_H_
#define _ASM_H_

/* -- Includes -- */

#include <stdio.h>

#include <util/fwn.h>
#include <util/err.h>
#include <util/choc.h>

/* -- Defines -- */

#define TRUE  1
#define FALSE 0

// space, tab, dollar sign, plus minus, and equals signs, 
// single and double quotes, colon and semicolon

#define SEPCHARSET (" \t\n\r$+-=\"':;")

// Character validation macros

// ch_is_alph      : a-Z
// ch_is_dig       : 0-9
// ch_is_alphnum   : a-Z || 0-9
// ch_is_name_lead : _ || a-Z 
// ch_is_name      : _ || a-Z || 0-9
// ch_is_bin       : 0 || 1
// ch_is_oct       : 0-7
// ch_is_hex       : 0-9 || a-F 
// ch_is_sep       : ch in SEPCHARSET

#define      ch_is_alph(_ch) \
    ((_ch >= 'a' && _ch <= 'z') || \
    (_ch >= 'A' && _ch <= 'Z')) 
#define       ch_is_dig(_ch) \
    (_ch >= '0' && _ch <= '9' )
#define   ch_is_alphnum(_ch) \
    (ch_is_alph(_ch) || ch_is_dig(_ch))
#define ch_is_name_lead(_ch) \
    (_ch == '_' || ch_is_alph(_ch))
#define      ch_is_name(_ch) \
    (_ch == '_' || ch_is_alphnum(_ch))
#define       ch_is_bin(_ch) \
    (_ch == '0' || _ch == '1')
#define       ch_is_oct(_ch) \
    (_ch >= '0' && _ch <= '7')
#define       ch_is_hex(_ch) \
    (ch_is_dig(_ch) || \
    (_ch >= 'a' && _ch <= 'f') || \
    (_ch >= 'A' && _ch <= 'F'))
#define       ch_is_sep(_ch) \
    char_occur(_ch, SEPCHARSET)

// These next 2 are to be used by mvm_asm_token_new() 

// Check if we have enough space in token_list

#define _toklst_nospace(_tknzr) \
    (_tknzr->parser->token_list_len + 1 > _tknzr->parser->token_list_size)

// _toklst_next() increments 1 to token_list_len

#define _toklst_next(_tknzr) \
    (&(_tknzr->parser->token_list[_tknzr->parser->token_list_len++]))

// To be used in mvm_asm_tokenize()
// _txtch_next() increments 1 to ch_idx

#define _txtch_next(_tknzr) \
    (_tknzr->parser->file_txt[++_tknzr->data.ch_idx])

/* -- Types & Enums -- */

typedef struct mvm_asm_tokenizer_t mvm_asm_tokenizer_t;
typedef struct mvm_asm_parser_t mvm_asm_parser_t;

// Token types

typedef enum {

    MVM_ATT_START,   // file-start
    MVM_ATT_NAME,    // instruction, variable or tag name
                     // maybe even booleans (true & false)
    MVM_ATT_NUMBER,  // decimal, no float or e-notation
    MVM_ATT_NUM_BIN, // binary number
    MVM_ATT_NUM_OCT, // octal number
    MVM_ATT_NUM_HEX, // hexadecimal number
    MVM_ATT_SIGN,    // plus, minus and equals signs (+-=)
    MVM_ATT_STRING,  // double quoted string literal
    MVM_ATT_CHAR,    // single quoted char literal
    MVM_ATT_COMMENT, // semicolon leading comment
    MVM_ATT_BREAK,   // line break (\n)
    MVM_ATT_END,     // file-end

} mvm_asm_token_types_t;

typedef struct mvm_asm_token_t {

    mvm_asm_tokenizer_t * tokenizer;
    i64                 start;
    i64                 row;
    i64                 col;
    i64                 len;
    i8                  type;

} mvm_asm_token_t;

// This enum describes Tokenizer and Parser elements 

typedef enum {

    // Don't change this order 

    MVM_AES_END,
    MVM_AES_INIT,
    MVM_AES_IN_USE,

} mvm_asm_elm_status_t;

// Tokenizer

typedef enum {

    MVM_ATS_BLANK,   // space or tab
    MVM_ATS_NAME,    // instruction, variable or tag name
                     // maybe even booleans (true & false)
    MVM_ATS_NUMBER,  // decimal, no float or e notation
    MVM_ATS_NUM_BIN, // binary number
    MVM_ATS_NUM_OCT, // octal number
    MVM_ATS_NUM_HEX, // hexadecimal number
    MVM_ATS_STRING,  // double quoted string literal
    MVM_ATS_CHAR,    // single quoted char literal
    MVM_ATS_COMMENT, // semicolon leading comment

} mvm_asm_tokenizer_state_t;

typedef struct mvm_asm_tokenizer_data_t {

    i8  cur_state;
    i64 last_break;
    i64 ch_idx;
    i64 cur_col;
    i64 cur_row;
    i64 tok_start;
    i64 tok_col;
    i8  tok_type;

} mvm_asm_tokenizer_data_t;

typedef struct mvm_asm_tokenizer_t {

    mvm_asm_parser_t         * parser;
    mvm_asm_tokenizer_data_t data;
    i8                       status;

} mvm_asm_tokenizer_t;

// Parser

typedef struct mvm_asm_parser_t {
 
    i8              * file_txt; 
    i64             file_txt_len;
    i8              * file_name; 
    mvm_asm_token_t * token_list; 
    i64             token_list_len;
    i64             token_list_size;
    i8              status;

} mvm_asm_parser_t;

/* -- Functions -- */

// TODO: Do declarations first, then definitions

// Token methods

i8 mvm_asm_token_new (mvm_asm_tokenizer_t * tokenizer)
{

    mvm_asm_token_t * new_token;

    if (_toklst_nospace(tokenizer)) {
 
        put_error_method( 
            "mvm_asm_token_new", 
            "Token list size needed exceeds actual size (%ld).", 
            tokenizer->parser->token_list_size
        );

        return 0;

    }

    new_token = _toklst_next(tokenizer);

    new_token->tokenizer = tokenizer;
    new_token->start     = tokenizer->data.tok_start;
    new_token->row       = tokenizer->data.cur_row;
    new_token->col       = tokenizer->data.tok_col;
    new_token->len       = tokenizer->data.ch_idx - \
                           tokenizer->data.tok_start;
    new_token->type      = tokenizer->data.tok_type;

    return 1;

}

i8 * mvm_asm_token_typename (i8 tok_type) {

    switch (tok_type) { 
 
        case MVM_ATT_START:   return "START";
        case MVM_ATT_NAME:    return "NAME";
        case MVM_ATT_NUMBER:  return "NUMBER";
        case MVM_ATT_NUM_BIN: return "BINARY";
        case MVM_ATT_NUM_OCT: return "OCTAL";
        case MVM_ATT_NUM_HEX: return "HEXA";
        case MVM_ATT_SIGN:    return "SIGN";
        case MVM_ATT_STRING:  return "STRING";
        case MVM_ATT_CHAR:    return "CHAR";
        case MVM_ATT_COMMENT: return "COMMENT";
        case MVM_ATT_BREAK:   return "BREAK";
        case MVM_ATT_END:     return "END";
        default:              return "N/A";

    }

}

i8 mvm_asm_token_show (mvm_asm_token_t * token) {

    printf(
        "<Token row: %ld\tcol: %ld\t" \
        "start: %ld\tlen: %ld\ttype: %s",
        token->row, token->col, 
        token->start, token->len,
        mvm_asm_token_typename(token->type)
    );

    // TODO: Show the string of the token
    //       Add a token reader

    if (token->type != MVM_ATT_START &&
        token->type != MVM_ATT_END &&
        token->type != MVM_ATT_BREAK) {
        
        printf("\tstr: ");

        for (int i = 0; i < token->len; ++i) {
        
            putchar(
                token->tokenizer->parser->file_txt[
                    token->start + i            
                ]
            );
        
        }

    }

    printf(" >\n");

    return 1;

}

// Tokenizer methods

i8 mvm_asm_tokenizer_init (
    mvm_asm_tokenizer_t * tokenizer, 
    mvm_asm_parser_t    * parser) 
{ 

    if (!tokenizer) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Tokenizer pointer should not be NULL."
        );

        return 0;
    }

    if (!parser) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Parser pointer should not be NULL."
        );

        return 0;
    }

    if (parser->status != MVM_AES_INIT) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Parser element needs to be initialized."
        );
 
        return 0;
    }

    parser->status = MVM_AES_IN_USE;

    tokenizer->parser = parser;
    tokenizer->status = MVM_AES_INIT;

    // Loop variables

    tokenizer->data.cur_state  = MVM_ATS_BLANK;
    tokenizer->data.last_break = 0;
    tokenizer->data.ch_idx     = -1;
    tokenizer->data.cur_col    = -1;
    tokenizer->data.cur_row    = 0;

    // Token variables

    tokenizer->data.tok_start = 0;
    tokenizer->data.tok_col   = 0;
    tokenizer->data.tok_type  = MVM_ATT_START;

    return 1;

}

i8 mvm_asm_tokenize_error (
    mvm_asm_tokenizer_t * tokenizer, 
    i8                  * reason) 
{ 

    eprintf(
        "In file %s\n" \
        "Error @ (%ld:%ld):\n" \
        "  %s\n",
        tokenizer->parser->file_name,
        tokenizer->data.cur_row + 1, 
        tokenizer->data.cur_col + 1,
        reason
    );
 
    // Show line of code and point to 
    // troubling character with an arrow

    // FIXME: Shows more than it should
    //        Arrow isn't on place

    i64 line_start;
    i64 ch_idx;
    i64 i;
    i8  ch;

    line_start = tokenizer->data.last_break;

    ch_idx = tokenizer->data.ch_idx - line_start + 1;

    // Code line
 
    eprintf("    "); 

    for (i = 0; i < ch_idx; ++i) {

        ch = tokenizer->parser->file_txt[line_start + i];
 
        eputchar(ch == '\t' ? ' ' : ch);
 
    }

    eprintf("\n");

    // Arrow
 
    eprintf("    ");

    ch_idx -= 1;

    for (i = 0; i < ch_idx; ++i) {

        eputchar(' ');
 
    }

    eprintf("^\n");

    return 0;

}

i8 mvm_asm_tokenize (mvm_asm_tokenizer_t * tokenizer) {

    i8 ch;
 
    i8  on_esc;    // Escape char in string or char literal
    i8  lead_zero; // Number literals starting with '0'
    i64 saved_val; // Multi-purpose val

    // Check if initialized

    if (tokenizer->status != MVM_AES_INIT) {

        put_error_method( 
            "mvm_asm_tokenize", 
            "Tokenizer element needs to be initialized."
        );
 
        return 0;
    }

    tokenizer->status = MVM_AES_IN_USE;

    // Start of process

    on_esc    = FALSE;
    lead_zero = FALSE;
    saved_val = 0;

    // Append file-start token before scanning

    if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

    while (ch = _txtch_next(tokenizer)) {

        tokenizer->data.cur_col++;

        // GOTO: Re-eval char but with diff state

        redo_char: 

        switch (tokenizer->data.cur_state) {

        // Just starting or after on a separator char

        // TODO: Implement scanning labels starting 
        //       with '.' and var names starting 
        //       with '$' 

        case MVM_ATS_BLANK:

            switch (ch) {

            case ' ': case '\t': case '\r':

                continue;

            case '\n':

                tokenizer->data.tok_type  = MVM_ATT_BREAK;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.last_break = tokenizer->data.ch_idx;
 
                tokenizer->data.cur_col = -1;
                tokenizer->data.cur_row += 1;

                continue;

            case '+': case '-': case '=': case ':':

                tokenizer->data.tok_type  = MVM_ATT_SIGN;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                continue;

            case '"':

                tokenizer->data.cur_state = MVM_ATS_STRING;

                tokenizer->data.tok_type  = MVM_ATT_STRING;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            case '\'':

                tokenizer->data.cur_state = MVM_ATS_CHAR;

                tokenizer->data.tok_type  = MVM_ATT_CHAR;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                saved_val = 1;

                continue;

            case ';':

                tokenizer->data.cur_state = MVM_ATS_COMMENT;

                tokenizer->data.tok_type  = MVM_ATT_COMMENT;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            }

            if (ch_is_name_lead(ch)) {

                tokenizer->data.cur_state = MVM_ATS_NAME;

                tokenizer->data.tok_type  = MVM_ATT_NAME;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            }

            if (ch_is_dig(ch)) {

                tokenizer->data.cur_state = MVM_ATS_NUMBER;

                tokenizer->data.tok_type  = MVM_ATT_NUMBER;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (ch == '0') lead_zero = TRUE;

                saved_val = 1;

                continue;

            }

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid syntax"
            );

            return 0;

        case MVM_ATS_NAME:

            if (ch_is_sep(ch)) {

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                goto redo_char;

            }

            if (ch_is_name(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid name syntax"
            );

            return 0;

        case MVM_ATS_NUMBER:

            if (ch_is_sep(ch)) {

                // Only if it's more than 1 character

                if (!saved_val && lead_zero) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Ilegal zero-leading decimal"
                    );

                    return 0;
 
                }

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                saved_val = 0;

                goto redo_char;

            }

            // Only on second character

            if (saved_val) {
 
                saved_val = 0;

                if (lead_zero) {

                    if (ch == 'b' || ch == 'B') {

                        tokenizer->data.cur_state = MVM_ATS_NUM_BIN;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_BIN;

                        saved_val = 1;

                        continue;

                    }

                    if (ch == 'o' || ch == 'O') {

                        tokenizer->data.cur_state = MVM_ATS_NUM_OCT;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_OCT;

                        saved_val = 1;

                        continue;

                    }

                    if (ch == 'x' || ch == 'X') {

                        tokenizer->data.cur_state = MVM_ATS_NUM_HEX;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_HEX;

                        saved_val = 1;

                        continue;

                    }

                }
            }

            if (ch_is_dig(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid decimal syntax"
            );

            return 0;

        case MVM_ATS_NUM_BIN:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0b

                if (saved_val) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid binary syntax"
                    );

                    return 0;
 
                }

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                goto redo_char;

            }

            if (saved_val) saved_val = 0; 

            if (ch_is_bin(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid binary syntax"
            );

            return 0;

        case MVM_ATS_NUM_OCT:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0o

                if (saved_val) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid octal syntax"
                    );

                    return 0;
 
                }

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                goto redo_char;

            }

            if (saved_val) saved_val = 0; 

            if (ch_is_oct(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid octal syntax"
            );

            return 0;

        case MVM_ATS_NUM_HEX:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0x

                if (saved_val) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid hexadecimal syntax"
                    );

                    return 0;
 
                }

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                goto redo_char;

            }

            if (saved_val) saved_val = 0; 

            if (ch_is_hex(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid hexadecimal syntax"
            );

            return 0;

        case MVM_ATS_STRING:

            if (ch == '\n') {

                mvm_asm_tokenize_error(
                    tokenizer,
                    "Ilegal line break in string literal"
                );

                return 0;

            }

            if (on_esc) {

                on_esc = FALSE;

                continue;

            }

            if (ch == '\\') {

                on_esc = TRUE;

                continue;

            }


            if (ch == '"') {

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                continue;

            }

            continue;

        case MVM_ATS_CHAR:

            // TODO: Combine character 
            //       and string statuses

            if (ch == '\n') {

                mvm_asm_tokenize_error(
                    tokenizer,
                    "Ilegal line break in character literal"
                );

                return 0;

            }

            if (on_esc) {

                on_esc = FALSE;

                continue;

            }

            if (ch == '\\') {

                on_esc = TRUE;

                continue;

            }

            if (ch == '\'') {

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                continue;

            }

            if (saved_val) {

                saved_val = 0;
                
                continue;

            }

            mvm_asm_tokenize_error(
                tokenizer,
                // "Invalid character literal syntax"
                "Multi-character character literal"
            );

            return 0;

        case MVM_ATS_COMMENT:

            if (ch == '\n') {

                if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

                tokenizer->data.cur_state = MVM_ATS_BLANK;

                goto redo_char;

            }

            continue;

        default:
 
            // TODO: Should this be like this?

            break;

        }

    }

    // TODO: Check for incomplete tokens

    // Append file-end token after finishing 

    tokenizer->data.tok_type = MVM_ATT_END;

    if (!mvm_asm_token_new(tokenizer)) goto new_tok_err;

    return 1;

    // GOTO: New token error
 
    new_tok_err: 

    put_error_method( 
        "mvm_asm_tokenize", 
        "Something unexpected happened while generating new token."
    );
 
    return 0;

}

// Parser methods

i8 mvm_asm_parser_init ( 
    mvm_asm_parser_t * parser, 
    i8               * file_txt, 
    i64              file_txt_len, 
    i8               * file_name, 
    mvm_asm_token_t  * token_list, 
    i64              token_list_size) 
{

    // Prob check for parent elem status here

    if (!parser) {
 
        put_error_method( 
            "mvm_asm_parser_init", 
            "Parser pointer should not be NULL."
        );

        return 0;

    }

    if (!file_txt) {
 
        put_error_method( 
            "mvm_asm_parser_init", 
            "Source string pointer should not be NULL."
        );

        return 0;

    }

    if (!token_list) {
 
        put_error_method( 
            "mvm_asm_parser_init", 
            "Token list pointer should not be NULL."
        );

        return 0;
        
    }

    parser->file_txt        = file_txt;
    parser->file_txt_len    = file_txt_len;
    parser->file_name       = file_name;
    parser->token_list      = token_list;
    parser->token_list_len  = 0;
    parser->token_list_size = token_list_size;
    parser->status          = MVM_AES_INIT;

    return 1;

}

i64 mvm_asm_parse (mvm_asm_parser_t * parser) {

    mvm_asm_tokenizer_t tokenizer;

    if (!parser) {
 
        put_error_method( 
            "mvm_asm_parse", 
            "Parser pointer should not be NULL."
        );

        return 0;
    }

    if (parser->status != MVM_AES_INIT) {
 
        put_error_method( 
            "mvm_asm_parse", 
            "Parser element needs to be initialized." 
        );
 
        return -1;
    }

    if (!mvm_asm_tokenizer_init(&tokenizer, parser)) {

        put_error_method( 
            "mvm_asm_parse", 
            "Something unexpected happened while initializing tokenizer." 
        );

        return -1;

    }

    if (!mvm_asm_tokenize(&tokenizer)) {
 
        put_error_method( 
            "mvm_asm_parse", 
            "Something unexpected happened while tokenizing file (%s).",
            tokenizer.parser->file_name
        );
 
        return -1;
 
    }

    for (int i = 0; i < parser->token_list_len; ++i) {
 
        mvm_asm_token_show(&(parser->token_list[i]));

    }

    return parser->token_list_len;

}

#endif /* #ifndef _ASM_H_ */