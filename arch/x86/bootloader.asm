;
; Define multiboot header just like with SaturnOS
;
ALIGNFG equ 1<<0					; Align modules to page boundaries
MEMINFOFG equ 1<<1					; Provide our own mem.map
FLAGSFG equ ALIGNFG|MEMINFOFG		; Create the flags field of header
MAGICFG equ 0x1BADB002				; Magic number for multiboot
CHECKSUMFG equ -(MAGICFG+FLAGSFG)	; Prove that we are multiboot compatible with checksum

; Create the header into the binary
SECTION .multiboot
ALIGN 4
	dd MAGICFG
	dd FLAGSFG
	dd CHECKSUMFG

; Allocate early stack
SECTION .early_stack nobits alloc write
early_stack_end:
	resb 16384
early_stack_start:

;
; BSS SECTION
;
SECTION .bss NOBITS ALLOC WRITE ALIGN=4096

GLOBAL boot_pagedir
boot_pagedir:
	resb 4096
GLOBAL boot_page_table
boot_page_table:
	resb 4096

;
; TEXT SECTION, KERNEL ENTRY POINT
;
SECTION .text
extern _begin_link
extern _end_link
extern kmain
GLOBAL _start:function
_start:
	mov edi, (boot_page_table-0xC0000000)

	mov esi, 0

	mov ecx, 1023

_1:
	cmp esi, (_begin_link-0xC0000000)
	jl _2
	cmp esi, (_end_link-0xC0000000)
	jge _3

	mov edx, esi
	or edx, 0x003
	mov [edi], edx

_2:
	add esi, 4096
	add edi, 4

	loop _1	; loop until ecx = 0

_3:
	; map VGA memory
	mov  dword [boot_page_table - 0xC0000000 + 1023 * 4], (0x000B8000|0x003)

	; Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	mov dword [boot_pagedir - 0xC0000000 + 0], (boot_page_table - 0xC0000000 + 0x003)
	mov dword [boot_pagedir - 0xC0000000 + 768 * 4], (boot_page_table - 0xC0000000 + 0x003)

	mov ecx, (boot_pagedir - 0xC0000000)
	mov cr3, ecx

	; enable paging
	mov ecx, cr3
	or ecx, 0x80010000
	mov cr0, ecx

	lea ecx, [_4]
	jmp ecx

_4:
	mov dword [boot_pagedir + 0], 0

	; Reload crc3 to force a TLB flush so the changes to take effect.
	mov ecx, cr3
	mov cr3, ecx

	; set the stack pointer
	mov esp, early_stack_start

	; start the high-level (C) kernel
	call kmain

	cli
	hlt