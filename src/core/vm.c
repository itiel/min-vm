/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 29/07/2021
*/

#include <core/vm.h>
#include <core/inst.h>

#include <stdlib.h>
#include <stdio.h>

mvm_reg_t * mvm_reg_create () {

    return malloc(sizeof(mvm_reg_t));

}

void mvm_reg_delete (mvm_reg_t * reg) {

    free(reg);

    return;

}

mvm_reg_group_t * mvm_reg_group_create () {

    mvm_reg_group_t * regs = malloc(sizeof(mvm_reg_group_t));

    regs->a_reg = mvm_reg_create();
    regs->b_reg = mvm_reg_create();
    regs->c_reg = mvm_reg_create();

    return regs;

}

void mvm_reg_group_delete (mvm_reg_group_t * regs) {

    mvm_reg_delete(regs->a_reg);
    mvm_reg_delete(regs->b_reg);
    mvm_reg_delete(regs->c_reg);

    free(regs);

    return;

}

void mvm_reg_group_debug (mvm_reg_group_t * regs) {

    printf(" - Debugging - \n");
    printf("    reg a: %d\n", regs->a_reg->data);
    printf("    reg b: %d\n", regs->b_reg->data);
    printf("    reg c: %d\n", regs->c_reg->data);
    printf("\n");

    return;

}

mvm_vm_t * mvm_vm_create () {

    mvm_vm_t * vm = malloc(sizeof(mvm_vm_t));

    vm->regs = mvm_reg_group_create();
 
    return vm;
}

void mvm_vm_delete (mvm_vm_t * vm) {

    mvm_reg_group_delete(vm->regs);

    free(vm);

    return;
}

void mvm_vm_exec (mvm_reg_group_t * regs, mvm_vm_uword_t * inst) {

    

    return;
}
