CFLAGS=-I.
DEPS = src/include/.h
OBJ = src/*.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stackcode: $(OBJ)
	$(CC) -o $@ src/*.c $(CFLAGS)
	rm $(OBJ)
debug: $(OBJ)
	$(CC) -Wall -ggdb -g -o $@ src/*.c
	rm $(OBJ)
	gdb $@