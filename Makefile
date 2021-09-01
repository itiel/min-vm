CC = gcc
FLAGS = -I./ -Wall 

ASM_TST = test/asm-test
ASM_EX = $(ASM_TST)/tok-scan-test.mvs 
ASM_OUT = $(ASM_TST)/asm-test.out 
ASM_IN = $(ASM_TST)/asm-test.c
ASM_DEP = core/asm/asm.c

asm-test:
	$(CC) $(FLAGS) -o $(ASM_OUT) $(ASM_IN) $(ASM_DEP)

clean-asm-test:
	rm $(ASM_OUT)