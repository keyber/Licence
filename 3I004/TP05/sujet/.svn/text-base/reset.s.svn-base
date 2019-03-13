/*
 * This is a minimal boot code:
 * - It initializes the Status Register (SR).
 * - It defines the stack size and initializes the stack pointer ($29).
 * - It initializes the EPC register, and jumps in user code.
 */

    .section .reset, "ax", @progbits

    .func   reset
    .type   reset, %function

reset:

    .set noreorder

    /* initializes SR register */
    li      $26,    0x00000013          /* set UM, EXL and IE */
    mtc0    $26,    $12

    /* initializes stack pointer */
    la      $29,    seg_stack_base
    addiu   $29,    $29,    0x4000      /* stack size = 16K bytes */

    /* jumps in user mode */
    la      $26,    seg_data_base
    lw      $26,    0($26)              /* retrieves the user code's entry point */
    mtc0    $26,    $14
    eret

    .set reorder

    .endfunc
    .size reset, .-reset

