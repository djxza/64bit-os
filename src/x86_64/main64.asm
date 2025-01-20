global long_mode_start    ; Export the symbol so the bootloader can jump here
extern kernel_main        ; Declare the external kernel_main function

section .text
bits 64

long_mode_start:
    ; Clear data segment registers to ensure a clean environment
    xor ax, ax            ; Set AX to 0
    mov ss, ax            ; Clear stack segment
    mov ds, ax            ; Clear data segment
    mov es, ax            ; Clear extra segment
    mov fs, ax            ; Clear FS segment
    mov gs, ax            ; Clear GS segment

    ; Print "ERR: " for debugging purposes
    mov dword [0xb8000], 0x4f524f45  ; "ERR: "
    mov dword [0xb8004], 0x4f3a4f52  ; "ROR: "
    mov byte [0xb800a], ' '          ; Space after "ROR:"

    ; Check if RSI (Multiboot2 info pointer) is NULL
    test rsi, rsi
    jz halt_error            ; If RSI is NULL, halt and show error message

    ; Align the stack to 16 bytes (required for the x86_64 ABI)
    sub rsp, 8            ; Ensure stack is aligned (subtract for return address)
    and rsp, -16          ; Align stack to 16-byte boundary

    ; Pass the Multiboot2 pointer from RSI to RDI (first argument in x86_64 ABI)
    mov rdi, rsi

    ; Store Multiboot2 pointer for debugging (optional)
    mov rax, rsi
    mov [0xa0000], rax

    ; Print "Proceeding to kernel_main" for debugging
    mov dword [0xb8008], 0x50726f63  ; "Proc"
    mov dword [0xb800c], 0x65656469  ; "eding"

    ; Call the kernel's main function
    call kernel_main

    ; Print a message if kernel_main returns unexpectedly
    mov dword [0xb8000], 0x4f524f45  ; "ERR: "
    mov dword [0xb8004], 0x4f3a4f52  ; "ROR: "
    mov byte [0xb800a], 'K'          ; Add "K" after error message

    ; Halt the CPU if kernel_main returns
halt_error:
    hlt                   ; Halt the CPU
    jmp halt_error        ; Infinite loop to prevent further execution
