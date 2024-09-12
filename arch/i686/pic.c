#include <pic.h>
#include <hal.h>

void pic_init()
{
	// pic initialization , by https://wiki.osdev.org/PIC
	uint8_t a1 = inb(PIC1_DATA);
	uint8_t a2 = inb(PIC2_DATA);

	// start init in cascading mode
	outb(PIC1, ICW1_INIT + ICW1_ICW4);
	outb(PIC2, ICW1_INIT + ICW1_ICW4);

	// set the master PIC's offset to 0x20 (32) and the slave's to 0x28
	// this is from the wiki as well
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);

	// inform the master about the slave they have now
	// slave pic is located at IRQ2
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);

	// set the mode 8086 (0x01)
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);

	// finally, reset the masks
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);

	return;
}

void pic_eoi(uint8_t irqno)
{
	if(irqno >= 0x28)
		outb(PIC2_COMMAND, PIC_END);
	outb(PIC1_COMMAND, PIC_END);
	return;
}