5.5.2019

Got TSS working yesterday, thanks to #osdev IRC channel on freenode :-) Today was time to create the interrupt trampoline routines in assembly, which came out pretty easily. I think I'll create the interrupt handling so that all interrupts fall to the same function in the kernel, which then checks if a handler has been assigned, and raises some sort of error if not. There is a file for PIC, but it is not yet implemented at all. 

4.5.2019

Added TSS, but for some reason loading it crashes the whole kernel. I have no idea why. https://wiki.osdev.org/TSS says that ss0, esp0 and iopb need to be defined when loading. I have not defined esp0, but it should not crash the whole kernel. Also, the GDT is loaded properly as described in https://wiki.osdev.org/GDT. I also checked that the TSS struct is indeed page-aligned and also packed properly using IDA. Well, I need to troubleshoot it properly some other day... It might even be the gcc messing up somehow :/

4.5.2019

I added a simple VGA driver which is able to clear the screen for now. I did not add any other functionality just yet, because the VGA cursor still remains. It seems like I need to add the outb and inb functions to disable/move it. More info about it can be found from the website https://wiki.osdev.org/Text_Mode_Cursor. The screen is now cleared once the system boots, so there is no blue text anymore for testing purposes :-)

4.5.2019

Adopted the string header file and the printk skeleton from the SaturnOS kernel, however, I don't really like the way I tried to implement the display "driver" last time. I also dislike the way the string is transferred from the printk function to the display in the old version, so next big thing is to implement a better display driver with actual input/output buffers so that the screen can be scrolled. For now I'm not sure if I need to implement a heap for buffer storage, but first I'm going to create a simple driver with input (putc and maybe remc wich should remove the latest input character) and a proper terminal with input buffer for basic line input.

21.3.2019

Wrote the entrypoint of the kernel in C and also a multiboot compatible bootloader in NASM assembly. This should work with GRUB. This time the bootloader code also implements memory paging, and therefore the kernel's memory space will be in the virtual address starting from 3GiB. The system is able to boot already, it has all the necessary stuff set up; GDT is initialized with very similar code to SaturnOS. It is loaded from inline assembly instead of inside the bootloader code though. It also writes one word to the VGA buffer (Blue A) to the first character so it can be confirmed that the kernel actually boots up. Next steps are implementing of IDT, then interrupts and timers so multiple tasks can be run at the same time. Also some sort of VGA "driver" would be nice, but the way I implemented it in the SaturnOS makes me just feel bad.. Got to think about the "right way" to implement it.