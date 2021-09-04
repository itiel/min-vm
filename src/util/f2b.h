/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 13/08/2021
*/

#ifndef _F2B_H_
#define _F2B_H_

/* -- Includes -- */

#include <stdlib.h>
#include <stdio.h>

#include "err.h"
#include "fwn.h"

/* -- Definitions -- */

/* 
 . -- file2buff() -- 
 .
 . Description:
 .
 .     TODO: Fill description
 . 
 . Recomended use:
 . 
 .     #define BUFFSIZE 2048
 . 
 .     char buffer[BUFFSIZE];
 .     long buff_len;
 . 
 .     buff_len = file2buff("/file/path", buffer, BUFFSIZE);
 . 
 .     if (buff_len < 0) {
 . 
 .         // Hanlde error
 . 
 .     }
 . 
 .     printf("buff_len: %ld\n", buff_len);
 .     printf("buffer:   \n%s\n", buffer);
 .
*/

i64 file2buff (i8 * file_name, i8 * buffer, i64 buff_size) {
 
    FILE * file;
    i64 buff_len = 0;
    i8 ch;

    if (buff_size < 0) {

        put_error_method( 
            "file2buff",
            "Buffer size cannot be lower than 0 (%ld).", 
            buff_size
        );
 
        return -1;

    }

    if (!(file = fopen(file_name, "rb"))) {

        put_error_method( 
            "file2buff",
            "No such file or directory (%s).", 
            file_name
        );

        return -1;

    }

    fseek(file, 0, SEEK_END);

    if (ftell(file) + 1 > buff_size) {
 
        fclose(file);

        put_error_method( 
            "file2buff",
            "File size needed exceeds buffer size (%ld).", 
            buff_size
        );

        return -1;
    }
 
    rewind(file);

    buff_len = fread(buffer, 1, buff_size, file);

    fclose(file);

    buffer[buff_len++] = '\0';

    return buff_len;

}

#endif /* #ifndef _F2B_H_ */
