ASM = nasm -f elf64
CC = x86_64-elf-gcc
LD = x86_64-elf-ld

CCFLAGS = -std=c2x
CCFLAGS += -Wall -Wextra -Wpedantic
CCFLAGS += -Wstrict-aliasing -Wno-pointer-arith
CCFLAGS += -Wno-unused-parameter -nostdlib -nostdinc
CCFLAGS += -ffreestanding -fno-stack-protector
CCFLAGS += -fno-builtin-function -fno-pie -fno-builtin
CCFLAGS += $(INCFLAGS)

INCFLAGS = -I include
INCFLAGS += -I include/kernel

KERNEL_SRC = $(shell find src/kernel -name "*.c")
KERNEL_OBJ = $(patsubst src/kernel/%.c, bin/obj/kernel/%.o, $(KERNEL_SRC))

X86_64_SRC = $(shell find src/x86_64 -name "*.c")
X86_64_OBJ = $(patsubst src/x86_64/%.c, bin/obj/x86_64/%.o, $(X86_64_SRC))

ASM_SRC = $(shell find src -name "*.asm")
ASM_OBJ = $(patsubst src/%.asm, bin/obj/%.o, $(ASM_SRC))

all: clean build

$(KERNEL_OBJ): bin/obj/kernel/%.o : src/kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) $< -o $@

$(X86_64_OBJ): bin/obj/x86_64/%.o : src/x86_64/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) $< -o $@

$(ASM_OBJ): bin/obj/%.o : src/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $< -o $@

build: $(ASM_OBJ) $(KERNEL_OBJ) $(X86_64_OBJ)
	mkdir -p bin/x86_64/iso/boot
	$(LD) -n -o ./bin/x86_64/iso/boot/kernel.bin -T buildenv/linker.ld $(ASM_OBJ) $(X86_64_OBJ) $(KERNEL_OBJ)
	grub-mkrescue -o bin/x86_64/iso/boot.iso bin/x86_64/iso

clean:
	rm -rf $(shell find bin/ -name "*.o")
	rm -rf $(shell find bin/ -name "*.iso")
	rm -rf $(shell find bin/ -name "*.bin")
