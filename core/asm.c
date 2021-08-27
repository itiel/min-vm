/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#include <util/f2b.h>

#include "asm.h"

#define BUFFSIZE    2048 * 2
#define TOKLISTSIZE 256 

int main (int argc, char const ** argv) {

    char             * file_name;
    char             buffer[BUFFSIZE];
    long             buff_len;
    mvm_asm_token_t  tokens[TOKLISTSIZE];
    i64              tokens_len;
    mvm_asm_parser_t parser;

    file_name = (char *) argv[1];

    if (argc > 1) {

        // TODO: Try doing this step without loading 
        //       a buffer but reading directly from file

        buff_len = file2buff(file_name, buffer, BUFFSIZE);

        if (buff_len < 0) {

            put_error_method( 
                "main", 
                "Something unexpected happened while loading file to buffer (%s).",
                file_name
            );

            return 1;

        }

        if (!mvm_asm_parser_init(
            &parser, buffer, buff_len, file_name, 
            tokens, TOKLISTSIZE)) 
        {

            put_error_method( 
                "main", 
                "Something unexpected happened while initializing parser."
            );

            return 1;

        }

        if (!mvm_asm_parse(&parser)) {

            put_error_method( 
                "main", 
                "Something unexpected happened while parsing file."
            );

            return 1;

        }

    }

    return 0;

}