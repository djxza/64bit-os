section .multiboot_header
align 8
header_start:
    dd 0xe85250d6                ; Multiboot2 magic number
    dd 0                         ; Architecture (must be 0 for i386+)
    dd header_end - header_start ; Header length
    dd 0x100000000 -(0xe85250d6 + 0 + (header_end - header_start)) ; Checksum



    ; Tag: End of header
    align 8
    dw 0                      ; Tag type (0 = end)
    dw 8                      ; Tag size (8 bytes)

header_end:
