#ifndef TIMER_H
#define TIMER_H

typedef struct {
  unsigned long last;
  unsigned interval;
} timer_t;

void timer_init(timer_t *timer, unsigned interval_ms);
char timer_update(timer_t *timer);

unsigned long get_current_time();

void wait_until(unsigned long until);

void wait_s(unsigned s);
void wait_ms(unsigned ms);
void wait_us(unsigned long us);
void sleep(unsigned long cycles);

#endif // TIMER_H