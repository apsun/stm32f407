MEMORY
{
  FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 1024K
  RAM (rw) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    . = ALIGN(4);
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  .data :
  {
    _sdata = .;
    . = ALIGN(4);
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT> FLASH /* address is in RAM, but initializer data is in flash */

  .bss :
  {
    _sbss = .;
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM
}

/* place stack top at the end of RAM */
_estack = 0x20020000;

/* where the initializer data is in flash */
_sidata = LOADADDR(.data);
