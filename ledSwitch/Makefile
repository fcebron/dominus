#GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc
GCC = /root/buildroot-2017.08-compiled/output/host/bin/arm-linux-gcc


all:
	$(GCC) -Wall src/client.c -o bin/client
	$(GCC) -Wall src/server.c -o bin/server

test:
	$(GCC) -Wall src/gpio.c src/gpio.h src/test.c -o bin/test


clean_all:
	rm -f bin/*

clean:
	rm -f bin/$(TEMP)
