CC = gcc
CFLAGS = -std=c2x -Wall
CLIBS = -lm -lgmp -lcapstone
CAPSTONE_PATH = C:/Program Files (x86)/capstone
NAME = cob

all: main.c
	$(CC) $(CFLAGS) -o $(NAME) main.c -I"$(CAPSTONE_PATH)/include" -L"$(CAPSTONE_PATH)/lib" $(CLIBS)

read:
	objdump -D -b binary -m arm code.bin

asm:
	as code.asm -o code.o
	ld code.o -o code