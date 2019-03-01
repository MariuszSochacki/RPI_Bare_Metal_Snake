#ifndef TIMER_H
#define TIMER_H

unsigned long get_current_time();

void wait_until(unsigned long until);

void wait_s(unsigned s);
void wait_ms(unsigned ms);
void wait_us(unsigned long us);
void sleep(unsigned long cycles);

#endif // TIMER_H