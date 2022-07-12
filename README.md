# Baremetal firmware for xmc1100 2Go devboard

This firmware implements a simple blinky on an Infineon XMC1100 2Go
development board, based on a 32Mhz Cortex-M0 MCU with 16k RAM, 64k flash, and
some peripherals including WDT, RTC, PRNG, USIC (serial: SPI, I2C, UART), ADC,
GPIO and a temperature sensor. The
[data sheet](https://www.infineon.com/dgdl/Infineon-xmc1100-AB_rm-UM-v01_03-EN.pdf?fileId=5546d46249cd1014014a0a8438a65e29#page=769&zoom=100,48,401)
available from the Infineon website.

## xmc1100 2Go devboard

<img src="https://eu.mouser.com/images/marketingid/2014/img/156264930.png?v=031122.0341" width="200" />

This little development board has a built-in j-link compatible debugger,
which makes it easy to program and debug using Segger j-link software.
It has 2 on-board LEDs, attached to P1.0 and P1.1 (in the source code,
those are pins B0 and B1). Both pins are red.

## Software Requirements

- ARM GCC, https://launchpad.net/gcc-arm-embedded
- GNU make, http://www.gnu.org/software/make/
- J-Link software, http://www.segger.com/jlink-software.html

## Build and flash

```sh
$ make build flash 
```
