/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
*/

#include "asm.h"

#define BUFFSIZE    2048
#define TOKLISTSIZE 256

int main (int argc, char const ** argv) {

    char             buffer[BUFFSIZE];
    long             buff_len;
    mvm_asm_token_t  tokens[TOKLISTSIZE];
    i64              tokens_len;
    mvm_asm_parser_t parser;

    if (argc > 1) {

        buff_len = file2buff((char *) argv[1], buffer, BUFFSIZE);

        if (buff_len < 0) {

            // Handle error

            return 1;

        }

        if (!mvm_asm_parser_init(&parser, buffer, buff_len, tokens, TOKLISTSIZE)) {

            // Handle error

            return 1;

        }

        if (!mvm_asm_parse(&parser)) {

            // Handle error

            return 1;

        }

    }

    return 0;

}