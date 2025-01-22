ENTRY(start)

SECTIONS {
    . = 1M;  /* Kernel load address */

    .boot ALIGN(8) : {
        *(.multiboot_header)
    }

    .text ALIGN(8) : {
        *(.text)
    }

    .rodata ALIGN(8) : {
        *(.rodata)
    }

    .bss ALIGN(8) : {
        *(.bss)
        *(COMMON)
    }
}
