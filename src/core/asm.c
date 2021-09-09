/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

/* -- Includes -- */

#include <stdio.h>

#include <util/fwn.h>
#include <util/bool.h>
#include <util/chval.h>
#include <util/err.h>
#include <util/choc.h>

#include "asm.h"
#include "asm/token.h"
#include "asm/tokenizer.h"

/* -- Macro definitions -- */

// Separator characters

// ' '  - space 
// '\t' - tab
// '\f' - feed
// '\n' - new line
// '\r' - carriage return
// '.'  - period
// '$'  - dollar sign
// '+'  - plus sign
// '-'  - minus sign
// '='  - equals sign
// "'"  - single quote
// '"'  - double quote
// ':'  - colon
// ';'  - semicolon

#define SEPCHARSET (" \t\f\n\r.&+-=\"':;")

// ch_is_sep : ch in SEPCHARSET

#define ch_is_sep(_ch) char_occur(_ch, SEPCHARSET)

/* -- Enums -- */

// Assembler element status

typedef enum {

    // Don't change this order 

    MVM_AES_END,
    MVM_AES_INIT,
    MVM_AES_IN_USE,

} mvm_asm_elm_status_t;

/* -- Function definitions -- */

// Assembler methods

i32 mvm_asm_assembler_init_file ( 
    mvm_asm_assembler_t * assembler, 
    FILE                * file, 
    i8                  * file_name) 
{

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_init_file", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (!file) {
 
        put_error_method( 
            "mvm_asm_assembler_init_file", 
            "File pointer should not be NULL."
        );

        return FALSE;

    }

    assembler->file            = file;
    assembler->file_name       = file_name;
    assembler->status          = MVM_AES_INIT;

    return TRUE;

}

i32 mvm_asm_assembler_init ( 
    mvm_asm_assembler_t * assembler, 
    i8                  * file_name) 
{

    FILE * file;

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_init", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (!file_name) {
 
        put_error_method( 
            "mvm_asm_assembler_init", 
            "File name pointer should not be NULL."
        );

        return FALSE;

    }

    if (!(file = fopen(file_name, "rb"))) {

        put_error_method(
            "mvm_asm_assembler_init",
            "No such file or directory (%s).", 
            file_name
        );

        return FALSE;

    }

    return mvm_asm_assembler_init_file(assembler, file, file_name);

}

i32 mvm_asm_assembler_kill (mvm_asm_assembler_t * assembler) {

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_kill", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (assembler->status != MVM_AES_END) {

        fclose(assembler->file);

    }

    assembler->status = MVM_AES_END;

    return TRUE;

}

i32 mvm_asm_assemble (mvm_asm_assembler_t * assembler) {

    mvm_asm_tokenizer_t tokenizer;
    mvm_asm_token_t     token;
    i32                 result;

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assemble", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;
    }

    if (assembler->status != MVM_AES_INIT) {
 
        put_error_method( 
            "mvm_asm_assemble", 
            "Assembler element should be initialized." 
        );
 
        return FALSE;
    }


    if (!mvm_asm_tokenizer_init(&tokenizer, assembler)) {

        put_error_method( 
            "mvm_asm_assemble", 
            "Something unexpected happened while initializing tokenizer." 
        );

        return FALSE;

    }

    assembler->status = MVM_AES_IN_USE;

    while ((result = mvm_asm_tokenize_next(&tokenizer, &token))) {

        if (result == -1) {
 
            put_error_method( 
                "mvm_asm_assemble", 
                "Something unexpected happened while tokenizing file (%s).",
                tokenizer.assembler->file_name
            );

            return FALSE;

        }

    }

    return TRUE;

}

// Token methods

i32 mvm_asm_token_yield (
    mvm_asm_tokenizer_t * tokenizer, 
    mvm_asm_token_t     * token) 
{

    if (!tokenizer) {
 
        put_error_method( 
            "mvm_asm_token_yield", 
            "Tokenizer pointer should not be NULL."
        );

        return FALSE;

    }

    if (!token) {
 
        put_error_method( 
            "mvm_asm_token_yield", 
            "Token pointer should not be NULL."
        );

        return FALSE;

    }

    token->tokenizer = tokenizer;
    token->start     = tokenizer->data.tok_start;
    token->row       = tokenizer->data.cur_row;
    token->col       = tokenizer->data.tok_col;
    token->type      = tokenizer->data.tok_type;

    if (tokenizer->data.tok_type == MVM_ATT_SIGN) {

        token->len = 1;

    } else {

        token->len = tokenizer->data.ch_idx - \
                         tokenizer->data.tok_start;
    }

    mvm_asm_token_show(token);

    return TRUE;

}

