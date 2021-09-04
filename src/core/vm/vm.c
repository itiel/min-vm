/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 29/07/2021
*/

#include <stdlib.h>
#include <stdio.h>

#include <core/inst.h>
#include "vm.h"

minvm_Register * minvm_Register_Create () {

    return malloc(sizeof(minvm_Register));

}

void minvm_Register_Delete (minvm_Register * reg) {

    free(reg);

    return;

}

minvm_RegisterGroup * minvm_RegisterGroup_Create () {

    minvm_RegisterGroup * regs = malloc(sizeof(minvm_RegisterGroup));

    regs->a_reg = minvm_Register_Create();
    regs->b_reg = minvm_Register_Create();
    regs->c_reg = minvm_Register_Create();

    return regs;

}

void minvm_RegisterGroup_Delete (minvm_RegisterGroup * regs) {

    minvm_Register_Delete(regs->a_reg);
    minvm_Register_Delete(regs->b_reg);
    minvm_Register_Delete(regs->c_reg);

    free(regs);

    return;

}

void minvm_RegisterGroup_Debug (minvm_RegisterGroup * regs) {

    printf(" - Debugging - \n");
    printf("    reg a: %d\n", regs->a_reg->data);
    printf("    reg b: %d\n", regs->b_reg->data);
    printf("    reg c: %d\n", regs->c_reg->data);
    printf("\n");

    return;

}

minvm_VM * minvm_VM_Create () {

    minvm_VM * vm = malloc(sizeof(minvm_VM));

    vm->regs = minvm_RegisterGroup_Create();
 
    return vm;
}

void minvm_VM_Delete (minvm_VM * vm) {

    minvm_RegisterGroup_Delete(vm->regs);

    free(vm);

    return;
}

void minvm_VM_ExecuteInstruction (minvm_RegisterGroup * regs, minvm_UnsWord * inst) {

    switch (inst[0]) {

        /* No operation */ 

        case MVM_INST_OP_NOOP: /* nop */ 
        default:
            break;

        /* Data */
 
        case MVM_INST_OP_LDA: /* ld #val */
            regs->a_reg->data = inst[1];
            break;
        case MVM_INST_OP_LDB: /* ldb #val */
            regs->b_reg->data = inst[1];
            break;
        case MVM_INST_OP_LDC: /* ldc #val */
            regs->c_reg->data = inst[1];
            break;
        case MVM_INST_OP_LAA: /* laa */
            regs->a_reg->data = regs->a_reg->data;
            break;
        case MVM_INST_OP_LAB: /* lab */
            regs->a_reg->data = regs->b_reg->data;
            break;
        case MVM_INST_OP_LAC: /* lac */
            regs->a_reg->data = regs->c_reg->data;
            break;
        case MVM_INST_OP_LBA: /* lba */
            regs->b_reg->data = regs->a_reg->data;
            break;
        case MVM_INST_OP_LBB: /* lbb */
            regs->b_reg->data = regs->b_reg->data;
            break;
        case MVM_INST_OP_LBC: /* lbc */
            regs->b_reg->data = regs->c_reg->data;
            break;
        case MVM_INST_OP_LCA: /* lca */
            regs->c_reg->data = regs->a_reg->data;
            break;
        case MVM_INST_OP_LCB: /* lcb */
            regs->c_reg->data = regs->b_reg->data;
            break;
        case MVM_INST_OP_LCC: /* lcc */
            regs->c_reg->data = regs->c_reg->data;
            break;

        /* Logic */
 
        case MVM_INST_OP_AND: /* and */
            regs->c_reg->data = regs->a_reg->data == regs->b_reg->data;
            break;
        case MVM_INST_OP_XOR: /* xor */
            regs->c_reg->data = regs->a_reg->data ^ regs->b_reg->data;
            break;
 
        /* Arithmetics */
 
        case MVM_INST_OP_ADD: /* add */
            regs->c_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case MVM_INST_OP_ADA: /* adda */
            regs->a_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case MVM_INST_OP_ADB: /* addb */
            regs->b_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case MVM_INST_OP_SUBT: /* subt */
            regs->c_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case MVM_INST_OP_SUBA: /* sbta */
            regs->a_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case MVM_INST_OP_SUBB: /* sbtb */
            regs->b_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case MVM_INST_OP_DIV: /* div */
            regs->c_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case MVM_INST_OP_DIVA: /* diva */
            regs->a_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case MVM_INST_OP_DIVB: /* divb */
            regs->b_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case MVM_INST_OP_MULT: /* mult */
            regs->c_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;
        case MVM_INST_OP_MULA: /* mlta */
            regs->a_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;
        case MVM_INST_OP_MULB: /* mltb */
            regs->b_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;

        /* Halt */
 
        case MVM_INST_OP_HALT: 
            /* Stop simulation */
            break;
    }

    return;
}
