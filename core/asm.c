/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
 */

#include <util/f2b.h>
#include "asm.h"

#define BUFFMAXLEN 2048

int main (int argc, char const ** argv) {

    if (argc > 1) {
        
        long buff_len;

        /* -- file2buff_maxlen() -- */
    
        char buffer[BUFFMAXLEN];

        buff_len = file2buff_maxlen((char *) argv[1], buffer, BUFFMAXLEN);

        if (buff_len < 0) {

            return 1;

        }

        printf("buffer_len: %ld\n", buff_len);

        printf("buffer:\n%s\n", buffer);

    }

    return 0;

}