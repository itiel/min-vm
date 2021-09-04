/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 31/08/2021
*/

#ifndef _MVM_ASM_H_
#define _MVM_ASM_H_

/* -- Includes -- */

#include <stdio.h>

/* -- Types -- */

typedef struct mvm_asm_assembler_t {
 
    FILE * file;
    char * file_name;
    int    status;

} mvm_asm_assembler_t;

/* -- Functions -- */

int mvm_asm_assembler_init      (mvm_asm_assembler_t * assembler, char * file_name);
int mvm_asm_assembler_init_file (mvm_asm_assembler_t * assembler, FILE * file, char * file_name);
int mvm_asm_assemble            (mvm_asm_assembler_t * assembler);
int mvm_asm_assembler_kill      (mvm_asm_assembler_t * assembler);

#endif /* #ifndef _MVM_ASM_H_ */
