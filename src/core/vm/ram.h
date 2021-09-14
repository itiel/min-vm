/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/09/2021
*/

#ifndef _RAM_H_
#define _RAM_H_

/* -- Includes -- */

#include <core/vm.h>

/* -- Macro definitions -- */

#define MVM_RAM_SZ     0x10000 // 0xFF is like 99, not quite 100
#define MVM_RAM_DMP_RW 0x10
#define MVM_RAM_DMP_CH '.'

/* -- Type definitions -- */

typedef struct mvm_vm_ram_t {

    i64            size;
    mvm_vm_uword_t * buffer;

} mvm_vm_ram_t;

/* -- Function declarations -- */

i32 mvm_vm_ram_init (mvm_vm_ram_t * ram_instnc); 
i32 mvm_vm_ram_kill (mvm_vm_ram_t * ram_instnc); 
i32 mvm_vm_ram_dump (mvm_vm_ram_t * ram_instnc); 

#endif /* #ifndef _RAM_H_ */
