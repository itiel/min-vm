/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 31/08/2021
*/

#ifndef _MVM_ASM_TOKEN_H_
#define _MVM_ASM_TOKEN_H_

/* -- Includes -- */

#include <util/fwn.h>

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
    MVM_ATT_SIGN,    // plus, minus and equals signs (+-=)
    MVM_ATT_STRING,  // double quoted string literal
    MVM_ATT_CHAR,    // single quoted char literal
    MVM_ATT_COMMENT, // semicolon leading comment
    MVM_ATT_BREAK,   // line break (\n)
    MVM_ATT_END,     // file-end

} mvm_asm_token_type_t;


/* -- Types -- */

typedef struct mvm_asm_token_t mvm_asm_token_t;
typedef struct mvm_asm_token_reader_t mvm_asm_token_reader_t;
typedef struct mvm_asm_tokenizer_t mvm_asm_tokenizer_t;

/* -- Functions -- */

i32 mvm_asm_token_yield         (mvm_asm_tokenizer_t * tokenizer, mvm_asm_token_t * token);
i32 mvm_asm_token_show          (mvm_asm_token_t * token);
i32 mvm_asm_token_repr_show     (mvm_asm_token_t * token);
i32 mvm_asm_token_typename_show (mvm_asm_token_t * token);
i32 mvm_asm_token_reader_init   (mvm_asm_token_reader_t * token_reader, mvm_asm_token_t * token);
i32 mvm_asm_token_read_next     (mvm_asm_token_reader_t * token_reader);

#endif /* #ifndef _MVM_ASM_TOKEN_H_ */
