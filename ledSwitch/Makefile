GCC = /root/buildroot-2017.08/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
BIN = Led_Server
TEMP = Gpio

all:
	$(GCC) -Wall src/gpio.c -o bin/$(BIN)

gpio:
	$(GCC) -Wall src/gpio.c -o bin/$(TEMP)

clean_all:
	rm -f bin/*

clean:
	rm -f bin/$(TEMP)
