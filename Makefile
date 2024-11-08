CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb 
LIBS = -lSDL2 -lSDL2_ttf -lm

OneFile: main.c
	$(CC) $(CFLAGS) -o OneFile main.c $(LIBS)
