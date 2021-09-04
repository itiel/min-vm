/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 02/09/2021
*/

/*
 . Example use:
 . 
 .     #include <stdio.h>
 . 
 .     #include "strcmp-s.h"
 . 
 .     #define STR1 "ABCDEFGHIJKLMNOP"
 .     #define STR2 "ABCDEFGHIJKLMNOQ"
 .     #define STR3 "abcdefghijklmnop"
 . 
 .     #define bool2str(_val) \
 .         (_val ? "true" : "false")
 . 
 .     int main () {
 . 
 .         int max_len;
 .         int result;
 . 
 .         // Case sensitive
 . 
 .         max_len = 20;
 . 
 .         result = strcmp_s(STR1, STR1, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         result = strcmp_s(STR1, STR2, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         result = strcmp_s(STR1, STR3, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         max_len = 10;
 . 
 .         result = strcmp_s(STR1, STR2, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         max_len = -1;
 . 
 .         result = strcmp_s(STR1, STR1, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         result = strcmp_s(STR1, STR2, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         // Case insensitive
 . 
 .         max_len = 20;
 . 
 .         result = strcmp_case_s(STR1, STR1, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         result = strcmp_case_s(STR1, STR2, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         result = strcmp_case_s(STR1, STR3, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         max_len = 10;
 . 
 .         result = strcmp_case_s(STR2, STR3, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         max_len = -1;
 . 
 .         result = strcmp_case_s(STR1, STR2, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         result = strcmp_case_s(STR2, STR3, max_len); 
 .         printf("%s\n", bool2str(result)); // false
 . 
 .         result = strcmp_case_s(STR1, STR3, max_len); 
 .         printf("%s\n", bool2str(result)); // true
 . 
 .         return 0;
 . 
 .     }
*/

#ifndef _STRCMP_S_H_
#define _STRCMP_S_H_

#include "fwn.h"
#include "case.h"

i32 strcmp_s (i8 * str1, i8 * str2, u64 max_len) {

    u64 i;

    if (!str1 || !str2) return -1;

    if (max_len == (u64) -1) { // No limit
 
        for (; 1; str1++, str2++) {

            if (!*str1 || !*str2) {

                if (*str1 == *str2) return 1; 

            }
 
            if (*str1 != *str2) return 0;

        }

    }

    for (i = 0; 1; str1++, str2++, i++) {

        if (!*str1 || !*str2 || i == max_len) {

            if (*str1 == *str2) return 1; 

        }

        if (*str1 != *str2) return 0;

    }

}

i32 strcmp_case_s (i8 * str1, i8 * str2, u64 max_len) {

    u64 i;

    if (!str1 || !str2) return -1;

    if (max_len == (u64) -1) { // No limit
 
        for (; 1; str1++, str2++) {

            if (!*str1 || !*str2) {

                if (ch_to_lower(*str1) == ch_to_lower(*str2)) return 1; 

            }
 
            if (ch_to_lower(*str1) != ch_to_lower(*str2)) return 0;

        }
 
    }

    for (i = 0; 1; str1++, str2++, i++) {

        if (!*str1 || !*str2 || i == max_len) {

            if (ch_to_lower(*str1) == ch_to_lower(*str2)) return 1; 

        }

        if (ch_to_lower(*str1) != ch_to_lower(*str2)) return 0;

    }

}

#endif /* #ifndef _STRCMP_S_H_ */
