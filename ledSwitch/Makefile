#GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
BIN = Led_Server


all: test
	#$(GCC) -Wall src/gpio.c -o bin/$(BIN)

test:
	$(GCC) -Wall src/gpio.c src/gpio.h src/main.c -o bin/gpio

clean_all:
	rm -f bin/*

clean:
	rm -f bin/$(TEMP)
