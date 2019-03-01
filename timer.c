#include "gpio.h"

#define SYSTMR_LO ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00003004))
#define SYSTMR_HI ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00003008))

unsigned long get_system_timer() {
  unsigned int h;
  unsigned int l;
  do {
    h = *SYSTMR_HI;
    l = *SYSTMR_LO;
  } while (h != *SYSTMR_HI);

  return ((unsigned long)h << 32) | l;
}

// TODO: Redefine to macro to save some function calls
void wait_until(unsigned long until) {
  while (until >= get_system_timer()) {
    asm("nop");
  }
}

void wait_s(unsigned ms) {
  unsigned long t = get_system_timer();
  wait_until(t + ms * 1000 * 1000);
}

void wait_ms(unsigned ms) {
  unsigned long t = get_system_timer();
  wait_until(t + ms * 1000);
}

void wait_us(unsigned long us) {
  unsigned long t = get_system_timer();
  wait_until(t + us);
}

void sleep(unsigned long cycles) {
  if (cycles) {
    while (cycles--) {
      asm volatile("nop");
    }
  }
}