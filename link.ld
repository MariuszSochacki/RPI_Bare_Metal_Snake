SECTIONS
{
  . = 0x8000;
  .text : { KEEP(*(.text.boot)) *(.text .text.*) }
  .data : { *(.data .data.*) }
  .rodata : { *(.rodata .rodata.*) }
  .bss : { *(.bss .bss.*) }
}
