INC_DIRS = include

INC = -I$(INC_DIRS)

CC = gcc

asm:
	$(CC) $(INC) -o test/asm-test/asm core/asm.c