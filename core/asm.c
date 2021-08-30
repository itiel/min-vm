/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#include "asm.h"

int main (int argc, char const ** argv) {

    char             * file_name;
    FILE             * file;
    mvm_asm_parser_t parser;

    file_name = (char *) argv[1];

    if (argc > 1) {

        if (!(file = fopen(file_name, "rb"))) {

            put_error_method(
                "main",
                "No such file or directory (%s).", 
                file_name
            );

            return 1;

        }

        fseek(file, 0, SEEK_END);

        if (!mvm_asm_parser_init(
            &parser, 
            file, file_name)) 
        {

            put_error_method( 
                "main", 
                "Something unexpected happened while initializing parser."
            );

            fclose(file);

            return 1;

        }

        if (!mvm_asm_parse(&parser)) {

            put_error_method( 
                "main", 
                "Something unexpected happened while parsing file (%s).",
                file_name
            );

            fclose(file);

            return 1;

        }

        fclose(file);

    }

    return 0;

}