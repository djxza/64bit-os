ENTRY(start)

SECTIONS {
    . = 0x10000;                /* Kernel load address (64 KiB) */

    .multiboot_header : AT(0x1000) { /* Ensure the Multiboot header is at the correct location */
        *(.multiboot_header)
    }
    .text : {
        *(.text*)
    }
    .rodata : {
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }
    .bss : {
        *(COMMON)
        *(.bss*)
    }
}
