[//]: # (Author: Itiel Lopez - itiel@soyitiel.com)
[//]: # (Created: 05/08/2021)
[//]: # (Last updated: 11/08/2021)

# Welcome to min-vm
An experimental VM hand-crafted with love. ❤

## Intro 🌟

(Please excuse my english, it isn't my first language. 🙏)

**min-vm** represents my own attempt 💪 at understanding the subject of vitual machines. 

I had heard about systems that function on their own VMs (like Java ☕ or Python 🐍), but I hadn't really understood how or why that was, nor did I really care. But then I found some examples of individuals who built their own physical CPUs on breadboards or wrote their own custom VMs in C or something. *That's when* I got interested. It was as if, now that I knew a mere mortal like me could do something like that with such little requirements, then I ***should*** do it too. 

Also, I find myself better understanding abstract things when shown a picture of them (y'know, like ♻ or ♾) or, even better, when I try to make it myself. So, there's that as well. 

## The VM ⚙

[🚧 Some description]

### The instruction set 🧬

[🚧 Some description]

| Opcode   | Asm Instruction Name                                   | Description                                                 |
| :------: | :----------------------------------------------------- | :----------------------------------------------------       |
|   `00`   | `nop`, `noop`, `nope`                                  | No operation                                                |
| | ***Data***                                                                                                                    |
|   `20`   | `ld #val`, `lda #val`                                  | Load value to ***a***                                       |
|   `21`   | `ldb #val`                                             | Load value to ***b***                                       |
|   `22`   | `ldc #val`                                             | Load value to ***c***                                       |
|   `23`   | `laa`, `ldaa`                                          | Load data from ***a*** to ***a***                           |
|   `24`   | `lab`, `ldab`                                          | Load data from ***a*** to ***b***                           |
|   `25`   | `lac`, `ldac`                                          | Load data from ***a*** to ***c***                           |
|   `26`   | `lba`, `ldba`                                          | Load data from ***b*** to ***a***                           |
|   `27`   | `lbb`, `ldbb`                                          | Load data from ***b*** to ***b***                           |
|   `28`   | `lbc`, `ldbc`                                          | Load data from ***b*** to ***c***                           |
|   `29`   | `lca`, `ldca`                                          | Load data from ***c*** to ***a***                           |
|   `2A`   | `lcb`, `ldcb`                                          | Load data from ***c*** to ***b***                           |
|   `2B`   | `lcc`, `ldcc`                                          | Load data from ***c*** to ***c***                           |
| | ***Logic***                                                                                                                   |
|   `40`   | `and`, `cmp`, `comp`                                   | Compare ***a*** to ***b*** and store result in ***c***      |
|   `41`   | `xor`, `xr`                                            | Exclusive-or ***a*** to ***b*** and store result in ***c*** |
| | ***Arithmetics***                                                                                                             |
|   `60`   | `add`, `ad`, `sum`, `sm`, `addc`, `adc`, `sumc`, `smc` | Add ***a*** plus ***b*** and store result in ***c***        |
|   `61`   | `adda`, `ada`, `suma`, `sma`                           | Add ***a*** plus ***b*** and store result in ***a***        |
|   `62`   | `addb`, `adb`, `sumb`, `smb`                           | Add ***a*** plus ***b*** and store result in ***b***        |
|   `63`   | `subt`, `sbt`, `sub`, `sb`, `sbtc`, `subc`, `sbc`      | Subtract ***a*** from ***b*** and store result in ***c***   |
|   `64`   | `sbta`, `suba`, `sba`                                  | Subtract ***a*** from ***b*** and store result in ***a***   |
|   `65`   | `sbtb`, `subb`, `sbb`                                  | Subtract ***a*** from ***b*** and store result in ***b***   |
|   `66`   | `div`, `dv`, `divc`, `dvc`                             | Divide ***a*** by ***b*** and store result in ***c***       |
|   `67`   | `diva`, `dva`                                          | Divide ***a*** by ***b*** and store result in ***a***       |
|   `68`   | `divb`, `dvb`                                          | Divide ***a*** by ***b*** and store result in ***b***       |
|   `69`   | `mult`, `mlt`, `mul`, `ml`, `mltc`, `mulc`, `mlc`      | Multiply ***a*** by ***b*** and store result in ***c***     |
|   `6A`   | `mlta`, `mula`, `mla`                                  | Multiply ***a*** by ***b*** and store result in ***a***     |
|   `6B`   | `mltb`, `mulb`, `mlb`                                  | Multiply ***a*** by ***b*** and store result in ***b***     |
| | ***Halt***                                                                                                                    |
|   `FF`   | `halt`, `hlt`, `stop`, `stp`                           | Stop simulation                                             |

### The compiler ✍

Technically an assembler, not a compiler, but it sounds *way cooler*. 😎 

## Useful resources

[🚧 Some description]

### Sources of inspiraton

[🚧 Some description]
