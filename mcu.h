// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved
// Datasheet:
// https://www.mouser.ie/datasheet/2/297/nRF52840_PS_v1.1-1623672.pdf

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BIT(x) (1UL << (x))
#define SETBITS(R, CLEARMASK, SETMASK) (R) = ((R) & ~(CLEARMASK)) | (SETMASK)
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)
#define FREQ 32000000

static inline void spin(volatile uint32_t count) {
  while (count--) asm("nop");
}

struct ccu {
  volatile uint32_t CLKCR, PWRSVCR, CGATSTAT0, CGATSET0, CGATCLR0, OSCCSR;
};
#define CCU ((struct ccu *) 0x40010300)

struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xe000e010)
static inline void systick_init(uint32_t ticks) {
  if ((ticks - 1) > 0xffffff) return;  // Systick timer is 24 bit
  SYSTICK->LOAD = ticks - 1;
  SYSTICK->VAL = 0;
  SYSTICK->CTRL = BIT(0) | BIT(1) | BIT(2);  // Enable systick
}

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF };
enum { GPIO_OTYPE_PUSH_PULL, GPIO_OTYPE_OPEN_DRAIN };
enum { GPIO_PULL_NONE, GPIO_PULL_DOWN, GPIO_PULL_UP };

struct gpio {
  volatile uint32_t OUT, OMR, RSVD1[2], IOCR[4], RSVD2, IN;
};
#define GPIO(N) ((struct gpio *) (0x40040000 + 0x100 * (N)))

static struct gpio *gpio_bank(uint16_t pin) {
  return GPIO(PINBANK(pin));
}
static inline void gpio_init(uint16_t pin, uint8_t mode, uint8_t type,
                             uint8_t pull, uint8_t af) {
  struct gpio *gpio = gpio_bank(pin);
  uint8_t n = (uint8_t) (PINNO(pin));
  uint32_t bits = 0;
  if (mode == GPIO_MODE_INPUT) {
    bits |= pull & 3U;
  } else {
    bits |= BIT(5);
    if (type == GPIO_OTYPE_OPEN_DRAIN) bits |= BIT(4);
    if (af > 0) bits |= af & 7U;
  }
  gpio->IOCR[n >> 8] = (bits << 2U) << ((n & 3U) * 8U);
}
static inline void gpio_output(uint16_t pin) {
  gpio_init(pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_PULL_NONE, 0);
}
static inline void gpio_input(uint16_t pin) {
  gpio_init(pin, GPIO_MODE_INPUT, GPIO_OTYPE_PUSH_PULL, GPIO_PULL_NONE, 0);
}
static inline int gpio_read(uint16_t pin) {
  return gpio_bank(pin)->IN & BIT(PINNO(pin)) ? 1 : 0;
}
static inline void gpio_write(uint16_t pin, bool val) {
  struct gpio *gpio = gpio_bank(pin);
  gpio->OMR |= BIT(PINNO(pin)) << (val ? 0 : 16);
}
static inline void gpio_toggle(uint16_t pin) {
  struct gpio *gpio = gpio_bank(pin);
  uint8_t n = (uint8_t) (PINNO(pin));
  gpio_write(pin, gpio->OUT & BIT(n) ? 0 : 1);
}

struct usic {
  volatile uint32_t RSVD1, CCFG, ID, KSCFG, FDR, BRG, INPR, DXCR[6], SCTR, TCSR,
      PCR, CCR, CMTR, PSR, PSCR, RBUFSR, RBUF, RBUFD, RBUF0, RBUF1, RBUF01SR,
      FMR, RSVD2[5], TBUF[32], BYP, BYPCR, TBCTR, RBCTR, TRBPTR, TRBSR, TRBSCR,
      OUTR, OUTDR;
};
#define USIC(N) ((struct usic *) (0x48000000 + 0x200 * (N)))
#define UART_DEBUG USIC(0)

extern void uart_write(void *uart, const void *buf, size_t len);

static inline void clock_init(void) {
}