i32 mvm_asm_token_show (mvm_asm_token_t * token) {

    if (!token) {

        put_error_method( 
            "mvm_asm_token_show", 
            "Token pointer should not be NULL."
        );

        return FALSE;
    }

    printf(
        "<Token row: %ld\tcol: %ld\t" \
        "start: %ld\tlen: %ld\ttype: ",
        token->row, token->col, 
        token->start, token->len
    );

    // Show token typename

    mvm_asm_token_typename_show(token);

    // Show token str

    printf("\tstr: ");

    mvm_asm_token_repr_show(token);

    printf(">\n");

    return TRUE;

}

i32 mvm_asm_token_repr_show (mvm_asm_token_t * token) {

    i8 ch;

    if (token->type == MVM_ATT_START ||
        token->type == MVM_ATT_END   ||
        token->type == MVM_ATT_BREAK) {
 
        printf("N/A");

        return FALSE;

    }

    mvm_asm_token_reader_t tok_reader;

    mvm_asm_token_reader_init(&tok_reader, token);

    putchar('"');

    while ((ch = mvm_asm_token_read_next(&tok_reader)) != EOF) {

        if ((ch >= 0 && 
            ch <= 31) || 
            ch == 127) 
        {
 
                 if (ch == '\b') printf("\\b");
            else if (ch == '\t') printf("\\t");
            else if (ch == '\r') printf("\\r");
            else if (ch == '\f') printf("\\f");
            else if (ch == '\v') printf("\\v");
            else if (ch == '\n') printf("\\n");
            else printf("\\x%02x", (int) ch);

            continue;

        }

        if (ch == 34 || ch == 92 ) {

            putchar('\\');

        }

        putchar(ch);

    }

    putchar('"');

    return TRUE;

}

i32 mvm_asm_token_typename_show (mvm_asm_token_t * token) {

    i8 * type_name; 

    // TODO: Check for null pointer
 
    switch (token->type) { 
 
        case MVM_ATT_START:   type_name = "START";   break;
        case MVM_ATT_NAME:    type_name = "NAME";    break;
        case MVM_ATT_NUMBER:  type_name = "NUMBER";  break;
        case MVM_ATT_NUM_BIN: type_name = "BINARY";  break;
        case MVM_ATT_NUM_OCT: type_name = "OCTAL";   break;
        case MVM_ATT_NUM_HEX: type_name = "HEXA";    break;
        case MVM_ATT_SIGN:    type_name = "SIGN";    break;
        case MVM_ATT_STRING:  type_name = "STRING";  break;
        case MVM_ATT_CHAR:    type_name = "CHAR";    break;
        case MVM_ATT_COMMENT: type_name = "COMMENT"; break;
        case MVM_ATT_BREAK:   type_name = "BREAK";   break;
        case MVM_ATT_END:     type_name = "END";     break;
        default:              type_name = "N/A";     break;

    }

    printf("%s", type_name);

    return TRUE;

}

i32 mvm_asm_token_reader_init (
    mvm_asm_token_reader_t * token_reader,
    mvm_asm_token_t        * token) 
{

    if (!token_reader) {

        put_error_method( 
            "mvm_asm_token_reader_init", 
            "Token-reader pointer should not be NULL."
        );

        return FALSE;
    } 

    if (!token) {

        put_error_method( 
            "mvm_asm_token_reader_init", 
            "Token pointer should not be NULL."
        );

        return FALSE;
    } 

    token_reader->token  = token;
    token_reader->ch_idx = 0;
    token_reader->status = MVM_AES_INIT;

    fseek(token->tokenizer->assembler->file, token->start, SEEK_SET);

    return TRUE;

}

i32 mvm_asm_token_read_next (mvm_asm_token_reader_t * token_reader) {

    if (token_reader->status == MVM_AES_END) {
 
        return EOF;

    }

    token_reader->status = MVM_AES_IN_USE;

    if (token_reader->token->type == MVM_ATT_START ||
        token_reader->token->type == MVM_ATT_END   ||
        token_reader->token->type == MVM_ATT_BREAK ||
        token_reader->ch_idx == token_reader->token->len) 
    {

        token_reader->status = MVM_AES_END;

        return EOF;

    }

    token_reader->ch_idx++;

    return getc(token_reader->token->tokenizer->assembler->file);

}

// Tokenizer methods

i32 mvm_asm_tokenizer_init (
    mvm_asm_tokenizer_t * tokenizer, 
    mvm_asm_assembler_t    * assembler) 
{ 

    if (!tokenizer) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Tokenizer pointer should not be NULL."
        );

        return FALSE;
    }

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;
    }

    if (assembler->status != MVM_AES_INIT) {
 
        put_error_method( 
            "mvm_asm_tokenizer_init", 
            "Assembler element should be initialized."
        );
 
        return FALSE;
    }

    assembler->status = MVM_AES_IN_USE;

    tokenizer->assembler = assembler;
    tokenizer->status = MVM_AES_INIT;

    // Loop variables

    tokenizer->data.cur_state  = MVM_ATDS_BLANK;
    tokenizer->data.redo_char  = FALSE;
    tokenizer->data.last_break = 0;
    tokenizer->data.ch_idx     = 0;
    tokenizer->data.cur_col    = -1;
    tokenizer->data.cur_row    = -1;

    // Token variables

    tokenizer->data.tok_start = 0;
    tokenizer->data.tok_col   = 0;
    tokenizer->data.tok_type  = MVM_ATT_START;

    return TRUE;

}

