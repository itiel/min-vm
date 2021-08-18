[//]: # (Author: Itiel Lopez - itiel@soyitiel.com)
[//]: # (Created: 17/08/2021)

# Bienvenido a min-vm

Una máquina virtual (MV) experimental hecha con amor. :heart:

> :warning: **Advertencia:** La mayor parte de este documento es un borrador y puede contener información incorrecta. Léalo con precaución.

## Introducción :star2:

**min-vm** representa mi propio intento :muscle: por entender el tema de las MVs. 

Había escuchado antes sobre sistemas que funcionan con su propia MV (como Java :coffee: o Python :snake:, y creo que V8 o Node también 🤷‍♂️), pero nunca había entendido cómo o por qué, ni tampoco me importaba mucho que digamos. Pero luego descubrí que hay quienes han escrito su propio **sistema operativo** o su propio **kernel**, algunos escribieron su propia **MV** y su ***assembler***, y algunos hasta construyeron su propio **procesador con protoboards** (qué⁉). ***Eso sí*** que captó mi atención. Fue com si, ahora que supe que un simple mortal como yo pudo construir algo como eso con tan pocos recursos, entonces yo ***estaba obligado*** a hacerlo también.

Así que, *welcome a The Internet, have a look around*. 🎶😎

## La MV ⚙

[🚧 Cierta descripción]

## El compilador ✍

Técnicamente, un ensamblador (*assembler*), no un compilador, pero se oye *mucho más padre* así. 😎 

### El set de instrucciones 🧬

Por convención, los nombres de las instrucciones deben ser de mínimo 2 y máximo 4 caracteres de largo.

La siguiente es una lista de las instrucciones que el *assembler* puede (o podrá) interpretar.

| Código OP | Nombre(s) de la Instrucción                            | Descripción                                                                   |
| :-------: | :----------------------------------------------------- | :---------------------------------------------------------------------------- |
|    `00`   | `nop`, `noop`, `nope`                                  | Ninguna operación                                                             |
|           | ***Datos***                                                                                                                            |
|    `20`   | `ld #val`, `lda #val`                                  | Cargar un valor a ***a***                                                     |
|    `21`   | `ldb #val`                                             | Cargar un valor a ***b***                                                     |
|    `22`   | `ldc #val`                                             | Cargar un valor a ***c***                                                     |
|    `23`   | `laa`, `ldaa`                                          | Cargar los datos de ***a*** en ***a***                                        |
|    `24`   | `lab`, `ldab`                                          | Cargar los datos de ***a*** en ***b***                                        |
|    `25`   | `lac`, `ldac`                                          | Cargar los datos de ***a*** en ***c***                                        |
|    `26`   | `lba`, `ldba`                                          | Cargar los datos de ***b*** en ***a***                                        |
|    `27`   | `lbb`, `ldbb`                                          | Cargar los datos de ***b*** en ***b***                                        |
|    `28`   | `lbc`, `ldbc`                                          | Cargar los datos de ***b*** en ***c***                                        |
|    `29`   | `lca`, `ldca`                                          | Cargar los datos de ***c*** en ***a***                                        |
|    `2A`   | `lcb`, `ldcb`                                          | Cargar los datos de ***c*** en ***b***                                        |
|    `2B`   | `lcc`, `ldcc`                                          | Cargar los datos de ***c*** en ***c***                                        |
|           | ***Lógica***                                                                                                                           |
|    `40`   | `and`, `cmp`, `comp`                                   | Comparar ***a*** con ***b*** y guardar el resultado en ***c***                |
|    `41`   | `exor`, `eor`, `xor`, `xo`, `xr`                       | Comparar ("o excusivo") ***a*** con ***b*** y guardar el resultado en ***c*** |
|           | ***Aritmética***                                                                                                                       |
|    `60`   | `add`, `ad`, `sum`, `sm`, `addc`, `adc`, `sumc`, `smc` | Sumar ***a*** más ***b*** y guardar el resultado en ***c***                   |
|    `61`   | `adda`, `ada`, `suma`, `sma`                           | Sumar ***a*** más ***b*** y guardar el resultado en ***a***                   |
|    `62`   | `addb`, `adb`, `sumb`, `smb`                           | Sumar ***a*** más ***b*** y guardar el resultado en ***b***                   |
|    `63`   | `subt`, `sbt`, `sub`, `sb`, `sbtc`, `subc`, `sbc`      | Restarle ***a*** a ***b*** y guardar el resultado en ***c***                  |
|    `64`   | `sbta`, `suba`, `sba`                                  | Restarle ***a*** a ***b*** y guardar el resultado en ***a***                  |
|    `65`   | `sbtb`, `subb`, `sbb`                                  | Restarle ***a*** a ***b*** y guardar el resultado en ***b***                  |
|    `66`   | `div`, `dv`, `divc`, `dvc`                             | Dividir ***a*** entre ***b*** y guardar el resultado en ***c***               |
|    `67`   | `diva`, `dva`                                          | Dividir ***a*** entre ***b*** y guardar el resultado en ***a***               |
|    `68`   | `divb`, `dvb`                                          | Dividir ***a*** entre ***b*** y guardar el resultado en ***b***               |
|    `69`   | `mult`, `mlt`, `mul`, `ml`, `mltc`, `mulc`, `mlc`      | Multiplicar ***a*** por ***b*** y guardar el resultado en ***c***             |
|    `6A`   | `mlta`, `mula`, `mla`                                  | Multiplicar ***a*** por ***b*** y guardar el resultado en ***a***             |
|    `6B`   | `mltb`, `mulb`, `mlb`                                  | Multiplicar ***a*** por ***b*** y guardar el resultado en ***b***             |
|           | ***Fin***                                                                                                                              |
|    `FF`   | `halt`, `hlt`, `stop`, `stp`                           | Detener simulación                                                            |

## Fuentes útiles de información

[🚧 Cierta descripción]

### Fuentes de inspiración

[🚧 Cierta descripción]
