#GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
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
