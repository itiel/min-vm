/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#ifndef _ASM_H_
#define _ASM_H_

/* -- Includes -- */

#include <stdio.h>

#include <util/fwn.h>
#include <util/f2b.h>

/* -- Defines -- */

/*
 . ch_is_alph    : a-Z
 . ch_is_dig     : 0-9
 . ch_is_alphnum : a-Z || 0-9
 . ch_is_hex     : 0-9 || a-F 
 . ch_is_oct     : 0-7
*/

#define ch_is_alph    (_ch) \
    ((_ch >= 'a' and _ch <= 'z') || (_ch >= 'A' and _ch <= 'Z')) 
#define ch_is_dig     (_ch) (_ch >= '0' && _ch <= '9' )
#define ch_is_alphnum (_ch) (ch_is_alph (_ch) || ch_is_dig (_ch))
#define ch_is_hex     (_ch) \
    (ch_is_dig(_ch) || (_ch >= 'a' && _ch <= 'f') || (_ch >= 'A' && _ch <= 'F'))
#define ch_is_oct     (_ch) (_ch >= '0' && _ch <= '7')

/* 
 . These next 2 are to be used by mvm_asm_token_new() 
 . _toknxt() increments 1 to token_list_len
*/

#define _toklstszex(_tknzr) \
    (_tknzr->parser->token_list_len + 1 > _tknzr->parser->token_list_size)

#define _toknxt(_tknzr) \
    (&(_tknzr->parser->token_list[_tknzr->parser->token_list_len++]))

/* -- Types -- */

typedef struct mvm_asm_tokenizer_t mvm_asm_tokenizer_t;
typedef struct mvm_asm_parser_t mvm_asm_parser_t;

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
    i64                 start;
    i64                 len;
    i64                 row;
    i64                 col;
    i8                  type;

} mvm_asm_token_t;

typedef enum {

    MVM_AES_END,
    MVM_AES_INIT,
    MVM_AES_IN_USE,

} mvm_asm_elm_status_t;

typedef struct mvm_asm_tokenizer_t {

    mvm_asm_parser_t * parser;
    i64              ch_idx;
    i8               status;

} mvm_asm_tokenizer_t;

typedef struct mvm_asm_parser_t {
 
    i8              * src; 
    i64             src_len;
    mvm_asm_token_t * token_list; 
    i64             token_list_len;
    i64             token_list_size;
    i8              status;

} mvm_asm_parser_t;

/* -- Functions -- */

i8 mvm_asm_token_new (
    mvm_asm_tokenizer_t * tokenizer,
    i64                 start,
    i64                 len,
    i64                 row,
    i64                 col,
    i8                  type)
{

    char            * error_msg;
    mvm_asm_token_t * new_token;

    if (_toklstszex(tokenizer)) {
        
        error_msg = 
            "Error in mvm_asm_token_new():\n" \
            "  Token list size needed exceeds actual size (%ld).\n";

        fprintf(stderr, error_msg, tokenizer->parser->token_list_size);

        return 0;

    }

    new_token = _toknxt(tokenizer);

    new_token->tokenizer = tokenizer;
    new_token->start     = start;
    new_token->len       = len;
    new_token->row       = row;
    new_token->col       = col;
    new_token->type      = type;

    return 1;

}

i8 mvm_asm_tokenizer_init (
    mvm_asm_tokenizer_t * tokenizer, 
    mvm_asm_parser_t    * parser) 
{ 

    char * error_msg;

    // TODO: Check for NULL pointers

    if (parser->status != MVM_AES_INIT) {
        
        error_msg = 
            "Error in mvm_asm_tokenizer_init():\n" \
            "  Parser element needs to be initialized.\n";

        fprintf(stderr, error_msg, 0);
        
        return 0;
    }

    parser->status = MVM_AES_IN_USE;

    tokenizer->parser = parser;
    tokenizer->ch_idx = -1;
    tokenizer->status = MVM_AES_INIT;

    return 1;

}

i8 mvm_asm_tokenize (mvm_asm_tokenizer_t * tokenizer) {

    char * error_msg;
    i8   ch;

    if (tokenizer->status != MVM_AES_INIT) {
        
        error_msg = 
            "Error in mvm_asm_tokenize():\n" \
            "  Tokenizer element needs to be initialized.\n";

        fprintf(stderr, error_msg, 0);
        
        return 0;
    }

    tokenizer->status = MVM_AES_IN_USE;

    // TODO: append file start token before starting 

    while (ch = tokenizer->parser->src[++tokenizer->ch_idx]) {

        // TODO: Develop this part

        if (0) {

            if(!mvm_asm_token_new(tokenizer, 0, 0, 0, 0, MVM_ATT_START)) {

                error_msg = 
                    "Error in mvm_asm_tokenize():\n" \
                    "  Something unexpected happened while generating new token.\n";

                fprintf(stderr, error_msg, 0);
                
                return 0;

            }

        }

    }

    // TODO: append file end token after finishing 

    return 1;

}

i8 mvm_asm_parser_init ( 
    mvm_asm_parser_t * parser, 
    i8               * src, 
    i64              src_len, 
    mvm_asm_token_t  * token_list, 
    i64              token_list_size) 
{

    // Prob Check for parent elem status here

    // TODO: Check for NULL pointers

    parser->src             = src;
    parser->src_len         = src_len;
    parser->token_list      = token_list;
    parser->token_list_len  = 0;
    parser->token_list_size = token_list_size;
    parser->status          = MVM_AES_INIT;

    return 1;

}

i64 mvm_asm_parse (mvm_asm_parser_t * parser) {

    char                * error_msg;
    mvm_asm_tokenizer_t tokenizer;

    // TODO: Check for NULL pointers

    if (parser->status != MVM_AES_INIT) {
        
        error_msg = 
            "Error in mvm_asm_parse():\n" \
            "  Parser element needs to be initialized.\n";

        fprintf(stderr, error_msg, 0);
        
        return -1;
    }

    if (!mvm_asm_tokenizer_init(&tokenizer, parser)) {

        error_msg = 
            "Error in mvm_asm_parse():\n" \
            "  Something unexpected happened while initializing tokenizer.\n";

        fprintf(stderr, error_msg, 0);
        
        return -1;

    }

    if (!mvm_asm_tokenize(&tokenizer)) {
        
        error_msg = 
            "Error in mvm_asm_parse():\n" \
            "  Something unexpected happened while tokenizing file.\n";

        fprintf(stderr, error_msg, 0);
        
        return -1;
    
    }

    return parser->token_list_len;

}

#endif /* #ifndef _ASM_H_ */