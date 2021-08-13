/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/08/2021
 . Last updated: 12/08/2021
 */

#include <util/f2b.h>
#include "asm.h"

int main (int argc, char const ** argv) {

    char buffer[BUFFMAXLEN];
    long buff_len;

    if (argc > 1) {

        buff_len = file2buff((char *) argv[1], buffer, BUFFMAXLEN);

        printf("buffer_len: %ld\n", buff_len);

        printf("buffer:\n%s\n", buffer);

    }

    return 0;

}