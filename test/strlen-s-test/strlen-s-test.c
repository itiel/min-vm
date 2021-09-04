#include <stdio.h>

#include <util/strlen-s.h>

#define SOURCE "1234567890"

int main () {

    int len;

    len = strlen_s(SOURCE, 100); 

    printf("%d\n", len); // prints: 10

    len = strlen_s(SOURCE, 5);

    printf("%d\n", len); // prints: 5

    len = strlen_s(SOURCE, -1);

    printf("%d\n", len); // prints: 10

    return 0;
}