// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved

#include "mcu.h"

#define LED1 PIN('B', 0)  // On-board LED1 pin
#define LED2 PIN('B', 1)  // On-board LED2 pin
#define TX PIN('C', 1)    // UART TX pin
#define RX PIN('C', 2)    // UART RX pin
#define BAUD 115200

static volatile uint64_t s_ticks;

// Bit-bang implementation of UART TX
void uart_write(void *uart, const void *buf, size_t len) {
  unsigned cycles = FREQ / BAUD;
  for (size_t i = 0; i < len; i++) {
    uint8_t ch = ((const uint8_t *) buf)[i];
    gpio_write(TX, false), spin(cycles);  // Start bit low
    for (uint8_t j = 0; j < 8; j++) {
      gpio_write(TX, ch & (1U << j)), spin(cycles);  // Data bits
    }
    gpio_write(TX, true), spin(cycles);  // No parity. Stop bit high
  }
  (void) uart;
}

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
  systick_init(FREQ / 1000);
  gpio_output(LED1);
  gpio_output(TX);

  for (;;) {
    gpio_toggle(LED1);
    delay_ms(250);
    printf("hi\n");
  }

  return 0;
}
