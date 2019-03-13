/*
 * This is a boot code for a multi-processor architecture supporting up to 8
 * processors with 1 task on each. Each processor executes this boot code and:
 * - initializes its Status Register (SR).
 * - initializes the stack pointer for the task (stack size = 64K)
 * - initializes the interrupt vector with one ISR addresses (_tty_get_task0):
 *  - interrupt index is computed as follow: for processor #p, the tty0
 *    corresponds to the index i=(1 + 3 * p + 2)
 * - configurates the ICU to enable tty0.
 * - initializes its EPC register, and jumps to the main in user mode.
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
    mfc0    $10,    $15,    1
    andi    $10,    $10,    0x7         /* $10 <= proc_id */
    li      $27,    0x10000/* A COMPLETER */      /* $27 <= 64 K */
    mult    $10,    $27/* A COMPLETER */
    mflo    $26/* A COMPLETER */      /* $26 <= proc_id*64K */
    addu    $26,    $27/* A COMPLETER */      /* $26 <= (proc_id + 1)*64K */
    la      $29,    seg_stack_base/* A COMPLETER */      /* $29 <= seg_stack_base */
    addu    $29,    $29, $26/* A COMPLETER */      /* $29 <= seg_stack_base + (proc_id + 1)*64K */

    /* initializes interrupt vector */
    la      $26,    _interrupt_vector   /* $26 <= interrupt_vector address */
    li      $27,    3*4
    mult    $27,    $10                 /* $27 <= proc_id*3 (*4 for words) */
    mflo    $27
    addu    $26,    $26,    $27         /* $26 <= @interrupt_vector[proc_id*3] */
    la      $27,    _isr_tty_get_task0  /* $27 <= isr_tty_get_task0 address */
    sw      $27,    (1+2)*4($26)        /* interrupt_vector[1+proc_id*3+2] <= isr_tty_get_task0 */

    /* initializes ICU */
    li      $26,    3
    mult    $26,    $10                 /* $26 <= proc_id*3 */
    mflo    $26
    addiu   $26,    $26,    (1+2)       /* $26 <= (1 + proc_id * 3 + 2) */
    li      $11,    1
    sllv    $11,    $11,    $26         /* $11 <= 1 << (1 + proc_id * 3 + 2) */
    li      $27,    8*4                 /* $27 <= ICU_SPAN (*4 for words) */
    mult    $27,    $10
    mflo    $27                         /* $27 <= proc_id*ICU_SPAN */
    la      $26,    seg_icu_base
    addu    $26,    $26,    $27         /* $26 <= seg_icu_base + proc_id*ICU_SPAN */
    sw      $11,    2*4($26)            /* ICU_MASK_SET <= enable tty0 */

    /* jumps in user mode */
    la      $26,    seg_data_base
    lw      $26,    0($26)              /* retrieves the user code's entry point */
    mtc0    $26,    $14
    eret

    .set reorder

    .endfunc
    .size reset, .-reset

