CFLAGS=-I.
DEPS = src/include/.h
OBJ = src/main.o src/vm.o src/parser.o  src/tokens.o src/utils.o src/cli.o src/hashmap.o src/env.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stackcode: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm $(OBJ)
debug: $(OBJ)
	$(CC) -Wall -ggdb -g -o $@ src/main.c src/vm.c src/parser.c  src/tokens.c src/utils.c src/cli.c src/hashmap.c src/env.o
	rm $(OBJ)
	gdb $@