/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 13/08/2021
 */

#ifndef _F2B_H_
#define _F2B_H_

/* -- Includes -- */

#include <stdlib.h>
#include <stdio.h>

#include "fwnums.h"

/* -- Declarations -- */

/*
 . -- file2buff() -- 
 .
 . Description:
 .
 .     TODO: Fill description
 . 
 . Recomended use:
 . 
 .     char * buffer;
 .     long buff_len;
 . 
 .     buffer = file2buff("/file/path/file_name", &buff_len);

 .     if (!buffer) {
 . 
 .         // Hanlde error
 . 
 .     }
 . 
 .     printf("buff_len:   %ld\n", buff_len);
 .     printf("buffer:\n   %s\n", buffer);
 . 
 .     free(buffer);
*/

i8 * file2buff (i8 * file_name, i64 * buffer_len);

/* 
 . -- file2buff_maxlen() -- 
 .
 . Description:
 .
 .     TODO: Fill description
 . 
 . Recomended use:
 . 
 .     #define BUFFMAXLEN 2048
 .     
 .     char buffer[BUFFMAXLEN];
 .     long buff_len;
 .     
 .     buff_len = file2buff_maxlen("/file/path/file_name", buffer, BUFFMAXLEN);
 .     
 .     if (buff_len < 0) {
 .     
 .         // Hanlde error
 .     
 .     }
 .     
 .     printf("buff_len:   %ld\n", buff_len);
 .     printf("buffer:\n   %s\n", buffer);
*/

i64 file2buff_maxlen (i8 * file_name, i8 * buffer, i64 max_len);

/* 
 . -- file2buff_fread() -- 
 .
 . Description:
 .
 .     TODO: Fill description
 . 
 . Recomended use:
 . 
 .     #define BUFFMAXLEN 2048
 .     
 .     char buffer[BUFFMAXLEN];
 .     long buff_len;
 .     
 .     buff_len = file2buff_maxlen("/file/path/file_name", buffer, BUFFMAXLEN);
 .     
 .     if (buff_len < 0) {
 .     
 .         // Hanlde error
 .     
 .     }
 .     
 .     printf("buff_len:   %ld\n", buff_len);
 .     printf("buffer:\n   %s\n", buffer);
*/

i64 file2buff_fread (FILE * file, i8 * buffer, i64 max_len);

/* -- Definitions -- */

i8 * file2buff (i8 * file_name, i64 * buffer_len) {

    FILE * file;
    i8 * error_msg;
    i8 * buffer;
    i64 buff_len;
    i8 ch;

    if (!(file = fopen(file_name, "r"))) {
        
        error_msg = 
            "Error in file2buff():\n" \
            "  No such file or directory (%s).\n";

        printf(error_msg, file_name);
        
        return 0;

    }

    // There's no need to catch any errors here 
    // because file2buff_fread() would only 
    // return -1 if max_len was above -1

    buff_len = file2buff_fread(file, 0, -1);

    /*if ((buff_len = file2buff_fread(file, 0, -1)) == -1) {
        
        fclose(file);

        error_msg = 
            "Error in file2buff():\n" \
            "  Something unexpected happened while reading file (%s).\n";

        printf(error_msg, file_name);
        
        return 0;

    }*/

    if (!(buffer = malloc(sizeof(i8) * (buff_len + 1)))) {

        fclose(file);

        error_msg = 
            "Error in file2buff():\n" \
            "  Something unexpected happened when allocating buffer.\n";

        printf(error_msg, 0);
        
        return 0;

    }

    rewind(file);

    // Same thing as before

    file2buff_fread(file, buffer, -1);

    // if ((file2buff_fread(file, buffer, -1)) == -1) {

    buffer[buff_len++] = '\0';

    if (buffer_len) {
        
        *buffer_len = buff_len;
    
    }

    return buffer;

}

i64 file2buff_maxlen (i8 * file_name, i8 * buffer, i64 max_len) {
    
    FILE * file;
    i8 * error_msg;
    i64 buff_len = 0;
    i8 ch;

    if (max_len < 0) {
        
        error_msg = 
            "Error in file2buff_maxlen():\n" \
            "  Max buffer size cannot be lower than 0 (%d).\n";

        printf(error_msg, max_len);
        
        return -1;

    }

    if (!(file = fopen(file_name, "r"))) {
        
        error_msg = 
            "Error in file2buff_maxlen():\n" \
            "  No such file or directory (%s).\n";

        printf(error_msg, file_name);
        
        return -1;

    }

    if ((buff_len = file2buff_fread(file, buffer, max_len)) == -1) {
        
        fclose(file);

        error_msg = 
            "Error in file2buff_maxlen():\n" \
            "  Something unexpected happened while reading file (%s).\n";

        printf(error_msg, file_name);

        return -1;

    }

    fclose(file);

    if (++buff_len > max_len) {
       
        error_msg = 
            "Error in file2buff_maxlen():\n" \
            "  Buffer size needed exceeds max size (%ld).\n";

        printf(error_msg, max_len);

        return -1;

    }

    buffer[buff_len] = '\0';

    return buff_len;

}

i64 file2buff_fread (FILE * file, i8 * buffer, i64 max_len) {
    
    i8 * error_msg;
    i64 buff_len = 0;
    i8 ch;

    while (1) {

        if ((ch = getc(file)) == EOF) {
            break;
        }

        if (max_len > -1 && buff_len + 1 > max_len) {
           
            error_msg = 
                "Error in file2buff_fread():\n" \
                "  Buffer size needed exceeds max size (%ld).\n";

            printf(error_msg, max_len);

            return -1;

        }

        if (buffer) {

            buffer[buff_len] = ch;
        
        }

        buff_len++;
        
    }

    return buff_len;

}

#endif /* #ifndef _F2B_H_ */