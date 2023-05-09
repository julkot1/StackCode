include ../Makefile.config

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lmpc

camelc: $(OBJ)
	$(CC) -Wall -ggdb -o $@ src/*.c $(CFLAGS) -lmpc
	rm $(OBJ)

debug: $(OBJ)
	$(CC) -Wall -ggdb -g -o $@ src/*.c $(CFLAGS)
	rm $(OBJ)

