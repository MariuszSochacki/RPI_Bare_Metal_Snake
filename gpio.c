#include "gpio.h"
#include "bool.h"
#include "timer.h"

char gpio_setup(unsigned int gpio, GPIO_MODE gpio_mode,
                GPIO_IN_PULL_MODE pull_mode) {
  unsigned int* gpfsel = GPFSEL0;
  if (gpio > 53) {
    return FALSE;
  }
  if (gpio_mode < 0 || gpio_mode > GPIO_MODE_MAX) {
    return FALSE;
  }
  if (pull_mode < 0 || pull_mode > GPIO_IN_PULL_MODE_MAX) {
    return FALSE;
  }

  if (pull_mode != GPIO_IN_PULL_MODE_REMAIN) {
    unsigned int* gppudclk = GPPUDCLK0;
    *GPPUD = pull_mode;
    sleep(150);
    gppudclk[gpio / 32] = 1 << (gpio % 32);
    sleep(150);
    *GPPUD = 0;
    gppudclk[gpio / 32] = 0;
  }

  unsigned int bit = ((gpio % 10) * 3);
  unsigned int mem = gpfsel[gpio / 10];
  mem &= ~(7 << bit);
  mem |= (gpio_mode << bit);
  gpfsel[gpio / 10] = mem;
  return TRUE;
}

// TODO: Fix potential change of other bits?
char gpio_output(unsigned int gpio, char on) {
  if (gpio > 53) {
    return FALSE;
  }
  volatile unsigned int* p;
  unsigned int bit = 1 << (gpio % 32);
  unsigned int regnum = gpio / 32;

  if (on == FALSE) {
    p = GPCLR0;
  } else {
    p = GPSET0;
  }

  p[regnum] = bit;
  return TRUE;
}

char gpio_input(unsigned int gpio) {
  volatile unsigned int* gplev = GPLEV0;
  if (gpio > 53) {
    return FALSE;
  }

  unsigned int bit = 1 << (gpio % 32);
  unsigned int mem = gplev[gpio / 32];
  if (mem & bit) return TRUE;

  return FALSE;
}