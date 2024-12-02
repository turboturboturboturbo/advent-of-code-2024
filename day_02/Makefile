CC=gcc
CPPFLAGS=-Wall -Wextra -Werror
CFLAGS=-I. -g
BIN=day02

DEPS=
OBJ= day_02.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(BIN) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)

re: fclean make

test: re
	./$(BIN)

.PHONY: clean re test fclean