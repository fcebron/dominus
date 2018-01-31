#GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc
BIN = Led_Server
TEMP = Gpio
TEMP1 = Gpio_on
TEMP2 = Gpio_off

all:
	$(GCC) -Wall src/gpio.c -o bin/$(BIN)

gpio:
	$(GCC) -Wall src/gpio.c -o bin/$(TEMP)

gpio_on:
	$(GCC) -Wall src/gpio_on.c -o bin/$(TEMP1)

gpio_off:
	$(GCC) -Wall src/gpio_off.c -o bin/$(TEMP2)

clean_all:
	rm -f bin/*

clean:
	rm -f bin/$(TEMP)
