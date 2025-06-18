CC = gcc
CFLAGS = -std=c2x -Wall -lm -lpthread -lgmp
NAME = lob

all: main.c
	$(CC) $(CFLAGS) -o $(NAME) main.c
