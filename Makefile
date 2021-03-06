GNU=aarch64-none-elf
CFLAGS= \
	-mgeneral-regs-only \
	-ffreestanding \
	-nostartfiles \
	-O2 \
	-I $(INCLUDE_DIR) \

ASMFLAGS= \
	-I $(INCLUDE_DIR) \
	-D ASSEMBLER \

LINKER=./linker.ld

BOOT_DIR=./boot
SRC_DIR=./src
ASM_DIR=$(SRC_DIR)/asm
INCLUDE_DIR=./include
OUT_DIR=./out
OBJ_DIR=./obj
ASM_OBJ_DIR=$(OBJ_DIR)/asm

DEPS:=$(wildcard $(INCLUDE_DIR)/*.h)
SRC:=$(wildcard $(SRC_DIR)/*.c)
ASM:=$(wildcard $(ASM_DIR)/*.S)
OBJ:=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_ASM:=$(ASM:$(ASM_DIR)/%.S=$(ASM_OBJ_DIR)/%.o)

kernel: $(OBJ) $(OBJ_ASM)
	$(GNU)-gcc $(CFLAGS) $^ -T $(LINKER) -o $(OUT_DIR)/client_kernel.elf
	$(GNU)-objcopy $(OUT_DIR)/client_kernel.elf -O binary $(OUT_DIR)/client_kernel.img
	$(GNU)-objdump -S $(OUT_DIR)/client_kernel.elf > $(OUT_DIR)/kernel_dump.disasm

.PHONY: boot
boot:
	$(MAKE) -C $(BOOT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(GNU)-gcc $(CFLAGS) -c $< -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_DIR)/%.S $(DEPS)
	$(GNU)-gcc $(ASMFLAGS) -c $< -o $@

flash:
	rm /media/kalsan/boot/kernel*.img
	cp $(BOOT_DIR)/out/boot_kernel.img /media/kalsan/boot/kernel8.img

umount:
	umount /media/kalsan/boot
	umount /media/kalsan/rootfs

.PHONY: clean

clean:
	rm -f $(ASM_OBJ_DIR)/*o
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OUT_DIR)/*
	$(MAKE) -C $(BOOT_DIR) clean

	