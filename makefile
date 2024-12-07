ASM = nasm -f elf64
CC = x86_64-elf-gcc
LD = x86_64-elf-ld

CCFLAGS  = -std=c2x
# CCFLAGS += -O2 
CCFLAGS += -v -Wall
CCFLAGS += -Wextra -Wpedantic
CCFLAGS += -Wstrict-aliasing
CCFLAGS += -Wno-pointer-arith
CCFLAGS += -Wno-unused-parameter
CCFLAGS += -nostdlib -nostdinc
CCFLAGS += -ffreestanding
CCFLAGS += -fno-stack-protector
CCFLAGS += -fno-builtin-function
CCFLAGS += -fno-pie -fno-builtin
CCFLAGS += $(INCFLAGS)

INCFLAGS  = -I include
INCFLAGS += -I include/kernel

# Kernel object files
KERNEL_SRC = $(shell find src/kernel -name "*.c")
KERNEL_OBJ = $(patsubst src/kernel/%.c, bin/obj/kernel/%.o, $(KERNEL_SRC))

# X86_64 object files
X86_64_SRC = $(shell find src/x86_64 -name "*.c")
X86_64_OBJ = $(patsubst src/x86_64/%.c, bin/obj/x86_64/%.o, $(X86_64_SRC))

# Assembly object files
ASM_SRC = $(shell find src -name "*.asm")
ASM_OBJ = $(patsubst src/x86_64/%.asm, bin/obj/x86_64/%.o, $(ASM_SRC))

# Compile kernel C files
$(KERNEL_OBJ): bin/obj/kernel/%.o : src/kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) $< -o $@

# Compile x86_64 C files
$(X86_64_OBJ): bin/obj/x86_64/%.o : src/x86_64/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) $< -o $@

# Assemble assembly files
$(ASM_OBJ): bin/obj/x86_64/%.o : src/x86_64/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $< -o $@

echo:
	@echo "HELLO!"

enter_docker:
	powershell -Command "docker run --rm -it -v $$(pwd):/root/env solis_os"

build-x86_64: build

build: $(ASM_OBJ) $(KERNEL_OBJ) $(X86_64_OBJ)
	$(LD) -n -o ./bin/x86_64/iso/boot/kernel.bin -T buildenv/linker.ld $(KERNEL_OBJ) $(X86_64_OBJ) $(ASM_OBJ) && \
	grub-mkrescue /usr/lib/grub/i386-pc -o bin/x86_64/iso/boot.iso bin/x86_64/iso

emu:
	qemu-system-x86_64.exe -cdrom ./bin/x86_64/iso/

clean:
	rm -f $(shell find bin/x86_64/ -name "*.iso")
	rm -f $(shell find bin/x86_64/ -name "*.bin")
	rm -f $(shell find . -name "*.o")
