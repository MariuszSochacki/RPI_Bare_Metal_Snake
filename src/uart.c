#include "gpio.h"
#include "timer.h"

#define UART_GPIO1 14
#define UART_GPIO2 15

#define AUX_ENABLE ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215004))
#define AUX_MU_IO ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215040))
#define AUX_MU_IER ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215044))
#define AUX_MU_IIR ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215048))
#define AUX_MU_LCR ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x0021504C))
#define AUX_MU_MCR ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215050))
#define AUX_MU_LSR ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215054))
#define AUX_MU_MSR ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215058))
#define AUX_MU_SCRATCH ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x0021505C))
#define AUX_MU_CNTL ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215060))
#define AUX_MU_STAT ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215064))
#define AUX_MU_BAUD ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00215068))

void uart_init() {
  *AUX_ENABLE |= 1;
  *AUX_MU_CNTL = 0;
  *AUX_MU_LCR = 3;
  *AUX_MU_MCR = 0;
  *AUX_MU_IER = 0;
  *AUX_MU_IIR = 0xc6;  
  *AUX_MU_BAUD = 270;  
  gpio_setup(UART_GPIO1, GPIO_MODE_ALTFUNC5, GPIO_PULL_NONE);
  gpio_setup(UART_GPIO2, GPIO_MODE_ALTFUNC5, GPIO_PULL_NONE);
  *AUX_MU_CNTL = 3;  
}

void uart_send(unsigned int c) {
  do {
    asm volatile("nop");
  } while (!(*AUX_MU_LSR & 0x20));
  *AUX_MU_IO = c;
}

char uart_getc() {
  char r;
  do {
    asm volatile("nop");
  } while (!(*AUX_MU_LSR & 0x01));
  r = (char)(*AUX_MU_IO);

  return r == '\r' ? '\n' : r;
}

void uart_puts(const char *s) {
  while (*s) {
    if (*s == '\n') uart_send('\r');
    uart_send(*s++);
  }
}