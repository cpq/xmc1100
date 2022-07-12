// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved

#include "mcu.h"

#define LED1 PIN('B', 0)  // On-board LED1 pin
#define LED2 PIN('B', 1)  // On-board LED2 pin

static volatile uint64_t s_ticks;

static inline void delay_ms(unsigned long ms) {
  uint64_t until = s_ticks + ms;
  while (s_ticks < until) spin(1);
}

void DefaultIRQHandler(void) {              // Catch-all fault handler
  gpio_output(LED2);                        // Setup LED
  for (;;) gpio_toggle(LED2), spin(49999);  // Blink LED infinitely
}

void SysTick_Handler(void) {  // SyStick IRQ handler, triggered every 1ms
  s_ticks++;
}

int main(void) {
  clock_init();
  gpio_output(LED1);

  for (;;) {
    gpio_toggle(LED1);
    delay_ms(250);
  }

  return 0;
}
