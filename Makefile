CFLAGS=-I.
DEPS = src/include/.h
OBJ = src/main.o src/vm.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stackcode: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm $(OBJ)