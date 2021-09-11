/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 31/08/2021
*/

#ifndef _MVM_ASM_TOKEN_H_
#define _MVM_ASM_TOKEN_H_

/* -- Includes -- */

#include <util/fwn.h>

#include "../asm.h"

/* -- Enums -- */

// Token types

typedef enum {

    MVM_ATT_START,   // file-start
    MVM_ATT_NAME,    // instruction, variable or tag name
                     // maybe even booleans (true & false)
    MVM_ATT_NUMBER,  // decimal, no float or e-notation
    MVM_ATT_NUM_BIN, // binary number
    MVM_ATT_NUM_OCT, // octal number
    MVM_ATT_NUM_HEX, // hexadecimal number
    MVM_ATT_SGN_PR,  // period (.)
    MVM_ATT_SGN_PL,  // plus sign (+)
    MVM_ATT_SGN_MN,  // minus sign (-)
    MVM_ATT_SGN_EQ,  // equals sign (=)
    MVM_ATT_SGN_DL,  // dollar sign ($)
    MVM_ATT_SGN_AT,  // at symbol (@)
    MVM_ATT_SGN_CL,  // colon sign (:)
    MVM_ATT_SGN_HS,  // hash symbol (#)
    MVM_ATT_SGN_PC,  // percentage symbol (%)
    MVM_ATT_STRING,  // double quoted string literal
    MVM_ATT_CHAR,    // single quoted char literal
    MVM_ATT_COMMENT, // semicolon leading comment
    MVM_ATT_BREAK,   // line break (\n)
    MVM_ATT_END,     // file-end

} mvm_asm_token_type_t;


/* -- Types -- */

typedef struct mvm_asm_token_t {

    mvm_asm_tokenizer_t * tokenizer;
    i64                 start;
    i64                 row;
    i64                 col;
    i64                 len;
    i32                 type;

} mvm_asm_token_t;

typedef struct mvm_asm_token_reader_t {

    mvm_asm_token_t * token;
    i64             ch_idx;
    i32             status;

} mvm_asm_token_reader_t;

/* -- Functions -- */

i32 mvm_asm_token_yield         (mvm_asm_tokenizer_t * tokenizer, mvm_asm_token_t * token);
i32 mvm_asm_token_show          (mvm_asm_token_t * token);
i32 mvm_asm_token_repr_show     (mvm_asm_token_t * token);
i32 mvm_asm_token_typename_show (mvm_asm_token_t * token);
i32 mvm_asm_token_reader_init   (mvm_asm_token_reader_t * token_reader, mvm_asm_token_t * token);
i32 mvm_asm_token_read_next     (mvm_asm_token_reader_t * token_reader);

#endif /* #ifndef _MVM_ASM_TOKEN_H_ */
