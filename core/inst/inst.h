/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
*/

#ifndef _INST_H_
#define _INST_H_

/* -- Defines -- */

#ifndef NULL
#define NULL 0
#endif

/*
 .  Opcode | Inst Name(s)     | Description
 . --------+------------------+-------------------------------------------
 .  💤 No Operation
 .   0x00  | nop, noop, nope, | Do nothing
 .           np
 .  📝 Data
 .   0x20  | load, loda, lod, | Load value to a
 .           ld, lda 
 .   0x21  | lodb, ldb        | Load value to b
 .   0x22  | lodc, ldc        | Load value to c
 .   0x23  | laa, ldaa        | Load data from a to a
 .   0x24  | lab, ldab        | Load data from a to b
 .   0x25  | lac, ldac        | Load data from a to c
 .   0x26  | lba, ldba        | Load data from b to a
 .   0x27  | lbb, ldbb        | Load data from b to b
 .   0x28  | lbc, ldbc        | Load data from b to c
 .   0x29  | lca, ldca        | Load data from c to a
 .   0x2A  | lcb, ldcb        | Load data from c to b
 .   0x2B  | lcc, ldcc        | Load data from c to c
 .  ☑ Logic
 .   0x40  | and, cmp, comp   | Compare a to b and store result in c
 .   0x41  | exor, eor, xor,  | Exclusive-or a to b and store result in c
 .         | xo, xr
 .  ➗ Arithmetics
 .   0x60  | add, ad, sum,    | Add a plus b and store result in c
 .         | sm, addc, adc, 
 .         | sumc, smc
 .   0x61  | adda, ada, suma, | Add a plus b and store result in a
 .           sma
 .   0x62  | addb, adb, sumb, | Add a plus b and store result in b
 .           smb
 .   0x63  | subt, sbt, sub,  | Subtract a from b and store result in c
 .           sb, sbtc, subc, 
 .           sbc
 .   0x64  | sbta, suba, sba  | Subtract a from b and store result in a
 .   0x65  | sbtb, subb, sbb  | Subtract a from b and store result in b
 .   0x66  | div, dv, divc,   | Divide a by b and store result in c
 .           dvc
 .   0x67  | diva, dva        | Divide a by b and store result in a
 .   0x68  | divb, dvb        | Divide a by b and store result in b
 .   0x69  | mult, mlt, mul,  | Multiply a by b and store result in c
 .           ml, mltc, mulc, 
 .           mlc
 .   0x6A  | mlta, mula, mla  | Multiply a by b and store result in a
 .   0x6B  | mltb, mulb, mlb  | Multiply a by b and store result in b
 .  🛑 Halt
 .   0xFF  | halt, hlt, stop, | Stop simulation
 .         | stp
*/

/* -- Op Codes -- */

enum MVM_INST_OP_SET {

    // No Operation 
    
    MVM_INST_OP_NOP = 0x00,

    // Data 

    MVM_INST_OP_LDA = 0x20,
    MVM_INST_OP_LDB = 0x21,
    MVM_INST_OP_LDC = 0x22,
    MVM_INST_OP_LAA = 0x23,
    MVM_INST_OP_LAB = 0x24,
    MVM_INST_OP_LAC = 0x25,
    MVM_INST_OP_LBA = 0x26,
    MVM_INST_OP_LBB = 0x27,
    MVM_INST_OP_LBC = 0x28,
    MVM_INST_OP_LCA = 0x29,
    MVM_INST_OP_LCB = 0x2A,
    MVM_INST_OP_LCC = 0x2B,
    
    // Logic 
    
    MVM_INST_OP_AND = 0x40,
    MVM_INST_OP_XOR = 0x41,

    // Arithmetics 

    MVM_INST_OP_ADD = 0x60,
    MVM_INST_OP_ADA = 0x61,
    MVM_INST_OP_ADB = 0x62,
    MVM_INST_OP_SUB = 0x63,
    MVM_INST_OP_SBA = 0x64,
    MVM_INST_OP_SBB = 0x65,
    MVM_INST_OP_DIV = 0x66,
    MVM_INST_OP_DVA = 0x67,
    MVM_INST_OP_DVB = 0x68,
    MVM_INST_OP_MUL = 0x69,
    MVM_INST_OP_MLA = 0x6A,
    MVM_INST_OP_MLB = 0x6B,

    // Halt 

    MVM_INST_OP_HLT = 0xFF,

};

