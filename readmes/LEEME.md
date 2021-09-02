[//]: # (Author: Itiel Lopez - itiel@soyitiel.com)
[//]: # (Created: 17/08/2021)

> :warning: **Advertencia:** La mayor parte de este documento es un borrador y puede contener información incorrecta. Léalo con precaución.

# Bienvenido a min-vm

Una máquina virtual (MV) experimental hecha con amor. :heart:

* [Read this document in english :uk:](../README.md)

## :star2: Introducción

**min-vm** representa mi propio intento :muscle: por entender el tema de las MVs. 

Había escuchado antes sobre sistemas que funcionan con su propia MV (como Java :coffee: o Python :snake:, y creo que V8 o Node también :man_shrugging:), pero nunca había entendido cómo o por qué, ni tampoco me importaba mucho que digamos. Pero luego descubrí que hay quienes han escrito su propio **sistema operativo** o su propio **kernel**, algunos escribieron su propia **MV** y su ***assembler***, y algunos hasta construyeron su propio **procesador con protoboards** (qué⁉). ***Eso sí*** que captó mi atención. Fue como si, ahora que supe que un simple mortal como yo pudo construir algo de tal magnitud con tan pocos recursos, entonces yo ***estaba obligado*** a hacerlo también.

Así que, *welcome to The Internet, have a look around*. :notes::sunglasses:

## :gear: La MV

[:construction: Descripción]

### :dna: El Set de Instrucciones

Por convención, los nombres de las instrucciones deben ser de mínimo 2 y máximo 4 caracteres de largo.

La siguiente es una lista de las instrucciones que el *assembler* puede (o podrá) interpretar.

<!---
 Código OP | Inst Nombre(s)   | Descripción
-----------+------------------+-------------------------------------------
 💤 No Operation
    0x00   | nop, noop, nope, | Ninguna operación
             np
    📝 Datos
    0x20   | load, loda, lod, | Cargar datos en a
             ld, lda 
    0x21   | lodb, ldb        | Cargar datos en b
    0x22   | lodc, ldc        | Cargar datos en c
    0x23   | laa, ldaa        | Cargar los datos de a en a
    0x24   | lab, ldab        | Cargar los datos de a en b
    0x25   | lac, ldac        | Cargar los datos de a en c
    0x26   | lba, ldba        | Cargar los datos de b en a
    0x27   | lbb, ldbb        | Cargar los datos de b en b
    0x28   | lbc, ldbc        | Cargar los datos de b en c
    0x29   | lca, ldca        | Cargar los datos de c en a
    0x2A   | lcb, ldcb        | Cargar los datos de c en b
    0x2B   | lcc, ldcc        | Cargar los datos de c en c
    ☑ Lógica
    0x40   | and, cmp, comp   | Comparar a con b y guardar el resultado en c
    0x41   | exor, eor, xor,  | Comparar ("o exclusivo") a con b y guardar el resultado en c
           | xo, xr
    ➗ Aritmética
    0x60   | add, ad, sum,    | Sumar a más b y guardar el resultado en c
           | sm, addc, adc, 
           | sumc, smc
    0x61   | adda, ada, suma, | Sumar a más b y guardar el resultado en a
             sma
    0x62   | addb, adb, sumb, | Sumar a más b y guardar el resultado en b
             smb
    0x63   | subt, sbt, sub,  | Restarle a a b y guardar el resultado en c
             sb, sbtc, subc, 
             sbc
    0x64   | sbta, suba, sba  | Restarle a a b y guardar el resultado en a
    0x65   | sbtb, subb, sbb  | Restarle a a b y guardar el resultado en b
    0x66   | div, dv, divc,   | Dividir a entre b y guardar el resultado en c
             dvc
    0x67   | diva, dva        | Dividir a entre b y guardar el resultado en a
    0x68   | divb, dvb        | Dividir a entre b y guardar el resultado en b
    0x69   | mult, mlt, mul,  | Multiplicar a por b y guardar el resultado en c
             ml, mltc, mulc, 
             mlc
    0x6A   | mlta, mula, mla  | Multiplicar a por b y guardar el resultado en a
    0x6B   | mltb, mulb, mlb  | Multiplicar a por b y guardar el resultado en b
    🛑 Fin
    0xFF   | halt, hlt, stop, | Detener simulación
           | stp
-->

<table>
    <thead>
        <tr>
            <th>Código <br>OP</th>
            <th>Nombre(s) de Inst</th>
            <th>Arg(s)</th>
            <th>Descripción</th>
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
        <td>Ninguna operación</td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:pencil: Datos</em>
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
            Cargar datos en <strong><em>a</em></strong>
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
            Cargar datos en <strong><em>b</em></strong>
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
            Cargar datos en <strong><em>c</em></strong>
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
            Cargar datos de <strong><em>a</em></strong> en <strong><em>a</em></strong>
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
            Cargar datos de <strong><em>a</em></strong> en <strong><em>b</em></strong>
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
            Cargar datos de <strong><em>a</em></strong> en <strong><em>c</em></strong>
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
            Cargar datos de <strong><em>b</em></strong> en <strong><em>a</em></strong>
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
            Cargar datos de <strong><em>b</em></strong> en <strong><em>b</em></strong>
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
            Cargar datos de <strong><em>b</em></strong> en <strong><em>c</em></strong>
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
            Cargar datos de <strong><em>c</em></strong> en <strong><em>a</em></strong>
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
            Cargar datos de <strong><em>c</em></strong> en <strong><em>b</em></strong>
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
            Cargar datos de <strong><em>c</em></strong> en <strong><em>c</em></strong>
        </td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:ballot_box_with_check: Lógica</em>
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
            Comparar <strong><em>a</em></strong> con <strong><em>b</em></strong> y guardar <br>
            el resultado en <strong><em>c</em></strong>
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
            Comparar <em>("o exclusivo")</em>  <strong><em>a</em></strong> con <strong><em>b</em></strong> <br>
            y guardar el resultado en <strong><em>c</em></strong>
        </td>
    </tr>
    <thead>
        <tr>
            <th colspan="4">
                <em>:heavy_division_sign: Aritmética</em>
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
            Sumar <strong><em>a</em></strong> más <strong><em>b</em></strong> y guardar el resultado en <strong><em>c</em></strong>
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
            Sumar <strong><em>a</em></strong> más <strong><em>b</em></strong> y guardar el resultado en <strong><em>a</em></strong>
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
            Sumar <strong><em>a</em></strong> más <strong><em>b</em></strong> y guardar el resultado en <strong><em>b</em></strong>
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
            Restarle <strong><em>a</em></strong> a <strong><em>b</em></strong> y guardar el resultado en <strong><em>c</em></strong>
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
            Restarle <strong><em>a</em></strong> a <strong><em>b</em></strong> y guardar el resultado en <strong><em>a</em></strong>
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
            Restarle <strong><em>a</em></strong> a <strong><em>b</em></strong> y guardar el resultado en <strong><em>b</em></strong>
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
            Dividir <strong><em>a</em></strong> entre <strong><em>b</em></strong> y guardar el resultado en <strong><em>c</em></strong>
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
            Dividir <strong><em>a</em></strong> entre <strong><em>b</em></strong> y guardar el resultado en <strong><em>a</em></strong>
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
            Dividir <strong><em>a</em></strong> entre <strong><em>b</em></strong> y guardar el resultado en <strong><em>b</em></strong>
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
            Multiplicar <strong><em>a</em></strong> por <strong><em>b</em></strong> y guardar el resultado en <strong><em>c</em></strong>
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
            Multiplicar <strong><em>a</em></strong> por <strong><em>b</em></strong> y guardar el resultado en <strong><em>a</em></strong>
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
            Multiplicar <strong><em>a</em></strong> por <strong><em>b</em></strong> y guardar el resultado en <strong><em>b</em></strong>
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
            Detener simulación
        </td>
    </tr>
</table>

## :writing_hand: El Compilador

Técnicamente, un ensamblador (*assembler*), no un compilador, pero se oye *mucho más padre* así. :sunglasses: 

## :books: Referncias Útiles

[:construction: Descripción]

### :sparkles: Fuentes de Inspiración

[:construction: Descripción]
