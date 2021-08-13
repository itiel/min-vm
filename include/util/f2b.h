/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 13/08/2021
 . Last updated: 13/08/2021
 */

#ifndef _F2B_H_
#define _F2B_H_

#include <stdlib.h>
#include <stdio.h>

#define BUFFMAXLEN 1028 

long file2buff (char * file_name, char * buffer, long max_len) {
    
    FILE * file;
    char * error_msg;
    long buff_len = 0;
    char ch;

    if (!(file = fopen(file_name, "r"))) {
        
        error_msg = 
            "Error in file2buff():\n" \
            "  No such file or directory (%s).\n";

        printf(error_msg, file_name);
        
        return -1;

    }

    while (1) {

        if (buff_len + 1 >= max_len) {
            
            fclose(file);

            error_msg = 
                "Error in file2buff():\n" \
                "  Buffer length exceeds max length (%ld).\n";

            printf(error_msg, max_len);

            return -1;

        }

        if ((ch = getc(file)) == EOF) {
            break;
        }

        buffer[buff_len++] = ch;
    }

    fclose(file);

    buffer[buff_len++] = '\0';

    return buff_len;
    
}

#endif /* #ifndef _F2B_H_ */