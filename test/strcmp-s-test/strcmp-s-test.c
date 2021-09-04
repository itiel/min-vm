#include <stdio.h>

#include <util/strcmp-s.h>

#define STR1 "ABCDEFGHIJKLMNOP"
#define STR2 "ABCDEFGHIJKLMNOQ"
#define STR3 "abcdefghijklmnop"

#define bool2str(_val) \
    (_val ? "true" : "false")

int main () {

    int max_len;
    int result;
 
    printf("STR1 = %s\n", STR1);
    printf("STR2 = %s\n", STR2);
    printf("STR3 = %s\n\n", STR3);

    // Case sensitive

    printf("-- Case senitive --\n\n");

    max_len = 20;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_s(STR1, STR1, max_len); 

    printf("STR1 vs STR1 = %s\n", bool2str(result)); 

    result = strcmp_s(STR1, STR2, max_len); 

    printf("STR1 vs STR2 = %s\n", bool2str(result)); 

    result = strcmp_s(STR1, STR3, max_len); 

    printf("STR1 vs STR3 = %s\n\n", bool2str(result)); 

    max_len = 10;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_s(STR1, STR2, max_len); 

    printf("STR1 vs STR2 = %s\n\n", bool2str(result)); 

    max_len = -1;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_s(STR1, STR1, max_len); 

    printf("STR1 vs STR1 = %s\n", bool2str(result)); 

    result = strcmp_s(STR1, STR2, max_len); 

    printf("STR1 vs STR2 = %s\n\n", bool2str(result)); 

    // Case insensitive

    printf("-- Case insenitive --\n\n");

    max_len = 20;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_case_s(STR1, STR1, max_len); 

    printf("STR1 vs STR1 = %s\n", bool2str(result)); 

    result = strcmp_case_s(STR1, STR2, max_len); 

    printf("STR1 vs STR2 = %s\n", bool2str(result)); 

    result = strcmp_case_s(STR1, STR3, max_len); 

    printf("STR1 vs STR3 = %s\n\n", bool2str(result)); 

    max_len = 10;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_case_s(STR2, STR3, max_len); 

    printf("STR2 vs STR3 = %s\n\n", bool2str(result)); 

    max_len = -1;

    printf("max_len = %d\n\n", max_len);

    result = strcmp_case_s(STR1, STR2, max_len); 

    printf("STR1 vs STR2 = %s\n", bool2str(result)); 

    result = strcmp_case_s(STR2, STR3, max_len); 

    printf("STR2 vs STR3 = %s\n", bool2str(result)); 

    result = strcmp_case_s(STR1, STR3, max_len); 

    printf("STR1 vs STR3 = %s\n\n", bool2str(result)); 

    return 0;

}