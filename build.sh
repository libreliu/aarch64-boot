#!/bin/bash

CUR_DIR=$(pwd)
SCRIPT_PATH=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "${SCRIPT_PATH}")

echo "aarch64-boot builder for RPi 3b+"

if [ $# -ne 3 ]; then
    echo "Usage: $0 kernel_file_path dtb_file_path"
    echo "When success, kernel8.img will be copied here."
    exit 1
fi

cp $1 "${SCRIPT_DIR}/src/kernel.elf.bin"
cp $2 "${SCRIPT_DIR}/src/devicetree.dtb"

cd "${SCRIPT_DIR}/src"
make clean
make

cp kernel8.img "${CUR_DIR}"

echo "Done."