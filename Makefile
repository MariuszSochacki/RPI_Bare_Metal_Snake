CC_DIR := /opt/cross-compilers/aarch64/
GCC := $(CC_DIR)bin/aarch64-elf-gcc
AS := $(CC_DIR)bin/aarch64-elf-as
LD := $(CC_DIR)bin/aarch64-elf-ld
OBJCOPY := $(CC_DIR)bin/aarch64-elf-objcopy

CFLAGS := -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -nodefaultlibs
BUILD_DIR := build/
OBJS_DIR := $(BUILD_DIR)objs/
ELF_DIR := $(BUILD_DIR)
IMAGE_DIR := $(BUILD_DIR)
SDCARD_DIR := $(BUILD_DIR)
TEMPFS_DIR := $(BUILD_DIR)tempfs/

SRC_DIR := src/
INCLUDE_DIR := include/
MISC_DIR := misc/
ADDITIONAL_SD_DIR := $(MISC_DIR)sdcard/

SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJS_DIR)%.o)

ELF_PATH := $(ELF_DIR)out.elf
IMAGE_PATH := $(IMAGE_DIR)kernel.img
SDCARD_PATH := $(SDCARD_DIR)sdcard.img

CFLAGS += -I$(INCLUDE_DIR)

.PHONY: all
all: image

$(OBJS_DIR)boot.o: $(SRC_DIR)boot.s
	mkdir -p $(OBJS_DIR)
	$(AS) -c $(SRC_DIR)boot.s -o $(OBJS_DIR)boot.o

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

.PHONY: elf
elf: $(OBJS_DIR)boot.o $(OBJS)
	mkdir -p $(ELF_DIR)
	$(LD) -T $(MISC_DIR)link.ld $(OBJS_DIR)boot.o $(OBJS) -o $(ELF_PATH)

.PHONY: image
image: elf
	mkdir -p $(IMAGE_DIR)
	$(OBJCOPY) $(ELF_PATH) -O binary $(IMAGE_PATH)

.PHONY: sdcard
sdcard: image
#TODO: Put it back into Makefile instead of a shell script?
	./$(MISC_DIR)build_image.sh $(SDCARD_PATH) $(TEMPFS_DIR) $(IMAGE_PATH) $(MISC_DIR)sfdisk.script $(ADDITIONAL_SD_DIR)

.PHONY: clean
clean:
	-sudo umount $(TEMPFS_DIR)
	rm -rf $(BUILD_DIR)
