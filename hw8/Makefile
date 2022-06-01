CC = clang

CFLAGS = -Wall -Wpedantic -Werror -Wextra -g

all: businessdb

businessdb: businessdb.o database_functions.o
	$(CC) database_functions.o businessdb.o -o businessdb

database_functions.o: database_functions.c database_functions.h
	$(CC) $(CFLAGS) -c database_functions.c

businessdb.o: businessdb.c database_functions.h
	$(CC) $(CFLAGS) -c businessdb.c

clean:
	rm -f businessdb businessdb.o database_functions.o

format:
	clang-format -i -style=file *.[ch]

