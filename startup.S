/* some assembler parameters */
.syntax unified
.thumb
.cpu cortex-m4

.section .text, "ax", %progbits

/* _start() - entry point */
_start:
  /* copy .data section into RAM */
_start_copy_data:
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  b _start_copy_data_loop_cond
_start_copy_data_loop:
  ldr r3, [r2], #4
  str r3, [r0], #4
_start_copy_data_loop_cond:
  cmp r0, r1
  bcc _start_copy_data_loop
  /* zero out .bss section */
_start_zero_bss:
  ldr r0, =_sbss
  ldr r1, =_ebss
  mov r2, #0
  b _start_zero_bss_loop_cond
_start_zero_bss_loop:
  str r2, [r0], #4
_start_zero_bss_loop_cond:
  cmp r0, r1
  bcc _start_zero_bss_loop
  /* call main() */
_start_call_main:
  bl main
_start_halt:
  b _start_halt
.type _start, %function
.size _start, .-_start

/* _isr() - calls isr(exception_number) */
_isr:
  mrs r0, ipsr
  b isr
.type _isr, %function
.size _isr, .-_isr

.section .isr_vector, "a", %progbits

/*
 * exception vector table - first entry is value of SP_main upon
 * processor reset, remaining entries are exception handlers
 * (second entry is the reset handler aka entry point).
 */
 _isr_vector:
.word _estack
.word _start
.rept 96 /* 82 IRQs + 16 system - 2 for SP/reset */
  .word _isr
.endr
.type _isr_vector, %object
.size _isr_vector, .-_isr_vector
