/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 31/08/2021
*/

#ifndef _MVM_ASM_TOKENIZER_H_
#define _MVM_ASM_TOKENIZER_H_

/* -- Includes -- */

#include <util/fwn.h>

/* -- Enums -- */

// Tokenizer data state

typedef enum {

    MVM_ATDS_BLANK,   // space or tab
    MVM_ATDS_NAME,    // instruction, variable or tag name
                      // maybe even booleans (true & false)
    MVM_ATDS_NUMBER,  // decimal, no float or e notation
    MVM_ATDS_NUM_BIN, // binary number
    MVM_ATDS_NUM_OCT, // octal number
    MVM_ATDS_NUM_HEX, // hexadecimal number
    MVM_ATDS_STRING,  // double quoted string literal
    MVM_ATDS_CHAR,    // single quoted char literal
    MVM_ATDS_COMMENT, // semicolon leading comment

} mvm_asm_tokenizer_data_state_t;

/* -- Types -- */

typedef struct mvm_asm_assembler_t mvm_asm_assembler_t;
typedef struct mvm_asm_token_t mvm_asm_token_t;

typedef struct mvm_asm_tokenizer_data_t {

    i32 cur_state;
    i32 redo_char;
    i64 last_break;
    i64 ch_idx;
    i64 cur_col;
    i64 cur_row;
    i64 tok_start;
    i64 tok_col;
    i32 tok_type;

} mvm_asm_tokenizer_data_t;

typedef struct mvm_asm_tokenizer_t {

    mvm_asm_assembler_t      * assembler;
    mvm_asm_tokenizer_data_t data;
    i32                      status;

} mvm_asm_tokenizer_t;


/* -- Functions -- */

i32 mvm_asm_tokenizer_init (mvm_asm_tokenizer_t * tokenizer, mvm_asm_assembler_t * assembler);
i32 mvm_asm_tokenize_next  (mvm_asm_tokenizer_t * tokenizer, mvm_asm_token_t * token);
i32 mvm_asm_tokenize_error (mvm_asm_tokenizer_t * tokenizer, i8 * reason);

#endif /* #ifndef _MVM_ASM_TOKENIZER_H_ */
