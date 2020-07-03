OUT_DIR=./out
OBJ_DIR=./obj
SRC_DIR=./src
INCLUDE_DIR=./include
CC=arm-none-eabi-gcc
CFLAGS= \
	-nostartfiles \
	-O2 \
	-mfpu=crypto-neon-fp-armv8 \
	-mfloat-abi=hard \
	-march=armv8-a+crc \
	-mcpu=cortex-a72 \
	-I $(INCLUDE_DIR)

DEPS:=$(wildcard $(INCLUDE_DIR)/*.h)
SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

kernel: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT_DIR)/kernel.elf
	arm-none-eabi-objcopy $(OUT_DIR)/kernel.elf -O binary $(OUT_DIR)/kernel.img

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

flash:
	cp out/*.img /media/kalsan/boot

umount:
	umount /media/kalsan/boot
	umount /media/kalsan/rootfs

.PHONY: clean

clean:
	rm $(OUT_DIR)/*
	rm $(OBJ_DIR)/*

	