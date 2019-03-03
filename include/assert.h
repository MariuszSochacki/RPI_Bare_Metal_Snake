#ifndef ASSERT_H
#define ASSERT_H

#include "uart.h"

#define ABORT(x)           \
  {                        \
    uart_puts(__func__);   \
    uart_puts(": ");       \
    uart_puts(x);          \
    while (1) {            \
      asm volatile("nop"); \
    }                      \
  }

#define ASSERT(x, s)    \
  {                     \
    if (!(x)) ABORT(s); \
  }

#endif  // ASSERT_H