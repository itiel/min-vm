#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define to_lower(_ch) (_ch >= 'A' || _ch <= 'Z' ? _ch | 0x60 : _ch)

int main(int argc, char const *argv[]) {
    
    char          * test_str;
    double        start, end, total;
    unsigned long cycles;

    test_str = \
        "This is a test.\n\t" \
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\t" \
        "abcdefghijklmnopqrstuvwxyz\n\t" \
        "0123456789\n";

    printf("Test string:\n\n%s\n\n", test_str);

    cycles = 50000000UL;

    printf("Cycles to test: %ld\n\n", cycles);    

    printf("ctype's tolower() test ...\n\n");

    start = clock();

    for (int cy = 0; cy < cycles; ++cy) {
        
        for (char * str_ptr = test_str; *str_ptr; ++str_ptr) {
            
            (void) (tolower(*str_ptr));
        
        }

    }

    end = clock();

    total = (double) (end - start) / CLOCKS_PER_SEC;
    
    printf("Total time: %f seconds\n\n", total);

    printf("Custom to_lower() test ...\n\n");

    start = clock();

    for (int cy = 0; cy < cycles; ++cy) {
        
        for (char * str_ptr = test_str; *str_ptr; ++str_ptr) {
            
            (void) (to_lower(*str_ptr));
        
        }

    }

    end = clock();

    total = (double) (end - start) / CLOCKS_PER_SEC;
    
    printf("Total time: %f seconds\n\n", total);

    return 0;
}