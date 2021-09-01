/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 11/08/2021
 . Last updated: 11/08/2021
 */

#ifndef _INST_H_
#define _INST_H_

/*
 . Instruction set
 . 
 .    Hex
 .  Opcode | Instruction Name(s)                    | Description
 . --------+----------------------------------------+-------------------------------------------
 .     00  | nop, noop, nope, np                    | No operation
 .  Data
 .     20  | ld #val, lda #val                      | Load value to a
 .     21  | ldb #val                               | Load value to b
 .     22  | ldc #val                               | Load value to c
 .     23  | laa, ldaa                              | Load data from a to a
 .     24  | lab, ldab                              | Load data from a to b
 .     25  | lac, ldac                              | Load data from a to c
 .     26  | lba, ldba                              | Load data from b to a
 .     27  | lbb, ldbb                              | Load data from b to b
 .     28  | lbc, ldbc                              | Load data from b to c
 .     29  | lca, ldca                              | Load data from c to a
 .     2A  | lcb, ldcb                              | Load data from c to b
 .     2B  | lcc, ldcc                              | Load data from c to c
 .  Logic
 .     40  | and, cmp, comp                         | Compare a to b and store result in c
 .     41  | exor, eor, xor, xo, xr                 | Exclusive-or a to b and store result in c
 .  Arithmetics
 .     60  | add, ad, sum, sm, addc, adc, sumc, smc | Add a plus b and store result in c
 .     61  | adda, ada, suma, sma                   | Add a plus b and store result in a
 .     62  | addb, adb, sumb, smb                   | Add a plus b and store result in b
 .     63  | subt, sbt, sub, sb, sbtc, subc, sbc    | Subtract a from b and store result in c
 .     64  | sbta, suba, sba                        | Subtract a from b and store result in a
 .     65  | sbtb, subb, sbb                        | Subtract a from b and store result in b
 .     66  | div, dv, divc, dvc                     | Divide a by b and store result in c
 .     67  | diva, dva                              | Divide a by b and store result in a
 .     68  | divb, dvb                              | Divide a by b and store result in b
 .     69  | mult, mlt, mul, ml, mltc, mulc, mlc    | Multiply a by b and store result in c
 .     6A  | mlta, mula, mla                        | Multiply a by b and store result in a
 .     6B  | mltb, mulb, mlb                        | Multiply a by b and store result in b
 .  Halt
 .     FF  | halt, hlt, stop, stp                   | Stop simulation
*/

enum _INST_SET {
    
    _INST_NOOP  = 0x00,

    /* Data */

    _INST_LDA   = 0x20,
    _INST_LDB   = 0x21,
    _INST_LDC   = 0x22,
    _INST_LAA   = 0x23,
    _INST_LAB   = 0x24,
    _INST_LAC   = 0x25,
    _INST_LBA   = 0x26,
    _INST_LBB   = 0x27,
    _INST_LBC   = 0x28,
    _INST_LCA   = 0x29,
    _INST_LCB   = 0x2A,
    _INST_LCC   = 0x2B,
    
    /* Logic */
    
    _INST_AND   = 0x40,
    _INST_XOR   = 0x41,

    /* Arithmetics */

    _INST_ADD   = 0x60,
    _INST_ADA   = 0x61,
    _INST_ADB   = 0x62,
    _INST_SUBT  = 0x63,
    _INST_SUBA  = 0x64,
    _INST_SUBB  = 0x65,
    _INST_DIV   = 0x66,
    _INST_DIVA  = 0x67,
    _INST_DIVB  = 0x68,
    _INST_MULT  = 0x69,
    _INST_MULA  = 0x6A,
    _INST_MULB  = 0x6B,

    /* Halt */

    _INST_HALT  = 0xFF

};

#endif /* #ifndef _INST_H */
