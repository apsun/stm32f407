/* some assembler parameters */
.syntax unified
.thumb
.cpu cortex-m4

/* defined in linker script */
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

.section .text, "ax", %progbits

/* _start() - entry point */
.global _start
.type _start, %function
_start:
  /* copy .data section into RAM */
_start_copy_data:
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
_start_copy_data_loop:
  cmp r0, r1
  bcs _start_zero_bss
  ldr r3, [r2]
  str r3, [r0]
  add r2, r2, #4
  add r0, r0, #4
  b _start_copy_data_loop
  /* zero out .bss section */
_start_zero_bss:
  ldr r0, =_sbss
  ldr r1, =_ebss
  mov r2, #0
_start_zero_bss_loop:
  cmp r0, r1
  bcs _start_call_main
  str r2, [r0]
  add r0, r0, #4
  b _start_zero_bss_loop
  /* call main() */
_start_call_main:
  bl main
  b _halt

/* _halt() - spin forever */
.global _halt
.type _halt, %function
_halt:
  b _halt

/* _exception_handler() - calls exception_handler(exception_number) */
.global _exception_handler
.type _exception_handler, %function
_exception_handler:
  mrs r0, ipsr
  b exception_handler

.section .isr_vector, "a", %progbits

/*
 * exception vector table - first entry is value of SP_main upon
 * processor reset, remaining entries are exception handlers
 * (second entry is the reset handler aka entry point).
 */
.word _estack
.word _start
.rept 96 /* 82 IRQs + 16 system - 2 for SP/reset */
  .word _exception_handler
.endr
