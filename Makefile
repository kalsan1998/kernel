
make: main.c
	arm-none-eabi-gcc -nostartfiles -O2 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -march=armv8-a+crc -mcpu=cortex-a72 main.c -o kernel8.elf
	arm-none-eabi-objcopy kernel8.elf -O binary kernel8.img

flash:
	cp kernel8.img /media/kalsan/boot

clean:
	rm *.elf *.img

	