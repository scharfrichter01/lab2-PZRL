CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o lab2.o
EXEC = sed_simplified

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c lab2.h
	$(CC) $(CFLAGS) -c main.c

lab2.o: lab2.c lab2.h
	$(CC) $(CFLAGS) -c lab2.c
