# Makefile for project 2
#
# You should not need to modify this file.

CC		= gcc

CFLAGS		= -g  -Wall -std=c99

CLIBS		= -lm 

all: program

program: main.o float.o
	$(CC) $(CFLAGS) -o program main.o float.o $(CLIBS) 

main.o: main.c float.h
	$(CC) $(CFLAGS) -c main.c

float.o: float.c float.h
	$(CC) $(CFLAGS) -c float.c

run: program
	./program < test.in > out

clean:
	rm -f *~ *.o a.out core program out
