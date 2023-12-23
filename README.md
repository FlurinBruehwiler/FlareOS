# FlareOS

## Building
nasm -fbin boot_sect.asm -o boot_sect.bin

## Running
quemu-system-x86_64 boot_sect.bin
