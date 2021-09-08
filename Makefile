CC    = gcc
STD   = c99
FLAGS = -std=$(STD) -Isrc/ -Wall

## Tests ##

TEST_DIR = test
SRC_DIR  = src

# Assembler test

ASM_NM  = asm-test
ASM_DIR = $(TEST_DIR)/$(ASM_NM)
ASM_EX  = $(ASM_DIR)/tok-scan-test.mvs
ASM_OUT = $(ASM_DIR)/$(ASM_NM).out
ASM_IN  = $(ASM_DIR)/$(ASM_NM).c
ASM_DEP = $(SRC_DIR)/core/asm.c

asm-test:
	$(CC) $(FLAGS) -o $(ASM_OUT) $(ASM_IN) $(ASM_DEP)

clean-asm-test:
	rm $(ASM_OUT)

# Instructions test

INST_NM  = inst-test
INST_DIR = $(TEST_DIR)/$(INST_NM)
INST_OUT = $(INST_DIR)/$(INST_NM).out
INST_IN  = $(INST_DIR)/$(INST_NM).c

inst-test:
	$(CC) $(FLAGS) -o $(INST_OUT) $(INST_IN)

clean-inst-test:
	rm $(INST_OUT)

# Case conversion test

CASE_NM  = case-test
CASE_DIR = $(TEST_DIR)/$(CASE_NM)
CASE_OUT = $(CASE_DIR)/$(CASE_NM).out
CASE_IN  = $(CASE_DIR)/$(CASE_NM).c

case-test:
	$(CC) $(FLAGS) -o $(CASE_OUT) $(CASE_IN)

clean-case-test:
	rm $(CASE_OUT)

# String length test

LEN_NM  = strlen-s-test
LEN_DIR = $(TEST_DIR)/$(LEN_NM)
LEN_OUT = $(LEN_DIR)/$(LEN_NM).out
LEN_IN  = $(LEN_DIR)/$(LEN_NM).c

strlen-s-test:
	$(CC) $(FLAGS) -o $(LEN_OUT) $(LEN_IN)

clean-strlen-s-test:
	rm $(LEN_OUT)

# String compare test

COMP_NM  = strcmp-s-test
COMP_DIR = $(TEST_DIR)/$(COMP_NM)
COMP_OUT = $(COMP_DIR)/$(COMP_NM).out
COMP_IN  = $(COMP_DIR)/$(COMP_NM).c

strcmp-s-test:
	$(CC) $(FLAGS) -o $(COMP_OUT) $(COMP_IN)

clean-strcmp-s-test:
	rm $(COMP_OUT)
