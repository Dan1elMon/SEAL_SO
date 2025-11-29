.section .multiboot
.align 4
    .long 0x1BADB002          # Multiboot Magic Number
    .long 0x0                 # Flags
    .long -(0x1BADB002 + 0x0) # Checksum: -(magic + flags)

.section .text
.global _start
_start:
    # Llamar a la función principal en C
    call kernel_main

    # Bucle infinito para evitar que el control vuelva al bootloader
hang:
    hlt
    jmp hang

