#!/bin/sh
set -e

SDCARD_PATH=$1
TEMPFS_DIR=$2
IMAGE_PATH=$3
SFDISK_SCRIPT_PATH=$4
ADDITIONAL_SD_DIR=$5

mkdir -p $TEMPFS_DIR
dd if=/dev/zero of=$SDCARD_PATH bs=1024k count=64 && sync
sfdisk $SDCARD_PATH < $4
sudo losetup --show --find --partscan $SDCARD_PATH > loop_path
#TODO: Hack, fix me
LOOP_PATH=$(cat loop_path)
rm loop_path

sudo mkfs.vfat -F 32 "$LOOP_PATH"p1
sudo mount -t vfat -o loop "$LOOP_PATH"p1 $TEMPFS_DIR
sudo cp $ADDITIONAL_SD_DIR* $TEMPFS_DIR

sudo cp $IMAGE_PATH "$TEMPFS_DIR/kernel8.img"
sync
sudo umount $TEMPFS_DIR
sudo losetup -d $LOOP_PATH
