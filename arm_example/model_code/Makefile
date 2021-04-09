all:
	arm-none-linux-gnueabi-gcc -fno-builtin -nostdinc -c -o start.o start.S
	arm-none-linux-gnueabi-gcc -fno-builtin -nostdinc -c -o main.o main.c
	arm-none-linux-gnueabi-ld start.o main.o -Tmap.lds -o test.elf
	arm-none-linux-gnueabi-objcopy -O binary  test.elf test.bin
	arm-none-linux-gnueabi-objdump -D test.elf > test.dis
clean:
	rm -rf *.bak start.o main.o test.elf test.bin test.dis
