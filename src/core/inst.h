/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
*/

#ifndef _MVM_INST_H_
#define _MVM_INST_H_

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

/* -- Includes -- */

#include <util/fwn.h>
#include <util/null.h>
#include <util/strcmp-s.h>

/* -- Types -- */

typedef struct mvm_inst_t {
    const u32 op;
    const i8  ** names;
} mvm_inst_t;

/*
 . `_mvm_inst_def()`
 . 
 . Defines an instruction's data (name, OP Code & 
 . name representation list) in separate variables and 
 . in a `mvm_inst_t` variable.
 . 
 . The nomenclature is as follows (`INS` being the 
 . instruction's name, which should preferably be
 . 3 characters long):
 . 
 .     - OP Code:       `MVM_INST_OP_INS` (32 int)
 .     - Name reprs:    `MVM_INST_NM_INS` (string list)
 .     - Inst type var: `MVM_INST_INS`
 . 
 . All arguments after the second are part of name 
 . representation list. The last one should be a `NULL`
 . pointer to help with looping.
 . 
 . Example use:
 . 
 .     _mvm_inst_def(LDB, 0x21, "lodb", "ldb", NULL);
 .         => 
 .             MVM_INST_OP_LDB = 0x21
 .             MVM_INST_NM_LDB = { "lodb", "ldb", NULL }
 .             MVM_INST_LDB = { 
 .                 MVM_INST_OP_LDB, 
 .                 MVM_INST_NM_LDB 
 .             }
 . 
 .     _mvm_inst_def(NUL, 0xFFFFFFFF, NULL);
 .         => 
 .             MVM_INST_OP_NUL = 0xFFFFFFFF
 .             MVM_INST_NM_NUL = { NULL }
 .             MVM_INST_NUL = { 
 .                 MVM_INST_OP_NUL, 
 .                 MVM_INST_NM_NUL 
 .             }
 . 
*/

#define _mvm_inst_def(_name, _op, _namelist...) \
    const u32 MVM_INST_OP_##_name = _op;        \
    const i8 * MVM_INST_NM_##_name[] = {        \
        _namelist                               \
    };                                          \
    const mvm_inst_t MVM_INST_##_name = {       \
        MVM_INST_OP_##_name,                    \
        MVM_INST_NM_##_name                     \
    };

/* -- Instruction Definitions -- */

// Inst name max length 

#define MVM_INST_NM_MAXLEN 4

// No Operation

_mvm_inst_def(NOP, 0x00, 
    "nop", "noop", "nope", "np", NULL);

// Data

_mvm_inst_def(LDA, 0x20, 
    "load", "loda", "lod", "ld", "lda", NULL);
_mvm_inst_def(LDB, 0x21, 
    "lodb", "ldb", NULL);
_mvm_inst_def(LDC, 0x22, 
    "lodc", "ldc", NULL);
_mvm_inst_def(LAA, 0x23, 
    "laa", "ldaa", NULL);
_mvm_inst_def(LAB, 0x24, 
    "lab", "ldab", NULL);
_mvm_inst_def(LAC, 0x25, 
    "lac", "ldac", NULL);
_mvm_inst_def(LBA, 0x26, 
    "lba", "ldba", NULL);
_mvm_inst_def(LBB, 0x27, 
    "lbb", "ldbb", NULL);
_mvm_inst_def(LBC, 0x28, 
    "lbc", "ldbc", NULL);
_mvm_inst_def(LCA, 0x29, 
    "lca", "ldca", NULL);
_mvm_inst_def(LCB, 0x2A, 
    "lcb", "ldcb", NULL);
_mvm_inst_def(LCC, 0x2B, 
    "lcc", "ldcc", NULL);
 
// Logic 

_mvm_inst_def(AND, 0x40, 
    "and", "cmp", "comp", NULL);
_mvm_inst_def(XOR, 0x41, 
    "exor", "eor", "xor", "xo", "xr", NULL);

// Arithmetics 

