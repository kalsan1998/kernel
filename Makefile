CC=arm-none-eabi-gcc
CFLAGS= \
	-nostartfiles \
	-O2 \
	-mfpu=crypto-neon-fp-armv8 \
	-mfloat-abi=hard \
	-march=armv8-a+crc \
	-mcpu=cortex-a72 \
	-fPIC \
	-I $(INCLUDE_DIR)
ASMFLAGS= \
	-I $(INCLUDE_DIR)

SRC_DIR=./src
ASM_DIR=$(SRC_DIR)/asm
INCLUDE_DIR=./include
OUT_DIR=./out
OBJ_DIR=./obj
ASM_OBJ_DIR=$(OBJ_DIR)/asm

DEPS:=$(wildcard $(INCLUDE_DIR)/*.h)
SRC:=$(wildcard $(SRC_DIR)/*.c)
ASM:=$(wildcard $(ASM_DIR)/*.S)
OBJ:=$(DEPS:$(INCLUDE_DIR)/%.h=$(OBJ_DIR)/%.o)
OBJ_ASM:=$(ASM:$(ASM_DIR)/%.S=$(ASM_OBJ_DIR)/%.o)

BOOT=$(SRC_DIR)/boot.c
KERNEL=$(SRC_DIR)/kernel.c

kernel: $(KERNEL) $(OBJ) $(OBJ_ASM)
	$(CC) $(CFLAGS) $^ -o $(OUT_DIR)/client_kernel.elf
	arm-none-eabi-objcopy $(OUT_DIR)/client_kernel.elf -O binary $(OUT_DIR)/client_kernel.img

boot: $(BOOT) $(OBJ) $(OBJ_ASM)
	$(CC) $(CFLAGS) $^ -o $(OUT_DIR)/boot_kernel.elf
	arm-none-eabi-objcopy $(OUT_DIR)/boot_kernel.elf -O binary $(OUT_DIR)/boot_kernel.img

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_DIR)/%.S $(DEPS)
	$(CC) $(ASMFLAGS) -c $< -o $@

flash:
	rm /media/kalsan/boot/kernel*.img
	cp out/boot_kernel.img /media/kalsan/boot/kernel.img

umount:
	umount /media/kalsan/boot
	umount /media/kalsan/rootfs

.PHONY: clean

clean:
	rm -f $(ASM_OBJ_DIR)/*o
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OUT_DIR)/*

	