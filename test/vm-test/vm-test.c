/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 16/09/2021
*/

#include <stdio.h>

#include <core/vm.h>

#include <util/err.h>

int main () {

    mvm_vm_t vm;

    if (!mvm_vm_init(&vm)) {
        
        put_error_method( 
            "main", 
            "Something unexpected happened while initializing VM instance." 
        );

        mvm_vm_kill(&vm);

        return 1;
    
    }

    if (!mvm_vm_run(&vm)) {
        
        put_error_method( 
            "main", 
            "Something unexpected happened while trying to run VM instance." 
        );

        mvm_vm_kill(&vm);

        return 1;
    
    }

    mvm_vm_kill(&vm);

    return 0;

}
