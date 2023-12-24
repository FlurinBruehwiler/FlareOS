
Article: https://dev.to/frosnerd/writing-my-own-boot-loader-3mld

Github Turoial: https://github.com/cfenollosa/os-tutorial

Birmingham PDF:  https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

OsDev Wiki: https://wiki.osdev.org/Main_Page

Book: https://littleosbook.github.io/

James Molly Tutorial: https://web.archive.org/web/20160412174753/http://www.jamesmolloy.co.uk/tutorial_html/index.html

How Computers Works: https://homepage.cs.uri.edu/faculty/wolfe/book/Readings/Reading04.htm

Assembly:

Registers:
`ax`: 16 bit register
`al`: lower 8 bits
`ah`: hight 8 bits

GP registers:
ax
bx

(Stack grows downwards, towards the bottom)
`bp`: top of the stack (fake news, [see](https://github.com/cfenollosa/os-tutorial/issues/269))
`sp`: bottom of the stack

Auxiliary register: temporary storage registers (not special)

Global Memory Offset:
`[org 0x7c00]` global offset to all memory locations, usefull to offset every memory addres to inside the boot sector, which is stored at `0x7c00`
![[Pasted image 20231223182130.png]]

Instructions:

`int` execute interupt
`int 0x10` 

`mov` move something into a register
`mov al, "2"` moves the ascii character 2 into al

`jmp` jump to a specific memory location

`je`: jump if equal

`push` push something onto the stack
`push 'A'`

`pop` pop something off the stack into a register
`pop` bx

`call` call a 'method', has the advantage over a jmp that one can use `ret`

`ret` return to where call was called :)

`pusha` pushed all registers to the stack
`popa` pops all registers from the stak

`db` define byte
`db "X"` write X to memory (statically at compile time) 

`dw` defines a word (two bytes / 16bits)

`times` repeats an instruction at compile time
`times 510 db 0` writes 510 `0` bytes