/* -- Inst Names -- */

// No Operation

char * MVM_INST_NM_NOP[] = {
    "nop","noop","nope","np", NULL
};

// Data

char * MVM_INST_NM_LDA[] = {
    "load", "loda", "lod", "ld", 
    "lda", NULL 
};
char * MVM_INST_NM_LDB[] = {
    "lodb", "ldb", NULL
};
char * MVM_INST_NM_LDC[] = {
    "lodc", "ldc", NULL
};
char * MVM_INST_NM_LAA[] = {
    "laa", "ldaa", NULL
};
char * MVM_INST_NM_LAB[] = {
    "lab", "ldab", NULL
};
char * MVM_INST_NM_LAC[] = {
    "lac", "ldac", NULL
};
char * MVM_INST_NM_LBA[] = {
    "lba", "ldba", NULL
};
char * MVM_INST_NM_LBB[] = {
    "lbb", "ldbb", NULL
};
char * MVM_INST_NM_LBC[] = {
    "lbc", "ldbc", NULL
};
char * MVM_INST_NM_LCA[] = {
    "lca", "ldca", NULL
};
char * MVM_INST_NM_LCB[] = {
    "lcb", "ldcb", NULL
};
char * MVM_INST_NM_LCC[] = {
    "lcc", "ldcc", NULL
};

// Logic

char * MVM_INST_NM_AND[] = {
    "and", "cmp", "comp", NULL
};
char * MVM_INST_NM_XOR[] = {
    "exor", "eor", "xor", "xo", 
    "xr", NULL
};

// Arithmetics

char * MVM_INST_NM_ADD[] = {
    "add", "ad", "sum", "sm", "addc", 
    "adc", "sumc", "smc", NULL
};
char * MVM_INST_NM_ADA[] = {
    "adda", "ada", "suma", "sma", NULL
};
char * MVM_INST_NM_ADB[] = {
    "addb", "adb", "sumb", "smb", NULL
};
char * MVM_INST_NM_SUB[] = {
    "subt", "sbt", "sub", "sb", 
    "sbtc", "subc", "sbc", NULL
};
char * MVM_INST_NM_SBA[] = {
    "sbta", "suba", "sba", NULL
};
char * MVM_INST_NM_SBB[] = {
    "sbtb", "subb", "sbb", NULL
};
char * MVM_INST_NM_DIV[] = {
    "div", "dv", "divc", "dvc", NULL
};
char * MVM_INST_NM_DVA[] = {
    "diva", "dva", NULL
};
char * MVM_INST_NM_DVB[] = {
    "divb", "dvb", NULL
};
char * MVM_INST_NM_MUL[] = {
    "mult", "mlt", "mul", "ml", 
    "mltc", "mulc", "mlc", NULL
};
char * MVM_INST_NM_MLA[] = {
    "mlta", "mula", "mla", NULL
};
char * MVM_INST_NM_MLB[] = {
    "mltb", "mulb", "mlb", NULL
};

// Halt

char * MVM_INST_NM_HLT[] = {
    "halt", "hlt", "stop", "stp", NULL
};

char ** MVM_INST_NM_LIST[] = {
    // No Operation

    MVM_INST_NM_NOP,

    // Data

    MVM_INST_NM_LDA,
    MVM_INST_NM_LDB,
    MVM_INST_NM_LDC,
    MVM_INST_NM_LAA,
    MVM_INST_NM_LAB,
    MVM_INST_NM_LAC,
    MVM_INST_NM_LBA,
    MVM_INST_NM_LBB,
    MVM_INST_NM_LBC,
    MVM_INST_NM_LCA,
    MVM_INST_NM_LCB,
    MVM_INST_NM_LCC,

    // Logic

    MVM_INST_NM_AND,
    MVM_INST_NM_XOR,

    // Arithmetics

    MVM_INST_NM_ADD,
    MVM_INST_NM_ADA,
    MVM_INST_NM_ADB,
    MVM_INST_NM_SUB,
    MVM_INST_NM_SBA,
    MVM_INST_NM_SBB,
    MVM_INST_NM_DIV,
    MVM_INST_NM_DVA,
    MVM_INST_NM_DVB,
    MVM_INST_NM_MUL,
    MVM_INST_NM_MLA,
    MVM_INST_NM_MLB,

    // Halt

    MVM_INST_NM_HLT,

    NULL
};

#endif /* #ifndef MVM_INST_OP_H */
