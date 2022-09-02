CFLAGS=-I.
DEPS = src/include/.h
OBJ = src/main.o src/vm.o src/parser.o  src/tokens.o src/utils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stackcode: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm $(OBJ)
debug: $(OBJ)
	$(CC) -Wall -ggdb -g -o $@ src/main.c src/vm.c src/parser.c  src/tokens.c src/utils.c
	rm $(OBJ)
	gdb $@