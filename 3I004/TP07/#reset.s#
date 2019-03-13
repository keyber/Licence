/*
 * This is an improved boot code supporting TIMER and TTY devices:
 * - It initializes the Status Register (SR).
 * - It defines the stack size and initializes the stack pointer ($29).
 * - It initializes the interrupt vector with two ISR addresses (timer and tty)
 *   and configurates the ICU: IRQ_IN[1] & IRQ_IN[3] activated.
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
    addiu   $29,    $29,    0x4000      /* stack size = 16 Kbytes */

    /* initializes interrupt vector */
    la      /* A COMPLETER */  /* $26 <= interrupt_vector address */
    la      /* A COMPLETER */  /* $27 <= isr_timer address */
    sw      /* A COMPLETER */  /* interrupt_vector[1] <= _isr_timer */
    la      /* A COMPLETER */  /* $27 <= isr_tty_get_task0 address */
    sw      /* A COMPLETER */  /* interrupt_vector[3] <= _isr_tty_get_task0 */

    /* initializes ICU */
    la      $26,    seg_icu_base
    li      $27,    0xA                 /* IRQ_IN[1] & IRQ_IN[3] enabled */
    sw      $27,    2*4($26)            /* ICU_MASK_SET = 0xA */

    /* jumps in user mode */
    la      $26,    seg_data_base
    lw      $26,    0($26)              /* retrieves the user code's entry point */
    mtc0    $26,    $14
    eret

    .set reorder

    .endfunc
    .size reset, .-reset

