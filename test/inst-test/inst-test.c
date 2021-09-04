#include <stdio.h>

#include <core/inst/inst.h>

int main () {

    const mvm_inst_t * inst;
    const char       * inst_name;

    for (int i = 0; (inst = MVM_INST_SET[i]); ++i) {
 
        for (int j = 0; (inst_name = inst->names[j]); ++j) {
 
            printf("%s\t: 0x%x\n", 
                inst_name, 
                mvm_inst_op_find((char *) inst_name));

        }
 
    }

    inst_name = "invalid";

    printf("%s\t: 0x%x\n", 
                inst_name, 
                mvm_inst_op_find((char *) inst_name));

    return 0;

}