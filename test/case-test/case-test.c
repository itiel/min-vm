#include <stdio.h>

#include <util/case.h>
#include <util/strlen-s.h>

#define SOURCE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

int main() {

    int source_len;
    int result;

    // Print og string
 
    printf("%s\n", SOURCE); 

    // Take og string's length

    source_len = strlen_s(SOURCE, 100);

    // Create buffer

    char buffer[source_len + 1];

    // Load lower-case string to buffer 

    result = str_to_lower(SOURCE, source_len, buffer, source_len);

    // NULL terminate buffer

    buffer[result] = '\0';

    // Print buffer

    printf("%s\n", buffer); 

    // Load upper-case string to buffer 
    // This time, the source is the buffer itself

    result = str_to_upper(buffer, source_len, buffer, source_len);

    // NULL terminate buffer

    buffer[result] = '\0';

    // Print buffer
 
    printf("%s\n", buffer); 

    return 0;
 
}