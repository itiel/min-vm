<!---
Author: Itiel Lopez - itiel@soyitiel.com
Created: 05/08/2021
-->

> :warning: **Warning:** Most of this document is a draft. May contain inaccurate information. Read with caution.

# Welcome to min-vm

An experimental VM hand-crafted with love. :heart:

* [Leer este documento en español :mexico:](readmes/LEEME.md)

## :star2: Intro

> Please excuse my english, it isn't my first language. Thank you. :pray:

**min-vm** represents my own attempt :muscle: at understanding the subject of virtual machines. 

I had heard about systems that function on their own VMs (like Java :coffee: or Python :snake:, and I think V8 or Node :man_shrugging: idk), but I hadn't really understood how or why that was, nor did I really care. But then I found about people who wrote their own **OS** or **kernel**, some who wrote their own **VM** or **assembler**, and some even built their own **physical CPUs on breadboards** (what⁉). Now, ***that*** got me interested. It was as if, now that I knew a mere mortal like me could do something like that with such little requirements, then I ***should*** do it too.

So, *welcome to The Internet, have a look around*. :notes::sunglasses:

## :gear: The VM

[:construction: Some description]

### :dna: The Instruction Set

By convention, instruction names are at least 2 and not more than 4 characters long.

The following is a list of instructions the assembler is (or will be) able to interpret.

<!---
 Opcode | Inst Name(s)     | Description
--------+------------------+-------------------------------------------
 💤 No Operation
  0x00  | nop, noop, nope, | Do nothing
          np
 📝 Data
  0x20  | load, loda, lod, | Load value to a
          ld, lda 
  0x21  | lodb, ldb        | Load value to b
  0x22  | lodc, ldc        | Load value to c
  0x23  | laa, ldaa        | Load data from a to a
  0x24  | lab, ldab        | Load data from a to b
  0x25  | lac, ldac        | Load data from a to c
  0x26  | lba, ldba        | Load data from b to a
  0x27  | lbb, ldbb        | Load data from b to b
  0x28  | lbc, ldbc        | Load data from b to c
  0x29  | lca, ldca        | Load data from c to a
  0x2A  | lcb, ldcb        | Load data from c to b
  0x2B  | lcc, ldcc        | Load data from c to c
 ☑ Logic
  0x40  | and, cmp, comp   | Compare a to b and store result in c
  0x41  | exor, eor, xor,  | Exclusive-or a to b and store result in c
        | xo, xr
 ➗ Arithmetics
  0x60  | add, ad, sum,    | Add a plus b and store result in c
        | sm, addc, adc, 
        | sumc, smc
  0x61  | adda, ada, suma, | Add a plus b and store result in a
          sma
  0x62  | addb, adb, sumb, | Add a plus b and store result in b
          smb
  0x63  | subt, sbt, sub,  | Subtract a from b and store result in c
          sb, sbtc, subc, 
          sbc
  0x64  | sbta, suba, sba  | Subtract a from b and store result in a
  0x65  | sbtb, subb, sbb  | Subtract a from b and store result in b
  0x66  | div, dv, divc,   | Divide a by b and store result in c
          dvc
  0x67  | diva, dva        | Divide a by b and store result in a
  0x68  | divb, dvb        | Divide a by b and store result in b
  0x69  | mult, mlt, mul,  | Multiply a by b and store result in c
          ml, mltc, mulc, 
          mlc
  0x6A  | mlta, mula, mla  | Multiply a by b and store result in a
  0x6B  | mltb, mulb, mlb  | Multiply a by b and store result in b
 🛑 Halt
  0xFF  | halt, hlt, stop, | Stop simulation
        | stp
-->

