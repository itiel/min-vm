/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#ifndef _ASM_H_
#define _ASM_H_

/* -- Includes -- */

#include <stdio.h>

#include <util/err.h>
#include <util/fwn.h>
#include <util/f2b.h>

/* -- Defines -- */

// Character validation macros

// ch_is_alph      : a-Z
// ch_is_dig       : 0-9
// ch_is_alphnum   : a-Z || 0-9
// ch_is_name_lead : _ || a-Z 
// ch_is_name      : _ || a-Z || 0-9
// ch_is_hex       : 0-9 || a-F 
// ch_is_oct       : 0-7

#define      ch_is_alph(_ch) \
    ((_ch >= 'a' && _ch <= 'z') || (_ch >= 'A' && _ch <= 'Z')) 
#define       ch_is_dig(_ch) \
    (_ch >= '0' && _ch <= '9' )
#define   ch_is_alphnum(_ch) \
    (ch_is_alph(_ch) || ch_is_dig(_ch))
#define ch_is_name_lead(_ch) \
    (_ch == '_' || ch_is_alph(_ch))
#define      ch_is_name(_ch) \
    (_ch == '_' || ch_is_alphnum(_ch))
#define       ch_is_hex(_ch) \
    (ch_is_dig(_ch) || (_ch >= 'a' && _ch <= 'f') || (_ch >= 'A' && _ch <= 'F'))
#define       ch_is_oct(_ch) \
    (_ch >= '0' && _ch <= '7')

// These next 2 are to be used by mvm_asm_token_new() 

// Check if we have enough space in token_list

#define _toklst_nospace(_tknzr) \
    (_tknzr->parser->token_list_len + 1 > _tknzr->parser->token_list_size)

// _tok_next() increments 1 to token_list_len

#define _tok_next(_tknzr) \
    (&(_tknzr->parser->token_list[_tknzr->parser->token_list_len++]))

/* -- Types & Enums -- */

typedef struct mvm_asm_tokenizer_t mvm_asm_tokenizer_t;
typedef struct mvm_asm_parser_t mvm_asm_parser_t;

// Token types

typedef enum {

    MVM_ATT_START,
    MVM_ATT_NAME,
    MVM_ATT_SIGN,
    MVM_ATT_NUMBER,
    MVM_ATT_STRING,
    MVM_ATT_CHAR,
    MVM_ATT_COMMENT,
    MVM_ATT_BREAK,
    MVM_ATT_END  

} mvm_asm_token_types_t;

typedef struct mvm_asm_token_t {

    mvm_asm_tokenizer_t * tokenizer;
    i64                 row;
    i64                 col;
    i64                 start;
    i64                 len;
    i8                  type;

} mvm_asm_token_t;

// This enum describes Tokenizer and Parser elements  

typedef enum {

    MVM_AES_END,
    MVM_AES_INIT,
    MVM_AES_IN_USE,

} mvm_asm_elm_status_t;

// Tokenizer

typedef enum {

    MVM_ATS_BLANK,
    MVM_ATS_NAME,
    MVM_ATS_NUMBER,
    MVM_ATS_OCT_NUM,
    MVM_ATS_HEX_NUM,
    MVM_ATS_SIGN,
    MVM_ATS_STRING,
    MVM_ATS_STR_ESC,
    MVM_ATS_CHAR,
    MVM_ATS_COMMENT,

} mvm_asm_tokenizer_state_t;

typedef struct mvm_asm_tokenizer_t {

    mvm_asm_parser_t * parser;
    i64              ch_idx;
    i8               status;

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

// Token methods

i8 mvm_asm_token_new (
    mvm_asm_tokenizer_t * tokenizer,
    i64                 row,
    i64                 col,
    i64                 start,
    i64                 len,
    i8                  type)
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

    new_token = _tok_next(tokenizer);

    new_token->tokenizer = tokenizer;
    new_token->row       = row;
    new_token->col       = col;
    new_token->start     = start;
    new_token->len       = len;
    new_token->type      = type;

    return 1;

}

i8 * mvm_asm_token_typename (i8 tok_type) {
    
    switch (tok_type) {                        
        case MVM_ATT_START:   return "START";
        case MVM_ATT_NAME:    return "NAME";
        case MVM_ATT_SIGN:    return "SIGN";
        case MVM_ATT_NUMBER:  return "NUMBER";
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
        "<Token row: %ld\tcol: %ld\tstart: %ld\tlen: %ld\ttype: %s\tstr: ",
        token->row, token->col, token->start, token->len,
        mvm_asm_token_typename(token->type)
    );

    // TODO: Show the string of the token

    printf(">\n");

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
    tokenizer->ch_idx = -1;
    tokenizer->status = MVM_AES_INIT;

    return 1;

}

i8 mvm_asm_tokenize_error (
    mvm_asm_tokenizer_t * tokenizer, 
    i8                  * reason) 
{

    put_error_method(
        "mvm_asm_tokenize",
        "%s",
        reason
    );

    // eputchar(ch);

    return 0;

}

i8 mvm_asm_tokenize (mvm_asm_tokenizer_t * tokenizer) {

    i8  ch;
    
    i64 cur_col;
    i8  cur_state;

    i64 tok_col;
    i8  tok_type;

    // Check for initialized token

    if (tokenizer->status != MVM_AES_INIT) {

        put_error_method( 
            "mvm_asm_tokenize", 
            "Tokenizer element needs to be initialized."
        );
        
        return 0;
    }

    tokenizer->status = MVM_AES_IN_USE;

    // Start of tokenizing process

    tokenizer_start: 

    // Initialize loop variables

    cur_col   = -1;
    cur_state = MVM_ATS_BLANK;

    // Append file-start token before scanning

    tok_type = MVM_ATT_START;

    if(!mvm_asm_token_new(tokenizer, 0, 0, 0, 0, tok_type)) {

        goto new_tok_err;

    } 

    next_ch: // Kinda like 'continue'

    while (ch = tokenizer->parser->file_txt[++tokenizer->ch_idx]) {

        cur_col++;

        redo_char: // Re-eval char but with diff state

        switch (cur_state) {
            
            case MVM_ATS_BLANK:

                if (ch_is_name_lead(ch)) {
                    
                    cur_state = MVM_ATS_NAME;
                    tok_col   = cur_col;
                    tok_type  = MVM_ATT_NAME;

                    continue;
                
                }

                break;

            case MVM_ATS_NAME:

                if (ch_is_name(ch)) {
                    
                    continue;
                
                }

                return mvm_asm_tokenize_error(
                    tokenizer,
                    "Invalid name syntax"
                );

                break;

            case MVM_ATS_NUMBER:

                break;

            case MVM_ATS_OCT_NUM:

                break;

            case MVM_ATS_HEX_NUM:

                break;

            case MVM_ATS_SIGN:

                break;

            case MVM_ATS_STRING:

                break;

            case MVM_ATS_STR_ESC:

                break;

            case MVM_ATS_CHAR:

                break;

            case MVM_ATS_COMMENT:

                break;

            default:
            
                break;

        }

        // if (0) {

        //     if(!mvm_asm_token_new(tokenizer, 0, 0, 0, 0, tok_type)) {

        //         goto new_tok_err;

        //     }

        // }

    }

    // Append file-end token after finishing 

    tok_type = MVM_ATT_END;

    if(!mvm_asm_token_new(tokenizer, 0, 0, 0, 0, tok_type)) {

        goto new_tok_err;

    }

    return 1;

    new_tok_err: // New token error

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

    // Prob Check for parent elem status here

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