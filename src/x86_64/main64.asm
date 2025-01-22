global long_mode_start
global multiboot_info

extern kernel_main

section .bss
align 8
multiboot_info: resq 1  ; Reserve 8 bytes for the multiboot info address

section .text
bits 64

long_mode_start:
    	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Store the Multiboot info pointer in the reserved variable
    mov [multiboot_info], rdi

    ; Pass the Multiboot info pointer to kernel_main
    mov rdi, [multiboot_info]
    call kernel_main

    ; Halt the CPU after kernel_main returns
    hlt