<table>
    <thead>
        <tr>
            <th>Opcode</th>
            <th>Inst Name(s)</th>
            <th>Arg(s)</th>
            <th>Description</th>
        </tr>
    </thead>
    <thead>
        <tr>
            <th colspan="4">
                <em>:zzz: No Operation</em>
            </th>
        </tr>
    </thead>
    <tr>
        <td align="center">
            <code>0x00</code>
        </td>
        <td>
            <code>nop</code>, 
            <code>noop</code>, 
            <code>nope</code>, 
            <code>np</code>
        </td>
        <td align="center">-</td>
        <td>Do nothing</td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:pencil: Data</em>
            </th>
        </tr>
    </thead>
    <tr>
        <td align="center">
            <code>0x20</code>
        </td>
        <td>
            <code>load</code>, 
            <code>loda</code>,
            <code>lod</code>, 
            <code>ld</code>,
            <br> 
            <code>lda</code>, 
        </td>
        <td align="center">
            <code>data</code>
        </td>
        <td>
            Load data to <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x21</code>
        </td>
        <td>
            <code>lodb</code>, 
            <code>ldb</code>
        </td>
        <td align="center">
            <code>data</code>
        </td>
        <td>
            Load data to <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x22</code>
        </td>
        <td>
            <code>lodc</code>, 
            <code>ldc</code>
        </td>
        <td align="center">
            <code>data</code>
        </td>
        <td>
            Load data to <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x23</code>
        </td>
        <td>
            <code>laa</code>,
            <code>ldaa</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>a</em></strong> to <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x24</code>
        </td>
        <td>
            <code>lab</code>,
            <code>ldab</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>a</em></strong> to <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x25</code>
        </td>
        <td>
            <code>lac</code>,
            <code>ldac</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>a</em></strong> to <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x26</code>
        </td>
        <td>
            <code>lba</code>,
            <code>ldba</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>b</em></strong> to <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x27</code>
        </td>
        <td>
            <code>lbb</code>,
            <code>ldbb</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>b</em></strong> to <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x28</code>
        </td>
        <td>
            <code>lbc</code>,
            <code>ldbc</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>b</em></strong> to <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x29</code>
        </td>
        <td>
            <code>lca</code>,
            <code>ldca</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>c</em></strong> to <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x2A</code>
        </td>
        <td>
            <code>lcb</code>,
            <code>ldcb</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>c</em></strong> to <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x2B</code>
        </td>
        <td>
            <code>lcc</code>,
            <code>ldcc</code>
        </td>
        <td align="center">-</td>
        <td>
            Load data from <strong><em>c</em></strong> to <strong><em>c</em></strong>
        </td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:ballot_box_with_check: Logic</em>
            </th>
        </tr>
    </thead>
    <tr>
        <td align="center">
            <code>0x40</code>
        </td>
        <td>
            <code>and</code>,
            <code>cmp</code>,
            <code>comp</code>
        </td>
        <td align="center">-</td>
        <td>
            Compare <strong><em>a</em></strong> to <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x41</code>
        </td>
        <td>
            <code>exor</code>,
            <code>eor</code>,
            <code>xor</code>,
            <code>xo</code>,
            <br>
            <code>xr</code>
        </td>
        <td align="center">-</td>
        <td>
            <em>Exclusive-or</em> <strong><em>a</em></strong> to <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:heavy_division_sign: Arithmetics</em>
            </th>
        </tr>
    </thead>
    <tr>
        <td align="center">
            <code>0x60</code>
        </td>
        <td>
            <code>add</code>,
            <code>ad</code>,
            <code>sum</code>,
            <code>sm</code>,
            <br>
            <code>addc</code>,
            <code>adc</code>,
            <code>sumc</code>,
            <code>smc</code>
        </td>
        <td align="center">-</td>
        <td>
            Add <strong><em>a</em></strong> plus <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x61</code>
        </td>
        <td>
            <code>adda</code>, 
            <code>ada</code>, 
            <code>suma</code>, 
            <code>sma</code>
        </td>
        <td align="center">-</td>
        <td>
            Add <strong><em>a</em></strong> plus <strong><em>b</em></strong> and store result in <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x62</code>
        </td>
        <td>
            <code>addb</code>, 
            <code>adb</code>, 
            <code>sumb</code>, 
            <code>smb</code>
        </td>
        <td align="center">-</td>
        <td>
            Add <strong><em>a</em></strong> plus <strong><em>b</em></strong> and store result in <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x63</code>
        </td>
        <td>
            <code>subt</code>, 
            <code>sbt</code>, 
            <code>sub</code>,
            <code>sb</code>, 
            <br> 
            <code>sbtc</code>, 
            <code>subc</code>, 
            <code>sbc</code>
        </td>
        <td align="center">-</td>
        <td>
            Subtract <strong><em>a</em></strong> from <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x64</code>
        </td>
        <td>
            <code>sbta</code>, 
            <code>suba</code>, 
            <code>sba</code>
        </td>
        <td align="center">-</td>
        <td>
            Subtract <strong><em>a</em></strong> from <strong><em>b</em></strong> and store result in <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x65</code>
        </td>
        <td>
            <code>sbtb</code>, 
            <code>subb</code>, 
            <code>sbb</code>
        </td>
        <td align="center">-</td>
        <td>
            Subtract <strong><em>a</em></strong> from <strong><em>b</em></strong> and store result in <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x66</code>
        </td>
        <td>
            <code>div</code>, 
            <code>dv</code>, 
            <code>divc</code>, 
            <code>dvc</code>
        </td>
        <td align="center">-</td>
        <td>
            Divide <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x67</code>
        </td>
        <td>
            <code>diva</code>, 
            <code>dva</code>
        </td>
        <td align="center">-</td>
        <td>
            Divide <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x68</code>
        </td>
        <td>
            <code>divb</code>, 
            <code>dvb</code>
        </td>
        <td align="center">-</td>
        <td>
            Divide <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>b</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x69</code>
        </td>
        <td>
            <code>mult</code>, 
            <code>mlt</code>, 
            <code>mul</code>, 
            <code>ml</code>, 
            <br>
            <code>mltc</code>, 
            <code>mulc</code>, 
            <code>mlc</code>
        </td>
        <td align="center">-</td>
        <td>
            Multiply <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>c</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x6A</code>
        </td>
        <td>
            <code>mlta</code>, 
            <code>mula</code>, 
            <code>mla</code>
        </td>
        <td align="center">-</td>
        <td>
            Multiply <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>a</em></strong>
        </td>
    </tr>
    <tr>
        <td align="center">
            <code>0x6B</code>
        </td>
        <td>
            <code>mltb</code>, 
            <code>mulb</code>, 
            <code>mlb</code>
        </td>
        <td align="center">-</td>
        <td>
            Multiply <strong><em>a</em></strong> by <strong><em>b</em></strong> and store result in <strong><em>b</em></strong>
        </td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:stop_sign: Halt</em>
            </th>
        </tr>
    </thead>
    <tr>
        <td align="center">
            <code>0xFF</code>
        </td>
        <td>
            <code>halt</code>, 
            <code>hlt</code>, 
            <code>stop</code>, 
            <code>stp</code>
        </td>
        <td align="center">-</td>
        <td>
            Stop simulation
        </td>
    </tr>
</table>

## :writing_hand: The compiler

Technically an assembler, not a compiler, but it sounds *way cooler*. :sunglasses: 

## :books: Useful References

[:construction: Some description]

### :sparkles: Sources of Inspiration

[:construction: Some description]
