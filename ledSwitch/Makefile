GCC = gcc
BIN = Led_Server
TEMP = Gpio

all:
	$(GCC) --Wall src/led_server.c -o bin/$(BIN)

gpio:
	$(GCC) --Wall src/gpio.c -o bin/$(Gpio)

clean:
	rm -f bin/*