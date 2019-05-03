all:
	gcc *.c libraries/*.c -o chase.x -lm -lncurses -Wall -Wextra
