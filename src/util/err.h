/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 16/08/2021
*/

#ifndef _ERR_H_
#define _ERR_H_

#include <stdio.h>

/*
 . I know there might be a better way to do this.
 . This is just so I don't repeat myself so much
 . as I was with the old way.
*/

#define eputchar(ch) putc(ch, stderr)

#define eprintf(format, args...) \
    fprintf(stderr, format , ## args)

#define put_error(error_msg, args...) { \
    eprintf("Error:\n  ");              \
    eprintf(error_msg , ## args);       \
    eprintf("\n");                      \
}

#define put_error_method(method_name, error_msg, args...) { \
    eprintf("Error in %s():\n  ", method_name);             \
    eprintf(error_msg , ## args);                           \
    eprintf("\n");                                          \
}

#endif /* #ifndef _ERR_H_ */
