/* some assembler parameters */
.thumb
.arch armv7-m
.cpu cortex-m4
.fpu softvfp

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

.section .isr_vector, "a", %progbits

/* interrupt vector table */
.global isr_vector
isr_vector:
  /* exceptions */
  .word _estack
  .word _start
  .word _halt /* non maskable interrupt */
  .word _halt /* hard fault */
  .word _halt /* memory management fault */
  .word _halt /* bus fault */
  .word _halt /* usage fault */
  .word 0
  .word 0
  .word 0
  .word 0
  .word _halt /* supervisor call (syscall) */
  .word 0
  .word 0
  .word _halt /* PendSV */
  .word _halt /* Systick */

  /* IRQs */
  .word _halt /* Window WatchDog              */
  .word _halt /* PVD through EXTI Line detection */
  .word _halt /* Tamper and TimeStamps through the EXTI line */
  .word _halt /* RTC Wakeup through the EXTI line */
  .word _halt /* FLASH                        */
  .word _halt /* RCC                          */
  .word _halt /* EXTI Line0                   */
  .word _halt /* EXTI Line1                   */
  .word _halt /* EXTI Line2                   */
  .word _halt /* EXTI Line3                   */
  .word _halt /* EXTI Line4                   */
  .word _halt /* DMA1 Stream 0                */
  .word _halt /* DMA1 Stream 1                */
  .word _halt /* DMA1 Stream 2                */
  .word _halt /* DMA1 Stream 3                */
  .word _halt /* DMA1 Stream 4                */
  .word _halt /* DMA1 Stream 5                */
  .word _halt /* DMA1 Stream 6                */
  .word _halt /* ADC1, ADC2 and ADC3s         */
  .word _halt /* CAN1 TX                      */
  .word _halt /* CAN1 RX0                     */
  .word _halt /* CAN1 RX1                     */
  .word _halt /* CAN1 SCE                     */
  .word _halt /* External Line[9:5]s          */
  .word _halt /* TIM1 Break and TIM9          */
  .word _halt /* TIM1 Update and TIM10        */
  .word _halt /* TIM1 Trigger and Commutation and TIM11 */
  .word _halt /* TIM1 Capture Compare         */
  .word _halt /* TIM2                         */
  .word _halt /* TIM3                         */
  .word _halt /* TIM4                         */
  .word _halt /* I2C1 Event                   */
  .word _halt /* I2C1 Error                   */
  .word _halt /* I2C2 Event                   */
  .word _halt /* I2C2 Error                   */
  .word _halt /* SPI1                         */
  .word _halt /* SPI2                         */
  .word _halt /* USART1                       */
  .word _halt /* USART2                       */
  .word _halt /* USART3                       */
  .word _halt /* External Line[15:10]s        */
  .word _halt /* RTC Alarm (A and B) through EXTI Line */
  .word _halt /* USB OTG FS Wakeup through EXTI line */
  .word _halt /* TIM8 Break and TIM12         */
  .word _halt /* TIM8 Update and TIM13        */
  .word _halt /* TIM8 Trigger and Commutation and TIM14 */
  .word _halt /* TIM8 Capture Compare         */
  .word _halt /* DMA1 Stream7                 */
  .word _halt /* FSMC                         */
  .word _halt /* SDIO                         */
  .word _halt /* TIM5                         */
  .word _halt /* SPI3                         */
  .word _halt /* UART4                        */
  .word _halt /* UART5                        */
  .word _halt /* TIM6 and DAC1&2 underrun errors */
  .word _halt /* TIM7                         */
  .word _halt /* DMA2 Stream 0                */
  .word _halt /* DMA2 Stream 1                */
  .word _halt /* DMA2 Stream 2                */
  .word _halt /* DMA2 Stream 3                */
  .word _halt /* DMA2 Stream 4                */
  .word _halt /* Ethernet                     */
  .word _halt /* Ethernet Wakeup through EXTI line */
  .word _halt /* CAN2 TX                      */
  .word _halt /* CAN2 RX0                     */
  .word _halt /* CAN2 RX1                     */
  .word _halt /* CAN2 SCE                     */
  .word _halt /* USB OTG FS                   */
  .word _halt /* DMA2 Stream 5                */
  .word _halt /* DMA2 Stream 6                */
  .word _halt /* DMA2 Stream 7                */
  .word _halt /* USART6                       */
  .word _halt /* I2C3 event                   */
  .word _halt /* I2C3 error                   */
  .word _halt /* USB OTG HS End Point 1 Out   */
  .word _halt /* USB OTG HS End Point 1 In    */
  .word _halt /* USB OTG HS Wakeup through EXTI */
  .word _halt /* USB OTG HS                   */
  .word _halt /* DCMI                         */
  .word _halt /* CRYP crypto                  */
  .word _halt /* Hash and Rng                 */
  .word _halt /* FPU                          */
