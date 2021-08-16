/*    
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 16/08/2021
*/

#ifndef _ER_H_
#define _ER_H_

#include <stdio.h>

/*
 . I know there might be a better way to do this.
 . This is just so I don't repeat myself so much
 . as I was with the old way
*/

#define put_error(method_name, error_msg, ...) {          \
    fprintf(stderr, "Error in %s():\n  ", method_name);   \
    fprintf(stderr, error_msg __VA_OPT__(, __VA_ARGS__)); \
    fprintf(stderr, "\n");                                \
}

#endif /* #ifndef _ER_H_ */
