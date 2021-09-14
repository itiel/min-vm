/*
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 12/09/2021
*/

/* -- Includes -- */

#include <core/vm/ram.h>

#include <stdlib.h>
#include <stdio.h>

#include <util/err.h>
#include <util/bool.h>
#include <util/chval.h>

i32 mvm_vm_ram_init (mvm_vm_ram_t * ram_instnc) {

    if (!ram_instnc) {

        put_error_method(
            "mvm_vm_ram_init",
            "RAM instance pointer should not be NULL."
        );

        return FALSE;

    }

    ram_instnc->size = MVM_RAM_SZ;

    ram_instnc->buffer = malloc(MVM_RAM_SZ * sizeof(mvm_vm_word_t));

    if (!ram_instnc->buffer) {

        put_error_method(
            "mvm_vm_ram_init",
            "Something unexpected happened while allocating RAM."
        );

        return FALSE;

    }

    return TRUE;

}

i32 mvm_vm_ram_kill (mvm_vm_ram_t * ram_instnc) {

    if (!ram_instnc) {

        put_error_method(
            "mvm_vm_ram_kill",
            "RAM instance pointer should not be NULL."
        );

        return FALSE;

    }

    free(ram_instnc->buffer);

    return TRUE;

}

i32 mvm_vm_ram_dump (mvm_vm_ram_t * ram_instnc) {

    i32            col;
    i32            same;
    i32            same_last;
    i32            dif;
    mvm_vm_uword_t row[MVM_RAM_DMP_RW];


    if (!ram_instnc) {

        put_error_method(
            "mvm_vm_ram_dump",
            "RAM instance pointer should not be NULL."
        );

        return FALSE;

    }

    same      = TRUE;
    same_last = FALSE;

    for (int i = 0; i < ram_instnc->size; ++i) {

        col = i % MVM_RAM_DMP_RW;
        
        same = same && row[col] == ram_instnc->buffer[i];

        row[col] = ram_instnc->buffer[i];

        // Do this every 16 bytes (MVM_RAM_DMP_RW) or when finished

        if (col + 1 == MVM_RAM_DMP_RW || i + 1 == ram_instnc->size) {

            // Don't print lines that repeat

            if (same) {

                if (!same_last)
                    printf("  *\n"); 
                
                same_last = TRUE;

                continue;
            
            }

            same      = TRUE;
            same_last = FALSE;

            printf("%04x  ", i - col);

            for (int j = 0; j < col + 1; ++j) {
            
                printf("%02x ", row[j]);

                if (j + 1 == MVM_RAM_DMP_RW / 2) {
                    
                    putchar(' ');
                
                }
            
            }

            if ((dif = MVM_RAM_DMP_RW - col - 1)) {

                for (int j = 0; j < dif; ++j) {

                    printf("   ");

                }

                if (dif > MVM_RAM_DMP_RW / 2) {
                
                    putchar(' ');
                
                }

            }

            putchar('|');

            for (int j = 0; j < col + 1; ++j) {
            
                putchar(
                    ch_is_printable(row[j]) ? 
                    row[j] : 
                    MVM_RAM_DMP_CH
                );
            
            }

            putchar('|');

            putchar('\n');
        
        }

    }

    return TRUE;

} 