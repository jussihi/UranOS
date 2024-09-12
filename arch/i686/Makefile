# Define the compilers for C and ASM
AS=nasm
CC=gcc

# Define compiler and linker flags
ASFLAGS=-f elf32
CFLAGS=-ffreestanding -fno-stack-protector -fno-pie -m32 -O0
LDFLAGS=-melf_i386

# Define the used QEMU for this architecture
QEMU_CMD=qemu-system-i386