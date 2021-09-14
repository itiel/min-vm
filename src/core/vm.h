/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
*/

#ifndef _VM_H_
#define _VM_H_

typedef char mvm_vm_word_t;
typedef unsigned char mvm_vm_uword_t;

typedef struct mvm_reg_t {

    mvm_vm_uword_t data;

} mvm_reg_t;

typedef struct mvm_reg_group_t {
 
    mvm_reg_t * a_reg;
    mvm_reg_t * b_reg;
    mvm_reg_t * c_reg;

} mvm_reg_group_t;

typedef struct mvm_vm_t {

    mvm_reg_group_t * regs;

} mvm_vm_t;

mvm_reg_t       * mvm_reg_create ();
void            mvm_reg_delete (mvm_reg_t * reg);
mvm_reg_group_t * mvm_reg_group_create ();
void            mvm_reg_group_delete (mvm_reg_group_t * regs);
void            mvm_reg_group_debug (mvm_reg_group_t * regs);
mvm_vm_t        * mvm_vm_create ();
void            mvm_vm_delete (mvm_vm_t * vm);
void            mvm_vm_exec (mvm_reg_group_t * regs, mvm_vm_uword_t * inst);

#endif /* #ifndef _VM_H_ */
