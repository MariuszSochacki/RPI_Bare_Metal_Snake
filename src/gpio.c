#include "gpio.h"
#include "assert.h"
#include "bool.h"
#include "timer.h"

void gpio_setup(unsigned int gpio, gpio_mode_t gpio_mode,
                gpio_pull_mode_t pull_mode) {
  volatile unsigned int* gpfsel = GPFSEL0;

  ASSERT(gpio <= 53, "GPIO port out of range\n");
  ASSERT(gpio_mode >= 0 && gpio_mode <= GPIO_MODE_MAX,
         "GPIO mode out of range\n");
  ASSERT(pull_mode >= 0 && pull_mode <= GPIO_PULL_MODE_MAX,
         "Pull mode out of range\n");

  if (pull_mode != GPIO_PULL_MODE_REMAIN) {
    volatile unsigned int* gppudclk = GPPUDCLK0;
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
}

void gpio_output(unsigned int gpio, char on) {
  ASSERT(gpio <= 53, "GPIO port out of range\n");

  volatile unsigned int* p;
  unsigned int bit = 1 << (gpio % 32);
  unsigned int regnum = gpio / 32;

  if (!on) {
    p = GPCLR0;
  } else {
    p = GPSET0;
  }

  p[regnum] = bit;
}

char gpio_input(unsigned int gpio) {
  volatile unsigned int* gplev = GPLEV0;
  ASSERT(gpio <= 53, "GPIO port out of range\n");

  unsigned int bit = 1 << (gpio % 32);
  unsigned int mem = gplev[gpio / 32];
  if (mem & bit) return TRUE;

  return FALSE;
}