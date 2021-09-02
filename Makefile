CC = gcc
FLAGS = -I./ -Wall

TEST_DIR = test

ASM_TST = $(TEST_DIR)/asm-test
ASM_EX  = $(ASM_TST)/tok-scan-test.mvs
ASM_OUT = $(ASM_TST)/asm-test.out
ASM_IN  = $(ASM_TST)/asm-test.c
ASM_DEP = core/asm/asm.c

asm-test:
	$(CC) $(FLAGS) -o $(ASM_OUT) $(ASM_IN) $(ASM_DEP)

clean-asm-test:
	rm $(ASM_OUT)

INST_TST = $(TEST_DIR)/inst-test
INST_OUT = $(INST_TST)/inst-test.out
INST_IN  = $(INST_TST)/inst-test.c

inst-test:
	$(CC) $(FLAGS) -o $(INST_OUT) $(INST_IN)

clean-inst-test:
	rm $(INST_OUT)