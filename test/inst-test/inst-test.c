#include <stdio.h>

#include <core/inst/inst.h>

int main (int argc, char const ** argv) {

    char ** inst_names;
    char * inst_name;

    for (int i = 0; (inst_names = MVM_INST_NM_LIST[i]); ++i) {
        
        for (int j = 0; (inst_name = inst_names[j]); ++j) {
            
            printf("%s\n", inst_name);

        }
    
    }

    return 0;
}