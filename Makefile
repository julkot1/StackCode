<<<<<<< HEAD
include Makefile.config
=======
CFLAGS=-I. -O3
DEPS = include/*.h
OBJ = src/*.o
>>>>>>> 29540adf093800f27124632d2ad4773b89862785

all:
	rm -rf out
	mkdir out
	cd vm && make && mv stcvm ../out/stcvm
	cd camel && make && mv camelc ../out/camelc
	
clean:
	rm -rf out