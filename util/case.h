/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 02/09/2021
*/

#ifndef _CASE_H_
#define _CASE_H_

/*
 . Example use:
 . 
 .     #include <stdio.h>
 .     #include <string.h>
 . 
 .     #include "case.h"
 . 
 .     #define SOURCE "ABCDWXYZabcdwxyz"
 . 
 .     int main() {
 . 
 .         int source_len;
 .         int result;
 . 
 .         // Print og string
 . 
 .         printf("%s\n", SOURCE); // prints: ABCDWXYZabcdwxyz
 . 
 .         // Take og string's length
 . 
 .         source_len = strlen(SOURCE);
 . 
 .         // Create buffer
 . 
 .         char buffer[source_len + 1];
 . 
 .         // Load lower-case string to buffer 
 . 
 .         result = str_to_lower(SOURCE, source_len, buffer, source_len);
 . 
 .         // NULL terminate buffer
 . 
 .         buffer[result] = '\0';
 . 
 .         // Print buffer
 . 
 .         printf("%s\n", buffer); // prints: abcdwxyzabcdwxyz
 . 
 .         // Load upper-case string to buffer 
 .         // This time, the source is the buffer itself
 . 
 .         result = str_to_upper(buffer, source_len, buffer, source_len);
 . 
 .         // NULL terminate buffer
 . 
 .         buffer[result] = '\0';
 . 
 .         // Print buffer
 . 
 .         printf("%s\n", buffer); // prints: ABCDWXYZABCDWXYZ
 . 
 .         return 0;
 . 
 .     }
*/

/* -- Includes -- */

#include "fwn.h"
#include "chval.h"

/* -- Macros -- */

// A -> a = A | 0x60
// a -> A = a ^ 0x20

#define ch_to_lower(_ch) \
    (ch_is_upper(_ch) ? _ch | 0x60 : _ch)
#define ch_to_upper(_ch) \
    (ch_is_lower(_ch) ? _ch ^ 0x20 : _ch)

u64 str_to_lower (i8 * src, u64 src_max, i8 * buff, u64 buff_len) {
 
    u64 i;

    if (!src || !buff) return -1;

    for (i = 0; i < src_max && i < buff_len && src[i]; ++i) {
 
        buff[i] = ch_to_lower(src[i]); 
 
    }

    return i;

}

u64 str_to_upper (i8 * src, u64 src_max, i8 * buff, u64 buff_len) {
 
    u64 i;

    if (!src || !buff) return -1;

    for (i = 0; i < src_max && i < buff_len && src[i]; ++i) {
 
        buff[i] = ch_to_upper(src[i]); 
 
    }

    return i;

}

#endif /* #ifndef _CASE_H_ */
