#ifndef TIMER_H
#define TIMER_H

typedef struct {
  unsigned long last;
  unsigned interval;
} timer_t;

/** Initializes and starts the timer
 * @param timer Timer structure to initialize
 * @param interval_ms Interval between notifications
 */
void timer_init(timer_t *timer, unsigned interval_ms);

/** Updates the timer logic
 * @param timer Timer structure to update
 * @return Zero if enough time has not passed yet. Non-zero if event was fired
 */
char timer_update(timer_t *timer);

/** Waits given number of seconds
 * @param s Number of seconds
 */
void wait_s(unsigned s);

/** Waits given number of miliseconds
 * @param s Number of miliseconds
 */
void wait_ms(unsigned ms);

/** Waits given number of microseconds
 * @param s Number of microseconds
 */
void wait_us(unsigned long us);

/** Waits given number of cycles
 * @param s Number of cycles
 */
void sleep(unsigned long cycles);

#endif  // TIMER_H