_mvm_inst_def(ADD, 0x60, 
    "add", "ad", "sum", "sm", "addc", "adc", 
    "sumc", "smc", NULL);
_mvm_inst_def(ADA, 0x61, 
    "adda", "ada", "suma", "sma", NULL);
_mvm_inst_def(ADB, 0x62, 
    "addb", "adb", "sumb", "smb", NULL);
_mvm_inst_def(SUB, 0x63, 
    "subt", "sbt", "sub", "sb", "sbtc", "subc", 
    "sbc", NULL);
_mvm_inst_def(SBA, 0x64, 
    "sbta", "suba", "sba", NULL);
_mvm_inst_def(SBB, 0x65, 
    "sbtb", "subb", "sbb", NULL);
_mvm_inst_def(DIV, 0x66, 
    "div", "dv", "divc", "dvc", NULL);
_mvm_inst_def(DVA, 0x67, 
    "diva", "dva", NULL);
_mvm_inst_def(DVB, 0x68, 
    "divb", "dvb", NULL);
_mvm_inst_def(MUL, 0x69, 
    "mult", "mlt", "mul", "ml", "mltc", "mulc", 
    "mlc", NULL);
_mvm_inst_def(MLA, 0x6A, 
    "mlta", "mula", "mla", NULL);
_mvm_inst_def(MLB, 0x6B, 
    "mltb", "mulb", "mlb", NULL);

// Halt 

_mvm_inst_def(HLT, 0xFF, 
    "halt", "hlt", "stop", "stp", NULL);

// No valid OP Code (`MVM_INST_NUL`)

_mvm_inst_def(NUL, 0xFFFFFFFF, NULL);

/* -- Instruction Set -- */

/*
 . `MVM_INST_SET`
 . 
 . Should contain all of the instructions above,
 . except for `MVM_INST_NUL`, and end with a `NULL`
 . pointer to help with looping. 
*/

const mvm_inst_t * MVM_INST_SET[] = {

    // No Operation

    &MVM_INST_NOP,

     // Data
 
    &MVM_INST_LDA,
    &MVM_INST_LDB,
    &MVM_INST_LDC,
    &MVM_INST_LAA,
    &MVM_INST_LAB,
    &MVM_INST_LAC,
    &MVM_INST_LBA,
    &MVM_INST_LBB,
    &MVM_INST_LBC,
    &MVM_INST_LCA,
    &MVM_INST_LCB,
    &MVM_INST_LCC, 

    // Logic
 
    &MVM_INST_AND,
    &MVM_INST_XOR, 

    // Arithmetics
 
    &MVM_INST_ADD,
    &MVM_INST_ADA,
    &MVM_INST_ADB,
    &MVM_INST_SUB,
    &MVM_INST_SBA,
    &MVM_INST_SBB,
    &MVM_INST_DIV,
    &MVM_INST_DVA,
    &MVM_INST_DVB,
    &MVM_INST_MUL,
    &MVM_INST_MLA,
    &MVM_INST_MLB, 

    // Halt
 
    &MVM_INST_HLT,

    // Null pointer

    NULL

};

/*
 . `mvm_inst_op_find()`
 . 
 . A type of hash func that checks if string matches 
 . an instruction's name representation and returns its 
 . OP Code. If the string doesn't match any instruction, 
 . returns `MVM_INST_OP_NUL`. Case insensitive.
*/

u32 mvm_inst_op_find (i8 * inst_name) {

    for (int i = 0; MVM_INST_SET[i]; ++i) {
 
        for (int j = 0; MVM_INST_SET[i]->names[j]; ++j) {

            if (strcmp_case_s(
                inst_name, 
                (i8 *) MVM_INST_SET[i]->names[j],
                MVM_INST_NM_MAXLEN + 1)) 
            { 

                return MVM_INST_SET[i]->op;
 
            }

        }
 
    }

    return MVM_INST_OP_NUL;

}

#endif /* #ifndef MVM_INST_OP_H */
