#include "LCD12864A.h"
#include "assert.h"
#include "bool.h"
#include "buttons.h"
#include "rand.h"
#include "snake.h"
#include "timer.h"
#include "uart.h"

// TODO: Move to a separate file?
void *__stack_chk_guard = (void *)0xA5A5A5A5;
void __stack_chk_fail(void) { uart_puts("Stack protector fail!"); }

void main() {
  rand_init();
  uart_init();
  uart_puts("UART initialized\n");
  setupButtonsGPIO();

  lcd_init();
  uart_puts("LCD initialized\n");
  lcd_on();

  snake_init();

  while (1) {
    button_t button = getButtonPress();

    if (!snake_update(button)) {
      snake_init();
    }
  }
}