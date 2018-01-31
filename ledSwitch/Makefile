GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
SONAME = libgpio.so
SERVER = dominus0_server
CLIENT = dominus1_client

all: init gpio client server

init:
	mkdir -p bin lib include

server:
	$(GCC) -Wall src/server.c -o bin/$(SERVER) -I include/ -L lib/ -lgpio
	cp src/server.conf bin/server.conf

client:
	$(GCC) -Wall src/client.c -o bin/$(CLIENT)
	cp src/client.conf bin/client.conf

gpio: init
	$(GCC) -g -c -fPIC src/lib/gpio/gpio.c -o src/lib/gpio/gpio.o
	$(GCC) -g -shared -Wl,-soname,$(SONAME) -o src/lib/gpio/$(SONAME) src/lib/gpio/gpio.o
	cp src/lib/gpio/gpio.h include/
	mv src/lib/gpio/$(SONAME) lib/

test:
	$(GCC) -Wall src/lib/gpio/gpio.c include/gpio.h src/lib/gpio/test.c -o bin/test

clean:
	rm -rf bin lib include
	rm src/lib/gpio/gpio.o
