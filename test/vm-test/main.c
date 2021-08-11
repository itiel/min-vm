/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
 . Last updated: 11/08/2021
 */

#include "../../min-vm/vm.h"

int main (int argc, char const ** argv) {
    
    minvm_VM * vm = minvm_VM_Create();
    minvm_UnsWord inst[2];

    /* Load the value of 1 to a */
    
    inst[0] = 0x20;
    inst[1] = 1;

    minvm_VM_ExecuteInstruction(vm->regs, (minvm_UnsWord *) inst);

    /* Load the value of 5 to b */
    
    inst[0] = 0x21;
    inst[1] = 5;
    
    minvm_VM_ExecuteInstruction(vm->regs, (minvm_UnsWord *) inst);

    /* Show the values in regs a to c */
    
    minvm_RegisterGroup_Debug(vm->regs);

    /* Add a plus b and store the result in c */
    
    inst[0] = 0x60;

    minvm_VM_ExecuteInstruction(vm->regs, (minvm_UnsWord *) inst);

    /* Show the values in regs a to c */

    minvm_RegisterGroup_Debug(vm->regs);

    /* Do nothing */
    
    inst[0] = 0x00;

    minvm_VM_ExecuteInstruction(vm->regs, (minvm_UnsWord *) inst);

    /* Stop simulation */
    
    inst[0] = 0xFF;

    minvm_VM_ExecuteInstruction(vm->regs, (minvm_UnsWord *) inst);

    /* Deallocate memory used by vm */

    minvm_VM_Delete(vm);

    return 0;
}