i32 mvm_asm_tokenize_error (
    mvm_asm_tokenizer_t * tokenizer, 
    i8                  * reason) 
{ 

    eprintf(
        "Tokenizer error @ (%ld:%ld):\n" \
        "In file %s\n" \
        "  %s\n",
        tokenizer->data.cur_row + 1, 
        tokenizer->data.cur_col + 1,
        tokenizer->assembler->file_name,
        reason
    );
 
    // Show line of code and point to 
    // troubling character with an arrow

    // TODO: Show the whole line, not just 
    //       up to the character in question

    i64 line_start;
    i64 ch_idx;
    i64 i;
    i8  ch;

    line_start = tokenizer->data.last_break + 1;
    ch_idx     = tokenizer->data.ch_idx - line_start + 1;

    fseek(tokenizer->assembler->file, line_start, SEEK_SET);

    // Code line
 
    eprintf("    "); 

    for (i = 0; i < ch_idx; ++i) {

        ch = getc(tokenizer->assembler->file);

        if (ch == '\n') break;
 
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

    return TRUE;

}

i32 mvm_asm_tokenize_next (
    mvm_asm_tokenizer_t * tokenizer,
    mvm_asm_token_t     * token)
{

    i8  ch;        // The character to check
    i32 on_esc;    // Escape char in string or char literal
    i32 lead_zero; // Number literals starting with '0'
    i32 fisrt_ch;  // First character in token flag

    if (!tokenizer) {
 
        put_error_method( 
            "mvm_asm_tokenize_next", 
            "Tokenizer pointer should not be NULL."
        );

        return -1;

    }

    if (!token) {
 
        put_error_method( 
            "mvm_asm_tokenize_next", 
            "Token pointer should not be NULL."
        );

        return -1;

    }

    if (tokenizer->status == MVM_AES_END) return 0;

    // Start of process

    if (tokenizer->status == MVM_AES_INIT) {
 
        // Append file-start token before scanning

        if (!mvm_asm_token_yield(tokenizer, token)) 
            goto tok_yld_err;

        tokenizer->status = MVM_AES_IN_USE;

        return 1;

    }

    fseek(tokenizer->assembler->file, tokenizer->data.ch_idx + 1, SEEK_SET);

    on_esc    = FALSE;
    lead_zero = FALSE;
    fisrt_ch  = FALSE;

    if (tokenizer->data.redo_char) {

        tokenizer->data.redo_char = FALSE;
 
        goto redo_char;
 
    }

    while ((ch = getc(tokenizer->assembler->file)) != EOF) {

        tokenizer->data.ch_idx++; 
        tokenizer->data.cur_col++;

        // GOTO: Re-eval char but with diff state

        redo_char: 

        switch (tokenizer->data.cur_state) {

        // Just starting or after on a separator char

        // TODO: Implement scanning labels starting with '.' 
        //       and var names starting with '$' 

        case MVM_ATDS_BLANK:

            switch (ch) {

            case ' ': case '\t': case '\r': case '\f':

                continue;

            case '\n':

                tokenizer->data.tok_type  = MVM_ATT_BREAK;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.last_break = tokenizer->data.ch_idx;
 
                tokenizer->data.cur_col = -1;
                tokenizer->data.cur_row += 1;

                return 1;

            case '+': case '-': case '=': case ':':

                tokenizer->data.tok_type  = MVM_ATT_SIGN;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                return 1;

            case '"':

                tokenizer->data.cur_state = MVM_ATDS_STRING;

                tokenizer->data.tok_type  = MVM_ATT_STRING;
                tokenizer->data.tok_start = tokenizer->data.ch_idx + 1;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            case '\'':

                tokenizer->data.cur_state = MVM_ATDS_CHAR;

                tokenizer->data.tok_type  = MVM_ATT_CHAR;
                tokenizer->data.tok_start = tokenizer->data.ch_idx + 1;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                fisrt_ch = TRUE;

                continue;

            case ';':

                tokenizer->data.cur_state = MVM_ATDS_COMMENT;

                tokenizer->data.tok_type  = MVM_ATT_COMMENT;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            }

            if (ch_is_name_lead(ch)) {

                tokenizer->data.cur_state = MVM_ATDS_NAME;

                tokenizer->data.tok_type  = MVM_ATT_NAME;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                continue;

            }

            if (ch_is_dig(ch)) {

                tokenizer->data.cur_state = MVM_ATDS_NUMBER;

                tokenizer->data.tok_type  = MVM_ATT_NUMBER;
                tokenizer->data.tok_start = tokenizer->data.ch_idx;
                tokenizer->data.tok_col   = tokenizer->data.cur_col;

                if (ch == '0') lead_zero = TRUE;

                fisrt_ch = TRUE;

                continue;

            }

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid syntax"
            );

            printf("ftell = %ld\n", ftell(tokenizer->assembler->file));
            printf("ch = %d = %c\n", ch, ch);

            return -1;

        case MVM_ATDS_NAME:

            if (ch_is_sep(ch)) {

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            if (ch_is_name(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid name syntax"
            );

            return -1;

        case MVM_ATDS_NUMBER:

            if (ch_is_sep(ch)) {

                // Only if it's more than 1 character

                if (!fisrt_ch && lead_zero) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Ilegal zero-leading decimal"
                    );

                    return -1;
 
                }

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            // Only on second character

            if (fisrt_ch) {
 
                fisrt_ch = FALSE;

                if (lead_zero) {

                    if (ch == 'b' || ch == 'B') {

                        tokenizer->data.cur_state = MVM_ATDS_NUM_BIN;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_BIN;

                        fisrt_ch = TRUE; // First character after 0b

                        continue;

                    }

                    if (ch == 'o' || ch == 'O') {

                        tokenizer->data.cur_state = MVM_ATDS_NUM_OCT;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_OCT;

                        fisrt_ch = TRUE; // First character after 0o

                        continue;

                    }

                    if (ch == 'x' || ch == 'X') {

                        tokenizer->data.cur_state = MVM_ATDS_NUM_HEX;
                        tokenizer->data.tok_type  = MVM_ATT_NUM_HEX;

                        fisrt_ch = TRUE; // First character after 0x

                        continue;

                    }

                }
            }

            if (ch_is_dig(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid decimal syntax"
            );

            return -1;

        case MVM_ATDS_NUM_BIN:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0b

                if (fisrt_ch) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid binary syntax"
                    );

                    return -1;
 
                }

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            fisrt_ch = FALSE; 

            if (ch_is_bin(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid binary syntax"
            );

            return -1;

        case MVM_ATDS_NUM_OCT:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0o

                if (fisrt_ch) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid octal syntax"
                    );

                    return -1;
 
                }

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            fisrt_ch = FALSE; 

            if (ch_is_oct(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid octal syntax"
            );

            return -1;

        case MVM_ATDS_NUM_HEX:

            if (ch_is_sep(ch)) {

                // Only if it's the first 
                // character after 0x

                if (fisrt_ch) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Invalid hexadecimal syntax"
                    );

                    return -1;
 
                }

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            fisrt_ch = FALSE; 

            if (ch_is_hex(ch)) continue;

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid hexadecimal syntax"
            );

            return -1;

        case MVM_ATDS_STRING:
        case MVM_ATDS_CHAR:

            if (ch == '\n') {

                if (tokenizer->data.cur_state == MVM_ATDS_STRING) {

                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Ilegal line break in string literal"
                    );

                } else {
 
                    mvm_asm_tokenize_error(
                        tokenizer,
                        "Ilegal line break in character literal"
                    );

                }

                return -1;

            }

            if (on_esc) {

                on_esc = FALSE;

                continue;

            }

            if (ch == '\\') {

                on_esc = TRUE;

                continue;

            }
 
            if ((tokenizer->data.cur_state == MVM_ATDS_STRING && 
                ch == '"') || ch == '\'') 
            {

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                return 1;

            }

            if (tokenizer->data.cur_state == MVM_ATDS_STRING || fisrt_ch) {

                fisrt_ch = FALSE;
 
                continue;

            }

            mvm_asm_tokenize_error(
                tokenizer,
                "Multi-character character literal"
            );

            return -1;

        case MVM_ATDS_COMMENT:

            if (ch == '\n') {

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                tokenizer->data.redo_char = TRUE;

                return 1;

            }

            continue;

        default:
 
            put_error_method( 
                "mvm_asm_tokenize", 
                "Tokenizer state out of range (%d).",
                tokenizer->data.cur_state
            );
 
            return -1;

        }

    }

    // TODO: Check for incomplete tokens

    // Append file-end token after finishing 

    tokenizer->data.tok_type = MVM_ATT_END;

    if (!mvm_asm_token_yield(tokenizer, token)) 
        goto tok_yld_err;

    tokenizer->status = MVM_AES_END;

    return 1;

    // GOTO: Token yield error
 
    tok_yld_err: 

    put_error_method( 
        "mvm_asm_tokenize_next", 
        "Something unexpected happened while yielding token."
    );
 
    return -1;

}
