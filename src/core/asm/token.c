/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/09/2021
*/

/* -- Includes -- */

#include <core/asm/token.h>
#include <core/asm/tokenizer.h>

#include <util/err.h>
#include <util/bool.h>

/* -- Token methods -- */

i32 mvm_asm_token_type_is_valid (i32 token_type) {
 
    return token_type >= MVM_ATT_START && token_type <= MVM_ATT_END;

}

i32 mvm_asm_token_start (
    mvm_asm_tokenizer_t * tokenizer,
    i32                 tok_type) 
{

    if (!tokenizer) {
 
        put_error_method( 
            "mvm_asm_token_start", 
            "Tokenizer pointer should not be NULL."
        );

        return FALSE;

    }

    if (!mvm_asm_token_type_is_valid(tok_type)) {

        put_error_method( 
            "mvm_asm_token_start", 
            "Token type not valid. (%d)",
            tok_type
        );

        return FALSE;

    }

    tokenizer->data.tok_type  = tok_type;
    tokenizer->data.tok_start = tokenizer->data.ch_idx;
    tokenizer->data.tok_col   = tokenizer->data.cur_col;

    if (tok_type == MVM_ATT_STRING || tok_type == MVM_ATDS_CHAR) {

        tokenizer->data.tok_start++;
 
    }

    return TRUE;

}

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

    if (tokenizer->data.cur_state == MVM_ATDS_SIGN) {

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

    if (!token) {

        put_error_method( 
            "mvm_asm_token_typename_show", 
            "Token pointer should not be NULL."
        );

        return FALSE;
    }
 
    switch (token->type) { 
 
        case MVM_ATT_START:   type_name = "START";   break;
        case MVM_ATT_NAME:    type_name = "NAME";    break;
        case MVM_ATT_NUMBER:  type_name = "NUMBER";  break;
        case MVM_ATT_NUM_BIN: type_name = "BINARY";  break;
        case MVM_ATT_NUM_OCT: type_name = "OCTAL";   break;
        case MVM_ATT_NUM_HEX: type_name = "HEXA";    break;
        case MVM_ATT_SGN_PR:  type_name = "PERIOD";  break;
        case MVM_ATT_SGN_PL:  type_name = "PLUS";    break;
        case MVM_ATT_SGN_MN:  type_name = "MINUS";   break;
        case MVM_ATT_SGN_EQ:  type_name = "EQUALS";  break;
        case MVM_ATT_SGN_DL:  type_name = "DOLLAR";  break;
        case MVM_ATT_SGN_AT:  type_name = "AT";      break;
        case MVM_ATT_SGN_CL:  type_name = "COLON";   break;
        case MVM_ATT_SGN_HS:  type_name = "HASH";    break;
        case MVM_ATT_SGN_PC:  type_name = "PERCENT"; break;
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
