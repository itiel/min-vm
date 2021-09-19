/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

/* -- Includes -- */

#include <stdio.h>

#include <core/asm.h>
#include <core/asm/token.h>
#include <core/asm/tokenizer.h>
#include <core/inst.h>

#include <util/fwn.h>
#include <util/bool.h>
#include <util/err.h>

/* -- Function definitions -- */

// Assembler methods

i32 mvm_asm_assembler_init_file ( 
    mvm_asm_assembler_t * assembler, 
    FILE                * file, 
    i8                  * file_name) 
{

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_init_file", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (!file) {
 
        put_error_method( 
            "mvm_asm_assembler_init_file", 
            "File pointer should not be NULL."
        );

        return FALSE;

    }

    assembler->file            = file;
    assembler->file_name       = file_name;
    assembler->status          = MVM_ELST_INIT;

    return TRUE;

}

i32 mvm_asm_assembler_init ( 
    mvm_asm_assembler_t * assembler, 
    i8                  * file_name) 
{

    FILE * file;

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_init", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (!file_name) {
 
        put_error_method( 
            "mvm_asm_assembler_init", 
            "File name pointer should not be NULL."
        );

        return FALSE;

    }

    if (!(file = fopen(file_name, "rb"))) {

        put_error_method(
            "mvm_asm_assembler_init",
            "No such file or directory (%s).", 
            file_name
        );

        return FALSE;

    }

    return mvm_asm_assembler_init_file(assembler, file, file_name);

}

i32 mvm_asm_assembler_kill (mvm_asm_assembler_t * assembler) {

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assembler_kill", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;

    }

    if (assembler->status != MVM_ELST_END) {

        fclose(assembler->file);

    }

    assembler->status = MVM_ELST_END;

    return TRUE;

}

i32 mvm_asm_assemble (mvm_asm_assembler_t * assembler) {

    mvm_asm_tokenizer_t tokenizer;
    mvm_asm_token_t     token;
    i32                 result;

    if (!assembler) {
 
        put_error_method( 
            "mvm_asm_assemble", 
            "Assembler pointer should not be NULL."
        );

        return FALSE;
    }

    if (assembler->status != MVM_ELST_INIT) {
 
        put_error_method( 
            "mvm_asm_assemble", 
            "Assembler element should be initialized." 
        );
 
        return FALSE;
    }


    if (!mvm_asm_tokenizer_init(&tokenizer, assembler)) {

        put_error_method( 
            "mvm_asm_assemble", 
            "Something unexpected happened while initializing tokenizer." 
        );

        return FALSE;

    }

    assembler->status = MVM_ELST_IN_USE;

    while ((result = mvm_asm_tokenize_next(&tokenizer, &token))) {

        if (result == -1) {
 
            put_error_method( 
                "mvm_asm_assemble", 
                "Something unexpected happened while tokenizing file (%s).",
                tokenizer.assembler->file_name
            );

            return FALSE;

        }

    }

    return TRUE;

}
