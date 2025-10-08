/**
 * SpiritOS Boot Assembly - Multiboot2 Entry Point
 * 
 * This file provides the bare-metal boot entry point for SpiritOS
 * Compatible with Multiboot2 specification for GRUB bootloader
 */

.set MULTIBOOT2_MAGIC,              0xe85250d6
.set MULTIBOOT2_ARCHITECTURE,       0          /* i386 */
.set MULTIBOOT2_HEADER_LENGTH,      (multiboot_header_end - multiboot_header)
.set MULTIBOOT2_CHECKSUM,           -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCHITECTURE + MULTIBOOT2_HEADER_LENGTH)

.section .multiboot
.align 8
multiboot_header:
    .long MULTIBOOT2_MAGIC
    .long MULTIBOOT2_ARCHITECTURE
    .long MULTIBOOT2_HEADER_LENGTH
    .long MULTIBOOT2_CHECKSUM
    
    /* End tag */
    .word 0
    .word 0
    .long 8
multiboot_header_end:

.section .bss
.align 16
stack_bottom:
    .skip 16384  /* 16 KiB stack */
stack_top:

.section .text
.global _start
.type _start, @function

/* Entry point is in 32-bit mode (multiboot starts in 32-bit) */
.code32

_start:
    /* We're in 32-bit protected mode here */
    
    /* Setup stack */
    mov $stack_top, %esp
    mov %esp, %ebp
    
    /* Save multiboot information */
    /* EAX contains multiboot2 magic (0x36d76289) */
    /* EBX contains physical address of multiboot information structure */
    push %ebx  /* Push multiboot info pointer */
    push %eax  /* Push multiboot magic */
    
    /* Clear direction flag */
    cld
    
    /* For simplicity, we'll stay in 32-bit mode */
    /* A full x86_64 kernel would transition to long mode here */
    
    /* Call kernel main */
    call kernel_main
    
    /* If kernel_main returns, hang */
halt:
    cli
    hlt
    jmp halt

.size _start, . - _start
