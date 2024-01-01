[org 0x7c00] ; tell the assembler that our offset is bootsector code
mov ah, 0x0e

mov bx, 0

loop:
    inc bx
    mov al, bl
    add al, 48
    int 0x10
    cmp bx, 400
    je endloop
    jmp loop

endloop:


; that's it! we can hang now
jmp $

; data
HELLO:
    db 'Hello, World', 0

GOODBYE:
    db 'Goodbye', 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55
