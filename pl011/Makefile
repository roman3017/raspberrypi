
ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding

gcc : uartx01.hex uartx01.bin kernel.img

all : gcc clang

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

pl011.o : pl011.c
	$(ARMGNU)-gcc $(COPS) -c pl011.c -o pl011.o

uartx01.o : uartx01.c
	$(ARMGNU)-gcc $(COPS) -c uartx01.c -o uartx01.o

uartx01.elf : memmap vectors.o pl011.o uartx01.o
	$(ARMGNU)-ld vectors.o pl011.o uartx01.o -T memmap -o uartx01.elf
	$(ARMGNU)-objdump -D uartx01.elf > uartx01.list

uartx01.bin : uartx01.elf
	$(ARMGNU)-objcopy uartx01.elf -O binary uartx01.bin

uartx01.hex : uartx01.elf
	$(ARMGNU)-objcopy uartx01.elf -O ihex uartx01.hex

kernel.img : uartx01.bin
	cp uartx01.bin kernel.img
