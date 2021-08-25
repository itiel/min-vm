INC_DIRS = include

INC = -I$(INC_DIRS)

CC = gcc

asm-test:
	$(CC) $(INC) -o test/asm-test/asm core/asm.c

clean:
	rm test/asm-test/asm