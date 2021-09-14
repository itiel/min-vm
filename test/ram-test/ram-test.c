#include <core/vm/ram.h>

int main () {

    mvm_vm_ram_t ram_instance;

    mvm_vm_ram_init(&ram_instance);

    for (int i = 0; i < '~' + 1; ++i) {
        ram_instance.buffer[i] = i;
    }

    ram_instance.buffer[0xFFFF] = 'P';

    mvm_vm_ram_dump(&ram_instance);

    mvm_vm_ram_kill(&ram_instance); 
    
    return 0;

}