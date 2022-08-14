#!/bin/bash
#
# YKUR command application build script

rm -rf hidapi

echo "Checking for git..."
command -v git >/dev/null 2>&1 || { echo >&2 "Git is required and is not installed. Aborting."; exit 1; }

echo "Fetching latest version of hidapi..."
git clone https://github.com/signal11/hidapi.git

echo "Building hidapi..."
make --directory=hidapi/linux -f Makefile-manual
mkdir ykurcmd/linux
cp -fv hidapi/linux/libhidapi-hidraw.so ykurcmd/linux/

make --directory=hidapi/libusb -f Makefile-manual
cp -fv hidapi/libusb/libhidapi-libusb.so ykurcmd/linux/

echo "Configuring ykur app files..."

echo "#ifndef PLATFORMDEFS_H" > ykurcmd/platformdefs.h
echo "#define PLATFORMDEFS_H" >> ykurcmd/platformdefs.h
echo "#define _LINUX_" >> ykurcmd/platformdefs.h
echo "#endif" >> ykurcmd/platformdefs.h

echo "Building ykur command..."
make

