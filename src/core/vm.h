/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
*/

#ifndef _MVM_VM_H_
#define _MVM_VM_H_

/* -- Includes -- */

#include <util/fwn.h>

#include <core/dunt.h>

#include <core/vm/reg.h>
#include <core/vm/ram.h>

/* -- Type definitions -- */

typedef struct mvm_vm_t {

    i32                status;
    mvm_vm_regs_main_t main_regs;
    mvm_vm_reg_ptr_t   addr_ptr;
    mvm_vm_reg_ptr_t   code_ptr;
    mvm_vm_ram_t       * ram;

} mvm_vm_t;

/* -- Function definitions -- */

i32 mvm_vm_init (mvm_vm_t * vm);
i32 mvm_vm_run  (mvm_vm_t * vm);
i32 mvm_vm_kill (mvm_vm_t * vm);

#endif /* #ifndef _MVM_VM_H_ */
