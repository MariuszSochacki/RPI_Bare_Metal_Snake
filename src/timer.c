#include "timer.h"
#include "bool.h"
#include "gpio.h"

#define SYSTMR_LO ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00003004))
#define SYSTMR_HI ((volatile unsigned int *)(PI_IOBASE_ADDR + 0x00003008))

#define WAIT_UNTIL(x)                                   \
  {                                                     \
    while (x > get_system_timer()) asm volatile("nop"); \
  }

static unsigned long get_system_timer() {
  unsigned int h;
  unsigned int l;
  do {
    h = *SYSTMR_HI;
    l = *SYSTMR_LO;
  } while (h != *SYSTMR_HI);

  return ((unsigned long)h << 32) | l;
}

// TODO: Redefine to macro to save some function calls?
void wait_until(unsigned long until) {
  while (until >= get_system_timer()) {
    asm volatile("nop");
  }
}

void wait_s(unsigned s) {
  unsigned long t = get_system_timer();
  WAIT_UNTIL(t + s * 1000 * 1000);
}

void wait_ms(unsigned ms) {
  unsigned long t = get_system_timer();
  WAIT_UNTIL(t + ms * 1000);
}

void wait_us(unsigned long us) {
  unsigned long t = get_system_timer();
  WAIT_UNTIL(t+ us);
}

void sleep(unsigned long cycles) {
  if (cycles) {
    while (cycles--) {
      asm volatile("nop");
    }
  }
}

void timer_init(timer_t *timer, unsigned interval_ms) {
  timer->interval = interval_ms * 1000;
  timer->last = get_system_timer();
}

char timer_update(timer_t *timer) {
  if (get_system_timer() > timer->last + timer->interval) {
    timer->last = timer->last + timer->interval;
    return TRUE;
  }
  return FALSE;
}