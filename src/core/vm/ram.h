/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/09/2021
*/

#ifndef _MVM_VM_RAM_H_
#define _MVM_VM_RAM_H_

/* -- Includes -- */

#include <util/fwn.h>

#include <core/dunt.h>

/* -- Macro definitions -- */

// Max reachable value with
// segment:offset system and 
// only 8-bit registers
// 0xFF:0xFF = 0x10EF = 4335

#define MVM_RAM_SZ 0x10EF 

// 0xF is like 9, not quite 10

#define MVM_RAM_DMP_RW 0x10
#define MVM_RAM_DMP_CH '.'

/* -- Type definitions -- */

typedef struct mvm_vm_ram_t {

    i64         size;
    mvm_word_t * buffer;

} mvm_vm_ram_t;

/* -- Function declarations -- */

i32 mvm_vm_ram_init (mvm_vm_ram_t * ram_instnc); 
i32 mvm_vm_ram_kill (mvm_vm_ram_t * ram_instnc); 
i32 mvm_vm_ram_dump (mvm_vm_ram_t * ram_instnc); 

#endif /* #ifndef _MVM_VM_RAM_H_ */
