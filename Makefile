# 
# UranOS makefile
# 

#######################
#   * CONFIG PART *   #
#######################

# Name for the kernel image to be generated
KERNEL_IMAGE=kernel.img 

# Set default arch (lol, could we do ARM some day?!)
ARCH=i686

# Options for QEMU
QEMU_PARAMS=

#######################
# * END CONFIG PART * #
#######################

C_SOURCES:=$(shell find . -name '*.c' -not -path './toolchain/*')
ASM_SOURCES:=$(shell find . -name '*.asm' -not -path './toolchain/*')

KERNEL_OBJS = $(subst .c,.o,$(C_SOURCES))
KERNEL_OBJS += $(subst .asm,.o,$(ASM_SOURCES))

# Includes needed CC, QEMU_CMD etc. and toolchain makefile ...
include arch/$(ARCH)/Makefile

all: $(KERNEL_IMAGE) TOOLCHAIN

run: $(KERNEL_IMAGE)
	$(QEMU_CMD) -kernel $(KERNEL_IMAGE) $(QEMU_PARAMS)

debug_run: $(KERNEL_IMAGE)
	$(QEMU_CMD) -s -S -kernel $(KERNEL_IMAGE) $(QEMU_PARAMS) -no-reboot -no-shutdown

CFLAGS+=-Iinclude -Iarch/$(ARCH)/include -D__URANOS_ARCH_$(ARCH)__
CFLAGS+=-g

include toolchain/toolchain-$(ARCH).mk

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
	@rm $(KERNEL_OBJS) $(KERNEL_IMAGE)


