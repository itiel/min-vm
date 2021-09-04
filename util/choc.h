/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 22/08/2021
*/

/*
 . Check for the occurrence of a character 
 . inside a string
*/

#ifndef _CHOC_H_
#define _CHOC_H_

/*
 . char_occur()
 . 
 . Recomended use:
 . 
 .     #include <stdio.h>
 . 
 .     int main() {
 . 
 .         if (char_occur('c', "ABCDabcd")) {
 . 
 .             printf("Character found\n");
 . 
 .             return 0; 
 . 
 .         }
 . 
 .         printf("Character not found\n");
 . 
 .         return 0;
 .     } 
*/

int char_occur (char ch, char * str) {

    for (; *str; str++) {

        if (ch == *str) {
 
            return 1;

        }
    }

    return 0;
}

#endif /* #ifndef _CHOC_H_ */
