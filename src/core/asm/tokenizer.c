/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/09/2021
*/

/* -- Includes -- */

#include <core/asm/token.h>
#include <core/asm/tokenizer.h>

#include <util/err.h>
#include <util/bool.h>
#include <util/choc.h>
#include <util/chval.h>

/* -- Macro definitions -- */

// Separator characters

// ' '  - space 
// '\t' - tab
// '\f' - feed
// '\n' - new line
// '\r' - carriage return
// '.'  - period
// '+'  - plus sign
// '-'  - minus sign
// '='  - equals sign
// '$'  - dollar sign
// '@'  - at symbol
// ':'  - colon
// '#'  - hash symbol
// '%'  - percentage symbol
// "'"  - single quote
// '"'  - double quote
// ';'  - semicolon

#define SEPCHARSET (" \t\f\n\r.+-=$@:#%\"';")

// ch_is_sep : ch in SEPCHARSET

#define ch_is_sep(_ch) char_occur(_ch, SEPCHARSET)

/* -- Tokenizer methods -- */

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
        tokenizer->data.cur_row + 2, 
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

        case MVM_ATDS_BLANK:

            switch (ch) {

            case ' ': case '\t': case '\r': case '\f':

                // True blank

                continue;

            case '\n':

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_BREAK)) 
                    goto tok_str_err;

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.last_break = tokenizer->data.ch_idx;
 
                tokenizer->data.cur_col = -1;
                tokenizer->data.cur_row += 1;

                return 1;

            case '.': case '+': case '-': case '=': 
            case '$': case '@': case ':': case '#':
            case '%': 

                tokenizer->data.cur_state = MVM_ATDS_SIGN;

                if (!mvm_asm_token_start(
                    tokenizer, 
                    ch == '.' ? MVM_ATT_SGN_PR :
                    ch == '+' ? MVM_ATT_SGN_PL :
                    ch == '-' ? MVM_ATT_SGN_MN :
                    ch == '=' ? MVM_ATT_SGN_EQ :
                    ch == '$' ? MVM_ATT_SGN_DL :
                    ch == '@' ? MVM_ATT_SGN_AT :
                    ch == ':' ? MVM_ATT_SGN_CL :
                    ch == '#' ? MVM_ATT_SGN_HS :
                    MVM_ATT_SGN_PC)) 
                    goto tok_str_err;

                if (!mvm_asm_token_yield(tokenizer, token)) 
                    goto tok_yld_err;

                tokenizer->data.cur_state = MVM_ATDS_BLANK;

                return 1;

            case '"':

                tokenizer->data.cur_state = MVM_ATDS_STRING;

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_STRING)) 
                    goto tok_str_err;

                continue;

            case '\'':

                tokenizer->data.cur_state = MVM_ATDS_CHAR;

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_CHAR)) 
                    goto tok_str_err;

                fisrt_ch = TRUE;

                continue;

            case ';':

                tokenizer->data.cur_state = MVM_ATDS_COMMENT;

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_COMMENT)) 
                    goto tok_str_err;

                continue;

            }

            if (ch_is_name_lead(ch)) {

                tokenizer->data.cur_state = MVM_ATDS_NAME;

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_NAME)) 
                    goto tok_str_err;

                continue;

            }

            if (ch_is_dig(ch)) {

                tokenizer->data.cur_state = MVM_ATDS_NUMBER;

                if (!mvm_asm_token_start(tokenizer, MVM_ATT_NUMBER)) 
                    goto tok_str_err;

                if (ch == '0') lead_zero = TRUE;

                fisrt_ch = TRUE;

                continue;

            }

            mvm_asm_tokenize_error(
                tokenizer,
                "Invalid syntax"
            );

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

    // GOTO: Token start error
 
    tok_str_err: 

    put_error_method( 
        "mvm_asm_tokenize_next", 
        "Something unexpected happened while starting token."
    );
 
    return -1;

    // GOTO: Token yield error
 
    tok_yld_err: 

    put_error_method( 
        "mvm_asm_tokenize_next", 
        "Something unexpected happened while yielding token."
    );
 
    return -1;

}
