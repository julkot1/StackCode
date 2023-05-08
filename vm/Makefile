include ../Makefile.config

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stcvm: $(OBJ)
	$(CC) -o $@ src/*.c $(CFLAGS)
	rm $(OBJ)
debug: $(OBJ)
	$(CC) -Wall -ggdb -g -o $@ src/*.c $(CFLAGS)
	rm $(OBJ)
	gdb $@
