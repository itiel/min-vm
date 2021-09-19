/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 29/07/2021
*/

/* -- Includes -- */

#include <stdio.h>
#include <stdlib.h>

#include <core/vm.h>
#include <core/inst.h>

#include <util/fwn.h>
#include <util/err.h>
#include <util/bool.h>

/* -- Function definitions -- */

i32 mvm_vm_init (mvm_vm_t * vm) {

    if (!vm) {

        put_error_method(
            "mvm_vm_init",
            "VM pointer should not be NULL."
        );

        return FALSE;

    }

    if (!(vm->ram = malloc(sizeof(mvm_vm_ram_t)))) {

        put_error_method(
            "mvm_vm_init",
            "Something unexpected happened while allocating memory for VM's RAM."
        );

        return FALSE;

    }

    if (!mvm_vm_ram_init(vm->ram)) {

        put_error_method(
            "mvm_vm_init",
            "Something unexpected happened while initializing RAM."
        );

        return FALSE;

    }

    return TRUE;

}

i32 mvm_vm_run (mvm_vm_t * vm) {

    if (!vm) {

        put_error_method(
            "mvm_vm_run",
            "VM pointer should not be NULL."
        );

        return FALSE;

    }

    return TRUE;

}

i32 mvm_vm_kill (mvm_vm_t * vm) {

    if (!vm) {

        put_error_method(
            "mvm_vm_kill",
            "VM pointer should not be NULL."
        );

        return FALSE;

    }

    mvm_vm_ram_kill(vm->ram); 

    return TRUE;

}

i32 mvm_vm_exec (mvm_vm_t * vm, mvm_uword_t inst) {

    return TRUE;

}
