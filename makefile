CC = gcc
CFLAGS = -std=c2x -Wall
CLIBS = -lm -lgmp
NAME = cob

all: main.c
	$(CC) $(CFLAGS) -o $(NAME) main.c $(CLIBS)
