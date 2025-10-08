/**
 * SpiritOS Kernel Linker Script
 * 
 * Defines the memory layout of the SpiritOS kernel binary
 */

ENTRY(_start)

SECTIONS
{
    /* Kernel starts at 1MB physical address (standard for x86) */
    . = 1M;
    
    _kernel_start = .;
    
    /* Multiboot header must be in first 8KB */
    .multiboot : ALIGN(4K)
    {
        *(.multiboot)
    }
    
    /* Read-only code */
    .text : ALIGN(4K)
    {
        *(.text)
        *(.text.*)
    }
    
    /* Read-only data */
    .rodata : ALIGN(4K)
    {
        *(.rodata)
        *(.rodata.*)
    }
    
    /* Initialized data */
    .data : ALIGN(4K)
    {
        *(.data)
        *(.data.*)
    }
    
    /* Uninitialized data (BSS) */
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }
    
    _kernel_end = .;
    
    /* Discard unnecessary sections */
    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.*)
    }
}
