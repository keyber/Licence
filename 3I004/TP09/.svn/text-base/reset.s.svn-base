/*
 * This boot code creates four tasks running on the same processor, and
 * executing four different programs: main0, main1, main2, main3.
 * Each task has its own terminal, and its own stack.
 * The boot code:
 * - Initializes the interrupt vector with seven ISR addresses (block-device,
 *   timer, dma, tty0, tty1, tty2 and tty3).
 * - Initializes the _current_task_array and _task_number_array variables.
 * - Initializes contexts for tasks T1, T2, T3: EPC, SR, SP, RA.
 * - Initializes registers for task T0: EPC, SR, SP.
 * - Initializes the Timer & ICU components.
 * - Jumps in user code.
 */

    .section .reset, "ax", @progbits

    .func   reset
    .type   reset, %function

reset:
    .set noreorder

    /* initializes interrupt vector */
    la      $27,    _interrupt_vector   /* $27 <= interrupt vector address */
    la      $26,    _isr_switch
    sw      $26,    1*4($27)            /* interrupt_vector[1] <= _isr_switch */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[0] <= _isr_ioc */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[2] <= _isr_dma */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[3] <= _isr_tty_get_task0 */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[4] <= _isr_tty_get_task1 */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[5] <= _isr_tty_get_task2 */
    la      /* A COMPLETER */
    sw      /* A COMPLETER */  /* interrupt_vector[6] <= _isr_tty_get_task3 */

    /* initializes task index and task number */
    la      $27,    _current_task_array
    sb      $0,     0($27)              /* task_index <= 0 (not necessary, already done by default) */
    la      $27,    _task_number_array
    li      $26,    4
    sb      $26,    0($27)              /* task_number <= 4 */

    /* initializes stack pointers for tasks 1,2,3 (each stack is 64 KB) */
    la      $27,    _task_context_array /* $27 <= &ctx[] */
    la      $26,    seg_stack_base
    li      $10,    0x00020000          /* 128 K */
    add     $10,    $26,    $10
    sw      $10,    4*(64+29)($27)      /* SP for task 1 */
    li      $10,    0x00030000          /* 192 K */
    add     $10,    $26,    $10
    sw      $10,    4*(128+29)($27)     /* SP for task 2 */
    li      /* A COMPLETER */     /* 256 K */
    add     /* A COMPLETER */
    sw      /* A COMPLETER */     /* SP for task 3 */

    /* initializes EPC for tasks 1,2,3 (main1, main2, main3) */
    la      $26,    seg_data_base
    lw      $10,    1*4($26)            /* retrieves main1 address */
    sw      $10,    4*(64+32)($27)      /* EPC for task 1 */
    lw      $10,    2*4($26)            /* retrieves main2 address */
    sw      $10,    4*(128+32)($27)     /* EPC for task 2 */
    lw      /* A COMPLETER */     /* retrieves main3 address */
    sw      /* A COMPLETER */     /* EPC for task 3 */

    /* initializes RA for tasks 1,2,3 (to execute the eret instruction) */
    la      $26,    to_user
    sw      $26,    4*(64+31)($27)      /* $31 for task 1 */
    sw      $26,    4*(128+31)($27)     /* $31 for task 2 */
    sw      /* A COMPLETER */     /* $31 for task 3 */

    /* initializes SR sor tasks 1,2,3 (set IM, UM, EXL, IE) */
    li      $26,    0x0000FF13
    sw      $26,    4*64($27)           /* SR for task 1 */
    sw      $26,    4*128($27)          /* SR for task 2 */
    sw      /* A COMPLETER */     /* SR for task 3 */

    /* ICU Configuration: 7 IRQs enabled (IOC, TIMER, DMA, TTYs) */
    la      $27,    seg_icu_base
    li      /* A COMPLETER */
    sw      $26,    2*4($27)            /* ICU_MASK_SET = 0111 1111 */

    /* TIMER Configuration: period = 10000 cycles */
    la      $27,    seg_timer_base
    li      $26,    10000
    sw      /* A COMPLETER */            /* period <= 10000 */
    li      $26,    0x3
    sw      $26,    1*4($27)            /* TIMER start */

    /* initializes registers for T0 (stack size = 64K) */
    la      $27,    seg_stack_base
    li      $26,    0x0010000
    add     $29,    $27,    $26         /* SP for task 0 */
    la      $26,    seg_data_base
    lw      $26,    0($26)              /* retrieves main0 address */
    mtc0    $26,    $14                 /* EPC for task 0 */
    li      $26,    0x0000FF13          /* set IM, UM, EXL and IE */
    mtc0    $26,    $12                 /* SR for task 0 */

    /* jumps to address contained in EPC (in user mode) */
to_user:
    eret

    .set reorder

    .endfunc
    .size reset, .-reset

