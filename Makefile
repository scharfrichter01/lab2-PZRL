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

clean:
	rm -f $(OBJ) $(EXEC)

test:
	./sed_simplified input.txt -r "old text" "new text"
	./sed_simplified input.txt -d "delete"
	./sed_simplified input.txt -i -f "Prefix: "
	./sed_simplified input.txt -i -b " - Suffix"
