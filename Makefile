# 
# UranOS makefile
# 

#######################
#   * CONFIG PART *   #
#######################

# Name for the kernel image to be generated
KERNEL_IMAGE=kernel.img 

# Set default arch (lol, could we do ARM some day?!)
ARCH=x86

# Options for QEMU
QEMU_PARAMS=-serial stdio -no-reboot

#######################
# * END CONFIG PART * #
#######################

C_SOURCES:=$(shell find . -name '*.c')
ASM_SOURCES:=$(shell find . -name '*.asm')

KERNEL_OBJS = $(subst .c,.o,$(C_SOURCES))
KERNEL_OBJS += $(subst .asm,.o,$(ASM_SOURCES))

# Includes needed CC, QEMU_CMD etc ...
include arch/$(ARCH)/Makefile

all: $(KERNEL_IMAGE)

run: $(KERNEL_IMAGE)
	$(QEMU_CMD) -kernel $(KERNEL_IMAGE) $(QEMU_PARAMS)

debug_run: $(KERNEL_IMAGE)
	$(QEMU_CMD) -s -S -kernel $(KERNEL_IMAGE) $(QEMU_PARAMS)

CFLAGS+=-Iinclude -Iarch/$(ARCH)/include -D__URANOS_ARCH_$(ARCH)__
CFLAGS+=-g

$(KERNEL_IMAGE): $(KERNEL_OBJS)
	@echo "  LD     $@"
	@ld $(LDFLAGS) -T arch/$(ARCH)/linker.ld -o $(KERNEL_IMAGE) $(KERNEL_OBJS)

%.o: %.c
	@echo "  CC     $<  -->   $@"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	@echo "  AS     $<  -->   $@"
	@$(AS) $(ASFLAGS) $< -o $@

clean:
	rm $(KERNEL_OBJS) $(KERNEL_IMAGE)