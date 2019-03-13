/*
 * This is an improved boot code supporting IOC and DMA devices:
 * - It initializes the Status Register (SR).
 * - It defines the stack size and initializes the stack pointer ($29).
 * - It initializes the interrupt vector with four ISR addresses (block-device,
 *   timer, dma and tty) and configurates the ICU.
 * - It initializes the EPC register, and jumps in user code.
 */

    .section .reset, "ax", @progbits

    .func   reset
    .type   reset, %function

reset:

    .set noreorder

    /* initializes SR register */
    li      $26,    0x0000FF13          /* set IM, UM, EXL and IE */
    mtc0    $26,    $12

    /* initializes stack pointer */
    la      $29,    seg_stack_base
    li      $26,    0x40000             /* imm is too big to be used directly */
    addu    $29,    $29,    $26         /* stack size = 256 Kbytes */

    /* initializes interrupt vector */
    la      $26,    _interrupt_vector   /* $26 <= interrupt_vector address */
    la      $27,    _isr_timer          /* $27 <= isr_timer address */
    sw      $27,    1*4($26)            /* interrupt_vector[1] <= _isr_timer */
    la      $27,    _isr_tty_get_task0  /* $27 <= isr_tty_get_task0 address */
    sw      $27,    3*4($26)            /* interrupt_vector[3] <= _isr_tty_get_task0 */
    /* A COMPLETER */            /* $27 <= isr_ioc address */
    /* A COMPLETER */            /* interrupt_vector[0] <= _isr_ioc */
    /* A COMPLETER */            /* $27 <= isr_dma address */
    /* A COMPLETER */            /* interrupt_vector[2] <= _isr_dma */

    /* initializes ICU */
    la      $26,    seg_icu_base
    li      $27,    /* A COMPLETER */   /* IRQ[0] & IRQ[1] & IRQ[2] & IRQ[3] enabled */
    sw      $27,    2*4($26)            /* ICU_MASK_SET */

    /* jumps in user mode */
    la      $26,    seg_data_base
    lw      $26,    0($26)              /* retrieves the user code's entry point */
    mtc0    $26,    $14
    eret

    .set reorder

    .endfunc
    .size reset, .-reset

