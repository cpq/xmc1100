ENTRY(_reset);
MEMORY {
  flash(rx) : ORIGIN = 0x010001000, LENGTH = 64k  /* datasheet 7.2*/
  sram(rwx) : ORIGIN = 0x020000000, LENGTH = 16k
}
_estack     = ORIGIN(sram) + LENGTH(sram);    /* stack points to end of SRAM */

SECTIONS {
  .vectors  : { KEEP(*(.vectors)) }   > flash
  .text     : { *(.text*) }           > flash
  .rodata   : { *(.rodata*) }         > flash

  .data : {
    _sdata = .;
    KEEP(*(.first_data))
    *(.data SORT(.data.*))
    _edata = .;
  } > sram AT > flash
  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;
  } > sram

  . = ALIGN(8);
  _end = .;
}
