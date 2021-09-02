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

#define eprintf(format, ...) {                         \
    fprintf(stderr, format __VA_OPT__(, __VA_ARGS__)); \
}

#define put_error(error_msg, ...) {               \
    eprintf("Error:\n  ");                        \
    eprintf(error_msg __VA_OPT__(, __VA_ARGS__)); \
    eprintf("\n");                                \
}

#define put_error_method(method_name, error_msg, ...) { \
    eprintf("Error in %s():\n  ", method_name);         \
    eprintf(error_msg __VA_OPT__(, __VA_ARGS__));       \
    eprintf("\n");                                      \
}

#endif /* #ifndef _ERR_H_ */
