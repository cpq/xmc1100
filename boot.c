// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved

// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
  // Init stack
  asm volatile("ldr r1, =_estack; mov sp, r1;");

  // Initialise memory
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *src = &_sbss; src < &_ebss; src++) *src = 0;
  for (long *src = &_sdata, *dst = &_sidata; src < &_edata;) *src++ = *dst++;

  // Call main()
  extern void main(void);
  main();
  for (;;) (void) 0;
}

void __attribute__((weak)) DefaultIRQHandler(void) {
  for (;;) (void) 0;
}
#define WEAK_ALIAS __attribute__((weak, alias("DefaultIRQHandler")))

WEAK_ALIAS void HardFault_Handler(void);
WEAK_ALIAS void SVC_Handler(void);
WEAK_ALIAS void PendSV_Handler(void);
WEAK_ALIAS void SysTick_Handler(void);

WEAK_ALIAS void I0_IRQHandler(void);
WEAK_ALIAS void I1_IRQHandler(void);
WEAK_ALIAS void I2_IRQHandler(void);
WEAK_ALIAS void I3_IRQHandler(void);
WEAK_ALIAS void I4_IRQHandler(void);
WEAK_ALIAS void I5_IRQHandler(void);
WEAK_ALIAS void I6_IRQHandler(void);
WEAK_ALIAS void I7_IRQHandler(void);
WEAK_ALIAS void I8_IRQHandler(void);
WEAK_ALIAS void I9_IRQHandler(void);
WEAK_ALIAS void I10_IRQHandler(void);
WEAK_ALIAS void I11_IRQHandler(void);
WEAK_ALIAS void I12_IRQHandler(void);
WEAK_ALIAS void I13_IRQHandler(void);
WEAK_ALIAS void I14_IRQHandler(void);
WEAK_ALIAS void I15_IRQHandler(void);
WEAK_ALIAS void I16_IRQHandler(void);
WEAK_ALIAS void I17_IRQHandler(void);
WEAK_ALIAS void I18_IRQHandler(void);
WEAK_ALIAS void I19_IRQHandler(void);
WEAK_ALIAS void I20_IRQHandler(void);
WEAK_ALIAS void I21_IRQHandler(void);
WEAK_ALIAS void I22_IRQHandler(void);
WEAK_ALIAS void I23_IRQHandler(void);
WEAK_ALIAS void I24_IRQHandler(void);
WEAK_ALIAS void I25_IRQHandler(void);
WEAK_ALIAS void I26_IRQHandler(void);
WEAK_ALIAS void I27_IRQHandler(void);
WEAK_ALIAS void I28_IRQHandler(void);
WEAK_ALIAS void I29_IRQHandler(void);
WEAK_ALIAS void I30_IRQHandler(void);
WEAK_ALIAS void I31_IRQHandler(void);

const unsigned long t1[] __attribute__((section(".vectors"))) = {
    0x20004000,  // _estack
    (unsigned long) _reset,
    0,
    0,
    (1UL << 8),  // CLK_VAL1, 19.1.3.1, then SCU_CLKCR.DIV = 1 (32MHz)
    (1UL << 9)   // CLK_VAL2, disable WDT
};

// remapped vectors 2.5.4.1
__attribute__((section(".first_data"))) void remapped_irq_table(void) {
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile("ldr r0, =HardFault_Handler; mov pc, r0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile("ldr r0, =SVC_Handler; mov pc, r0");
  asm volatile(".long 0");
  asm volatile(".long 0");
  asm volatile("ldr r0, =PendSV_Handler; mov pc, r0");
  asm volatile("ldr r0, =SysTick_Handler; mov pc, r0");

  asm volatile("ldr r0, =I0_IRQHandler; mov pc, r0");   // IRQ 0
  asm volatile("ldr r0, =I1_IRQHandler; mov pc, r0");   // IRQ 1
  asm volatile("ldr r0, =I2_IRQHandler; mov pc, r0");   // IRQ 2
  asm volatile("ldr r0, =I3_IRQHandler; mov pc, r0");   // IRQ 3
  asm volatile("ldr r0, =I4_IRQHandler; mov pc, r0");   // IRQ 4
  asm volatile("ldr r0, =I5_IRQHandler; mov pc, r0");   // IRQ 5
  asm volatile("ldr r0, =I6_IRQHandler; mov pc, r0");   // IRQ 6
  asm volatile("ldr r0, =I7_IRQHandler; mov pc, r0");   // IRQ 7
  asm volatile("ldr r0, =I8_IRQHandler; mov pc, r0");   // IRQ 8
  asm volatile("ldr r0, =I9_IRQHandler; mov pc, r0");   // IRQ 9
  asm volatile("ldr r0, =I10_IRQHandler; mov pc, r0");  // IRQ 10
  asm volatile("ldr r0, =I11_IRQHandler; mov pc, r0");  // IRQ 11
  asm volatile("ldr r0, =I12_IRQHandler; mov pc, r0");  // IRQ 12
  asm volatile("ldr r0, =I13_IRQHandler; mov pc, r0");  // IRQ 13
  asm volatile("ldr r0, =I14_IRQHandler; mov pc, r0");  // IRQ 14
  asm volatile("ldr r0, =I15_IRQHandler; mov pc, r0");  // IRQ 15
  asm volatile("ldr r0, =I16_IRQHandler; mov pc, r0");  // IRQ 16
  asm volatile("ldr r0, =I17_IRQHandler; mov pc, r0");  // IRQ 17
  asm volatile("ldr r0, =I18_IRQHandler; mov pc, r0");  // IRQ 18
  asm volatile("ldr r0, =I19_IRQHandler; mov pc, r0");  // IRQ 19
  asm volatile("ldr r0, =I20_IRQHandler; mov pc, r0");  // IRQ 20
  asm volatile("ldr r0, =I21_IRQHandler; mov pc, r0");  // IRQ 21
  asm volatile("ldr r0, =I22_IRQHandler; mov pc, r0");  // IRQ 22
  asm volatile("ldr r0, =I23_IRQHandler; mov pc, r0");  // IRQ 23
  asm volatile("ldr r0, =I24_IRQHandler; mov pc, r0");  // IRQ 24
  asm volatile("ldr r0, =I25_IRQHandler; mov pc, r0");  // IRQ 25
  asm volatile("ldr r0, =I26_IRQHandler; mov pc, r0");  // IRQ 26
  asm volatile("ldr r0, =I27_IRQHandler; mov pc, r0");  // IRQ 27
  asm volatile("ldr r0, =I28_IRQHandler; mov pc, r0");  // IRQ 28
  asm volatile("ldr r0, =I29_IRQHandler; mov pc, r0");  // IRQ 29
  asm volatile("ldr r0, =I30_IRQHandler; mov pc, r0");  // IRQ 30
  asm volatile("ldr r0, =I31_IRQHandler; mov pc, r0");  // IRQ 31
}
