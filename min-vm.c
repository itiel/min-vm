#include <stdlib.h>
#include <stdio.h>

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

/*
 . Instruction set
 .
 HEX | ASM                                    | DESC
-----+----------------------------------------+-------------------------------------------
  00 | nop, noop, nope                        | no operation
 Data
  20 | ld #val, lda #val                      | load value to a
  21 | ldb #val                               | load value to b
  22 | ldc #val                               | load value to c
  23 | laa, ldaa                              | load data from a to a
  24 | lab, ldab                              | load data from a to b
  25 | lac, ldac                              | load data from a to c
  26 | lba, ldba                              | load data from b to a
  27 | lbb, ldbb                              | load data from b to b
  28 | lbc, ldbc                              | load data from b to c
  29 | lca, ldca                              | load data from c to a
  2A | lcb, ldcb                              | load data from c to b
  2B | lcc, ldcc                              | load data from c to c
 Logic
  40 | and, cmp, comp                         | compare a to b and store result in c
  41 | xor                                    | exclusive-or a to b and store result in c
 Arithmetics
  60 | add, ad, sum, sm, addc, adc, sumc, smc | add a plus b and store result in c
  61 | adda, ada, suma, sma                   | add a plus b and store result in a
  62 | addb, adb, sumb, smb                   | add a plus b and store result in b
  63 | subt, sbt, sub, sb, sbtc, subc, sbc    | subtract a from b and store result in c
  64 | sbta, suba, sba                        | subtract a from b and store result in a
  65 | sbtb, subb, sbb                        | subtract a from b and store result in b
  66 | div, dv, divc, dvc                     | divide a by b and store result in c
  67 | diva, dva                              | divide a by b and store result in a
  68 | divb, dvb                              | divide a by b and store result in b
  69 | mult, mlt, mul, ml, mltc, mulc, mlc    | multiply a by b and store result in c
  6A | mlta, mula, mla                        | multiply a by b and store result in a
  6B | mltb, mulb, mlb                        | multiply a by b and store result in b
 Halt
  FF | hlt, halt      | stop simulation
*/

void minvm_VM_ExecuteInstruction (minvm_RegisterGroup * regs, minvm_UnsWord * inst) {

    switch (inst[0]) {

        /* No operation */ 

        case 0x00: /* nop */ 
        default:
            break;

        /* Data */
        
        case 0x20: /* ld #val */
            regs->a_reg->data = inst[1];
            break;
        case 0x21: /* ldb #val */
            regs->b_reg->data = inst[1];
            break;
        case 0x22: /* ldc #val */
            regs->c_reg->data = inst[1];
            break;
        case 0x23: /* laa */
            regs->a_reg->data = regs->a_reg->data;
            break;
        case 0x24: /* lab */
            regs->a_reg->data = regs->b_reg->data;
            break;
        case 0x25: /* lac */
            regs->a_reg->data = regs->c_reg->data;
            break;
        case 0x26: /* lba */
            regs->b_reg->data = regs->a_reg->data;
            break;
        case 0x27: /* lbb */
            regs->b_reg->data = regs->b_reg->data;
            break;
        case 0x28: /* lbc */
            regs->b_reg->data = regs->c_reg->data;
            break;
        case 0x29: /* lca */
            regs->c_reg->data = regs->a_reg->data;
            break;
        case 0x2A: /* lcb */
            regs->c_reg->data = regs->b_reg->data;
            break;
        case 0x2B: /* lcc */
            regs->c_reg->data = regs->c_reg->data;
            break;

        /* Logic */
        
        case 0x40: /* and */
            regs->c_reg->data = regs->a_reg->data == regs->b_reg->data;
            break;
        case 0x41: /* xor */
            regs->c_reg->data = regs->a_reg->data ^ regs->b_reg->data;
            break;
        
        /* Arithmetics */
        
        case 0x60: /* add */
            regs->c_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case 0x61: /* adda */
            regs->a_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case 0x62: /* addb */
            regs->b_reg->data = regs->a_reg->data + regs->b_reg->data;
            break;
        case 0x63: /* subt */
            regs->c_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case 0x64: /* sbta */
            regs->a_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case 0x65: /* sbtb */
            regs->b_reg->data = regs->b_reg->data - regs->a_reg->data;
            break;
        case 0x66: /* div */
            regs->c_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case 0x67: /* diva */
            regs->a_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case 0x68: /* divb */
            regs->b_reg->data = regs->a_reg->data / regs->b_reg->data;
            break;
        case 0x69: /* mult */
            regs->c_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;
        case 0x6A: /* mlta */
            regs->a_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;
        case 0x6B: /* mltb */
            regs->b_reg->data = regs->a_reg->data * regs->b_reg->data;
            break;

        /* Halt */
        
        case 0xFF: 
            /* Stop simulation */
            break;
    }

    return;
}

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