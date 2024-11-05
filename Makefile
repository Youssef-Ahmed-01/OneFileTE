CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb 
LIBS = -lSDL2 -lSDL2_ttf -lm

te: main.c
	$(CC) $(CFLAGS) -o te main.c $(LIBS)
