#include <tss.h>
#include <uranos/string.h>

static TSS_t tss __attribute__((aligned(4096)));

void tss_init(void)
{
	memset(&tss, 0, sizeof(TSS_t));
	tss.ss0 = 0x10;
    tss.iopb = sizeof(TSS_t);
    return;
}

TSS_t* get_tss(void)
{
	return &tss;
}
