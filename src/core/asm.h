/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 31/08/2021
*/

#ifndef _MVM_ASM_H_
#define _MVM_ASM_H_

/* -- Includes -- */

#include <stdio.h>

#include <util/fwn.h>

#include <core/elst.h>

/* -- Types -- */

typedef struct mvm_asm_assembler_t {
 
    FILE * file;
    i8   * file_name;
    i32  status;

} mvm_asm_assembler_t;

typedef struct mvm_asm_token_t mvm_asm_token_t;
typedef struct mvm_asm_token_reader_t mvm_asm_token_reader_t;
typedef struct mvm_asm_tokenizer_data_t mvm_asm_tokenizer_data_t;
typedef struct mvm_asm_tokenizer_t mvm_asm_tokenizer_t;

/* -- Functions -- */

i32 mvm_asm_assembler_init      (mvm_asm_assembler_t * assembler, i8 * file_name);
i32 mvm_asm_assembler_init_file (mvm_asm_assembler_t * assembler, FILE * file, i8 * file_name);
i32 mvm_asm_assemble            (mvm_asm_assembler_t * assembler);
i32 mvm_asm_assembler_kill      (mvm_asm_assembler_t * assembler);

#endif /* #ifndef _MVM_ASM_H_ */
