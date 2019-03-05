.section ".text.boot"

.globl _start
_start:
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbnz    x1, hang
    ldr     x1, =_start
    mov     sp, x1
    bl main
hang:
    wfe
    b hang
