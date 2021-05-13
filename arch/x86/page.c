#include <page.h>
#include <x86.h>
#include <uranos/kernel.h>

int paging_init = 0;

pde_t kernel_page_dir[1024] __attribute__((aligned(4096)));

pte_t kernel_page_table[1024] __attribute__((aligned(4096)));
pte_t additional1[1024] __attribute__((aligned(4096)));
pte_t additional2[1024] __attribute__((aligned(4096)));
pte_t additional3[1024] __attribute__((aligned(4096)));
pte_t additional4[1024] __attribute__((aligned(4096)));
pte_t additional5[1024] __attribute__((aligned(4096)));

static inline uintptr_t kernel_virt_to_phys(void* _addr)
{
  return (uint32_t)_addr - VIRT_START;
}

static inline uint32_t pde_index(uint32_t _addr)
{
  return _addr >> 22;
}

static inline uintptr_t pte_index(uint32_t _addr)
{
  return (uintptr_t) ((_addr / 4096) % 1024);
}

static inline pte_t create_pte(uint32_t phys_addr, int user, int rw)
{
  phys_addr = phys_addr >> 12;

  //user = rw = 1;

  pte_t ret = 0;

  // This entry is now present
  ret |= (1 << PTE_PRESENT_SHIFT);

  // We can read and write the memory behind this entry
  ret |= (rw << PTE_RW_SHIFT);

  // Is this user memory?
  ret |= (user << PTE_USER_SHIFT);

  // Writethru
  ret |= (1 << PTE_WRITETHRU_SHIFT);

  ret |= (0 << PTE_CACHE_SHIFT);

  ret |= (0 << PTE_ACCESS_SHIFT);

  ret |= (0 << PTE_DIRTY_SHIFT) & (PTE_ZERO_MASK);

  ret |= (0 << PTE_GLOB_SHIFT) & (PTE_AVAIL_MASK);

  ret |= (phys_addr << PTE_ADDR_SHIFT);

  return ret;
}

static inline pde_t create_pde(uint32_t phys_addr, int user, int rw)
{
  phys_addr = phys_addr >> 12;

    //user = rw = 1;

  pde_t ret = 0;

  ret |= (1    << PDE_PRESENT_SHIFT);

  ret |= (rw   << PDE_RW_SHIFT);

  ret |= (user << PDE_USER_SHIFT);

  ret |= (1    << PDE_WRITETHRU_SHIFT);

  ret |= (0    << PDE_CACHE_SHIFT);

  ret |= (0    << PDE_ACCESS_SHIFT);

  ret |= (0    << PDE_ZERO_SHIFT);

  ret |= (0    << PDE_SIZE_SHIFT);

  ret |= (0    << PDE_IGNORE_SHIFT) & (PDE_AVAIL_MASK);

  ret |= (phys_addr << PDE_ADDR_SHIFT);

  return ret;
}

void reinit_kernel_paging()
{
  // This should NEVER be called twice
  if(paging_init)
  {
    // TODO: PANIC!
    return;
  }

  DISABLE_INTERRUPTS();

  kprintf("Re-mapping kernel pages for first 4MiB\n");

  for (int i = 0; i < 4 * 1024 * 1023; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    kernel_page_table[pte_index(i)] = page;
  }
  pte_t vga_page = create_pte(0x000B8000, 0, 1);
  kernel_page_table[pte_index(4 * 1024 * 1023)] = vga_page;
  kernel_page_dir[pde_index(VIRT_START)] = create_pde(kernel_virt_to_phys(kernel_page_table), 0, 1);

  /*
  for (int i = 4 * 1024 * 1024; i < 8 * 1024 * 1024; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    additional1[pte_index(i)] = page;
  }
  kernel_page_dir[pde_index(VIRT_START + 4 * 1024 * 1024)] = create_pde(kernel_virt_to_phys(additional1), 0, 1);

  for (int i = 8 * 1024 * 1024; i < 12 * 1024 * 1024; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    additional2[pte_index(i)] = page;
  }
  kernel_page_dir[pde_index(VIRT_START + 8 * 1024 * 1024)] = create_pde(kernel_virt_to_phys(additional2), 0, 1);

  for (int i = 12 * 1024 * 1024; i < 16 * 1024 * 1024; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    additional3[pte_index(i)] = page;
  }
  kernel_page_dir[pde_index(VIRT_START + 12 * 1024 * 1024)] = create_pde(kernel_virt_to_phys(additional3), 0, 1);

  for (int i = 16 * 1024 * 1024; i < 20 * 1024 * 1024; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    additional4[pte_index(i)] = page;
  }
  kernel_page_dir[pde_index(VIRT_START + 16 * 1024 * 1024)] = create_pde(kernel_virt_to_phys(additional4), 0, 1);

  for (int i = 20 * 1024 * 1024; i < 24 * 1024 * 1024; i += 4096)
  {
    pte_t page = create_pte(i, 0, 1);
    additional5[pte_index(i)] = page;
  }
  kernel_page_dir[pde_index(VIRT_START + 20 * 1024 * 1024)] = create_pde(kernel_virt_to_phys(additional5), 0, 1);
  */
  
  kprintf("Flushing TLB ....\n");
  // Flush TLB
  __asm__ __volatile__("mov %0, %%cr3"::"r"(kernel_virt_to_phys(kernel_page_dir)));
  paging_init = 1;

  ENABLE_INTERRUPTS();

  kprintf("Kernel memory re-mapped!\n");
}