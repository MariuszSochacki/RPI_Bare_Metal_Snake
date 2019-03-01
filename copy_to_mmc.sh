#!/bin/sh
if [ -e /dev/mmcblk0p1 ]
then
  sudo umount /dev/mmcblk0
  sudo umount /dev/mmcblk0p1
  sudo dd if=build/sdcard.img of=/dev/mmcblk0 status=progress
  sync
else
  echo "No sdcard detected!"
fi