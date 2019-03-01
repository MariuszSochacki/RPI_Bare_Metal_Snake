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

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
OBJS_PATH := $(patsubst %.o,$(OBJS_DIR)%.o,$(OBJS))

ELF_PATH := $(ELF_DIR)out.elf
IMAGE_PATH := $(IMAGE_DIR)kernel.img
SDCARD_PATH := $(SDCARD_DIR)sdcard.img

LOOP_PATH_CMD := sudo losetup --show --find --partscan $(SDCARD_PATH)

.PHONY: all
all: image

.PHONY: directories
directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJS_DIR)
	mkdir -p $(ELF_DIR)
	mkdir -p $(ELF_DIR)

$(OBJS_DIR)boot.o: boot.s
	$(AS) -c boot.s -o $(OBJS_DIR)boot.o

$(OBJS_DIR)%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

.PHONY: elf
elf: directories $(OBJS_DIR)boot.o $(OBJS_PATH)
	$(LD) -T link.ld $(OBJS_DIR)boot.o $(OBJS_PATH) -o $(ELF_PATH)

.PHONY: image
image: elf
	$(OBJCOPY) $(ELF_PATH) -O binary $(IMAGE_PATH)

.PHONY: sdcard
sdcard: image
#TODO: Put it back into Makefile instead of a shell script?
	./build_image.sh $(SDCARD_PATH) $(TEMPFS_DIR) $(IMAGE_PATH)

.PHONY: clean
clean:
	-sudo umount $(TEMPFS_DIR)
	rm -rf $(BUILD_DIR)
