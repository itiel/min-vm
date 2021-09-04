/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 02/09/2021
*/

#ifndef _STRLEN_S_H_
#define _STRLEN_S_H_

/*
 . Example use:
 . 
 .     #include <stdio.h>
 . 
 .     #include "strlen-s.h"
 . 
 .     #define SOURCE "1234567890"
 . 
 .     int main () {
 . 
 .         int len;
 . 
 .         len = strlen_s(SOURCE, 100); 
 . 
 .         printf("%d\n", len); // prints: 10
 . 
 .         len = strlen_s(SOURCE, 5);
 . 
 .         printf("%d\n", len); // prints: 5
 . 
 .         len = strlen_s(SOURCE, -1);
 . 
 .         printf("%d\n", len); // prints: 10
 . 
 .         return 0;
 .     }
 . 
*/

#include "fwn.h"

u64 strlen_s(i8 * str, u64 max_len) {

    i8  * strp;
    u64 i;

    if (!str) return -1;

    if (max_len == (u64) -1) { // No limit
 
        for (strp = str; *strp; ++strp);

        return strp - str; 
 
    }

    for (i = 0; *str && i < max_len; ++str, ++i);

    return i;

}

#endif /* #ifndef _STRLEN_S_H_ */
