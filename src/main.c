#include "uart.h"
#include "mbox.h"
#include "printf.h"
#include "move.h"
#include "config.h"

extern char _binary_devicetree_dtb_start;
extern char _binary_devicetree_dtb_end;
extern char *_binary_devicetree_dtb_size;

extern char _binary_kernel_elf_start;
extern char _binary_kernel_elf_end;
extern char _binary_kernel_elf_size;

extern char __bss_start;
extern char __bss_end;

extern int _end;
extern int _ELF_START_;

void mem_rand(void) {
    // Check for available area
    int rand_begin = &_end;
    int m = 20;
    for (char *i = rand_begin; i < 0x0fffffff; i++) {
        *i = m++;
    }
}


int main(void) {
    // Clear BSS
    for (char *p = &__bss_start; p <= &__bss_end; p++) {
        *p = 0;
    }

    //mem_rand();
    uart_init();

    printf("ELF Multiboot Bootloader\n");
    printf("DTB Start=%x, End=%x, Size=%x\n", 
            &_binary_devicetree_dtb_start, 
            &_binary_devicetree_dtb_end,
            &_binary_devicetree_dtb_size);
    printf("Binary Start=%x, End=%x, Size=%x\n", 
            &_binary_kernel_elf_start,
            &_binary_kernel_elf_end,
            &_binary_kernel_elf_size);
    if (!multiboot_search(&_binary_kernel_elf_start)) {
        move(DTB_START, &_binary_devicetree_dtb_start, &_binary_devicetree_dtb_size);
        multiboot_boot(&_binary_kernel_elf_start);
    }

}