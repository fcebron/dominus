#GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
BIN = Led_Server


all:
	$(GCC) -Wall src/gpio.c -o bin/$(BIN)

test:
	$(GCC) -Wall src/gpio.c src/gpio.h src/test.c -o bin/test

clean_all:
	rm -f bin/*

clean:
	rm -f bin/$(TEMP)
