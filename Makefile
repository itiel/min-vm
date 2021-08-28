INC_DIRS = include
INC = -I$(INC_DIRS)
WALL = -Wall
CC = gcc

asm-test:
	$(CC) $(WALL) $(INC) -o test/asm-test/asm core/asm.c

clean:
	rm test/asm-test/asm