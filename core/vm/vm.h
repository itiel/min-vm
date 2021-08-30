/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
 . Last updated: 11/08/2021
 */

#ifndef _VM_H_
#define _VM_H_

typedef char minvm_Word;
typedef unsigned char minvm_UnsWord;

typedef struct minvm_Register {

    minvm_Word data;

} minvm_Register;

typedef struct minvm_RegisterGroup {
    
    minvm_Register * a_reg;
    minvm_Register * b_reg;
    minvm_Register * c_reg;

} minvm_RegisterGroup;

typedef struct minvm_VM {

    minvm_RegisterGroup * regs;

} minvm_VM;

minvm_Register * minvm_Register_Create ();

void minvm_Register_Delete (minvm_Register * reg);

minvm_RegisterGroup * minvm_RegisterGroup_Create ();

void minvm_RegisterGroup_Delete (minvm_RegisterGroup * regs);

void minvm_RegisterGroup_Debug (minvm_RegisterGroup * regs);

minvm_VM * minvm_VM_Create () ;

void minvm_VM_Delete (minvm_VM * vm);

void minvm_VM_ExecuteInstruction (minvm_RegisterGroup * regs, minvm_UnsWord * inst);

#endif /* #ifndef _VM_H_ */