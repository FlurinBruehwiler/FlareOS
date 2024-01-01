# FlareOS

The goal of this project is to create an operating system from scratch. The only function it should have is to run Minecraft. Not the real Minecraft but a [Minecraft Clone written in C](https://github.com/FlurinBruehwiler/MinecraftInC).

## Building
`sudo apt install nasm`

`nasm -fbin boot_sect.asm -o boot_sect.bin`

## Running
`sudo apt install quemu-system-x86_64`

`quemu-system-x86_64 boot_sect.bin`
