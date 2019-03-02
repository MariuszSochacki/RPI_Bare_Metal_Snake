.section ".text.boot"

.globl _start
_start:
    mov sp,#0x00010000 // TODO: BSS clear, separate cores
    bl main
hang: b hang
