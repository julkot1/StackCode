include Makefile.config

all:
	rm -rf out
	mkdir out
	cd vm && make && mv stcvm ../out/stcvm
	cd camel && make && mv camelc ../out/camelc

clean:
	rm -rf out