/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 15/09/2021
*/

#ifndef _MVM_VM_REG_H_
#define _MVM_VM_REG_H_

/* -- Includes -- */

#include <util/fwn.h>

/* -- Type Definitions -- */

typedef struct mvm_vm_reg_t {

    u8 buffer;

} mvm_vm_reg_t;

typedef struct mvm_vm_regs_main_t {
    
    mvm_vm_reg_t a;
    mvm_vm_reg_t b;
    mvm_vm_reg_t c;

} mvm_vm_regs_main_t;

typedef struct mvm_vm_reg_ptr_t {
    
    mvm_vm_reg_t seg;
    mvm_vm_reg_t off;

} mvm_vm_reg_ptr_t;

#endif /* #ifndef _MVM_VM_REG_H_ */
