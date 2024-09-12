BINUTILS_VERSION=2.43
GCC_VERSION=14.2.0

TOOLCHAIN_BUILD_DIR=$(CURDIR)/toolchain/i686-build
TOOLCHAIN_PREFIX=$(CURDIR)/toolchain/i686
TOOLCHAIN_TARGET=i686-elf
TOOLCHAIN_PATH="$PREFIX/bin:$PATH"

BINUTILS_LD=$(TOOLCHAIN_PREFIX)/bin/i686-elf-ld
BINUTILS_TARBALL=$(TOOLCHAIN_BUILD_DIR)/binutils-$(BINUTILS_VERSION).tar.gz

GCC_GCC=$(TOOLCHAIN_PREFIX)/bin/i686-elf-gcc
GCC_TARBALL=$(TOOLCHAIN_BUILD_DIR)/gcc-$(GCC_VERSION).tar.gz

PATH := $(TOOLCHAIN_PREFIX)/bin:$(PATH)

.PHONY: TOOLCHAIN
TOOLCHAIN: $(BINUTILS_LD) $(GCC_GCC)

$(TOOLCHAIN_PREFIX):
	mkdir -p $(TOOLCHAIN_PREFIX)

$(TOOLCHAIN_BUILD_DIR): $(TOOLCHAIN_PREFIX)
	mkdir -p $(TOOLCHAIN_BUILD_DIR)

$(BINUTILS_TARBALL): $(TOOLCHAIN_BUILD_DIR)
	echo $(BINUTILS_TARBALL)
	wget -nc https://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VERSION).tar.gz -P toolchain/$(ARCH)-build

$(BINUTILS_LD): $(BINUTILS_TARBALL)
	echo  $(BINUTILS_LD)
	cd toolchain/$(ARCH)-build && tar -xvzf binutils-$(BINUTILS_VERSION).tar.gz
	mkdir -p toolchain/$(ARCH)-build/binutils-build
	cd toolchain/$(ARCH)-build/binutils-build && \
	../binutils-$(BINUTILS_VERSION)/configure --target=$(TOOLCHAIN_TARGET) --prefix="$(TOOLCHAIN_PREFIX)"" --with-sysroot --disable-nls --disable-werror && \
	make && \
	make install

$(GCC_TARBALL): $(TOOLCHAIN_BUILD_DIR)
	wget -nc https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VERSION)/gcc-$(GCC_VERSION).tar.gz -P toolchain/$(ARCH)-build

$(GCC_GCC): $(GCC_TARBALL)
	cd toolchain/$(ARCH)-build && tar -xvzf gcc-$(GCC_VERSION).tar.gz
	mkdir -p toolchain/$(ARCH)-build/gcc-build
	cd toolchain/$(ARCH)-build/gcc-build && \
	../gcc-$(GCC_VERSION)/configure --target=$(TOOLCHAIN_TARGET) --prefix="$(TOOLCHAIN_PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers && \
	make -j12 all-gcc && \
	make -j12 all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc