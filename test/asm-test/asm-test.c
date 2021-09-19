/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#include <core/asm.h>

#include <util/err.h>

int main (int argc, char const ** argv) {

    char                * file_name;
    mvm_asm_assembler_t assembler;

    if (argc > 1) {
 
        file_name = (char *) argv[1];

        if (!mvm_asm_assembler_init(&assembler,  file_name)) {

            put_error_method( 
                "main", 
                "Something unexpected happened while initializing assembler." 
            );

            mvm_asm_assembler_kill(&assembler);

            return 1;

        }

        if (!mvm_asm_assemble(&assembler)) {

            put_error_method( 
                "main", 
                "Something unexpected happened while assembling file (%s).", 
                file_name 
            );

            mvm_asm_assembler_kill(&assembler);

            return 1;

        }

        mvm_asm_assembler_kill(&assembler);

    }

    return 0;

}
