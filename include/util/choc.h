/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 22/08/2021
*/

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

int char_occur (char ch, char * list) {

    for (; *list; list++) {

        if (ch == *list) {
            
            return 1;

        }
    }

    return 0;
}