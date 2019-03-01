#!/bin/sh
set -e

SDCARD_PATH=$1
TEMPFS_DIR=$2
IMAGE_PATH=$3

mkdir -p $TEMPFS_DIR
dd if=/dev/zero of=$SDCARD_PATH bs=1024k count=64 && sync
sfdisk $SDCARD_PATH < sfdisk.script
sudo losetup --show --find --partscan $SDCARD_PATH > loop_path
#TODO: Hack, fix me
LOOP_PATH=$(cat loop_path)
rm loop_path

sudo mkfs.vfat -F 32 "$LOOP_PATH"p1
sudo mount -t vfat -o loop "$LOOP_PATH"p1 $TEMPFS_DIR
sudo cp bootcode.bin "$TEMPFS_DIR/bootcode.bin"
sudo cp start.elf "$TEMPFS_DIR/start.elf"
sudo cp fixup.dat "$TEMPFS_DIR/fixup.dat"

sudo cp $IMAGE_PATH "$TEMPFS_DIR/kernel8.img"
sync
sudo umount $TEMPFS_DIR
sudo losetup -d $LOOP_PATH
