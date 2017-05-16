#!/bin/bash

echo installing ykush command...
sudo cp -f ykurcmd/bin/ykurcmd /usr/bin

echo installing shared libraries...
sudo cp -f ykurcmd/linux/libhidapi-hidraw.so /usr/lib/libhidapi-hidraw.so
sudo cp -f ykurcmd/linux/libhidapi-hidraw.so /usr/lib/libhidapi-hidraw.so.0

sudo cp -f ykurcmd/linux/libhidapi-libusb.so /usr/lib/libhidapi-libusb.so
sudo cp -f ykurcmd/linux/libhidapi-libusb.so /usr/lib/libhidapi-libusb.so.0

