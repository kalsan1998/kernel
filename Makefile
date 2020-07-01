
make: main.c
	arm-none-eabi-gcc -nostartfiles -O2 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -march=armv8-a+crc -mcpu=cortex-a72 main.c -o kernel.elf
	arm-none-eabi-objcopy kernel.elf -O binary kernel.img

flash:
	cp kernel.img /media/kalsan/boot

umount:
	umount /media/kalsan/boot
	umount /media/kalsan/rootfs

clean:
	rm *.elf *.img

	