#include "LCD12864A.h"
#include "bool.h"
#include "buttons.h"
#include "snake.h"
#include "timer.h"
#include "uart.h"

// TODO: Move somewhere else
void *__stack_chk_guard = (void *)0xA5A5A5A5;
void __stack_chk_fail(void) { uart_puts("Stack protector fail!"); }

void main() {
  uart_init();
  direction_t direction = DIRECTION_RIGHT;

  if (setupButtonsGPIO()) {
    uart_puts("Set up buttons\n");
  } else {
    uart_puts("Failed to set up buttons\n");
    return;
  }

  if (setupLCDGPIO()) {
    uart_puts("Set up LCD\n");
  } else {
    uart_puts("Failed to set up LCD\n");
    return;
  }

  lcd_init();
  uart_puts("LCD initialized\n");
  lcd_on();
  lcd_fill(0);
  lcd_display();

  snake_init();

  timer_t timer;
  timer_init(&timer, 300);

  while (1) {
    button_t button = getButtonPress();

    switch (button) {
      case BUTTON_NONE:
        break;
      case BUTTON_UP:
        direction = DIRECTION_UP;
        break;
      case BUTTON_DOWN:
        direction = DIRECTION_DOWN;
        break;
      case BUTTON_LEFT:
        direction = DIRECTION_LEFT;
        break;
      case BUTTON_RIGHT:
        direction = DIRECTION_RIGHT;
        break;
      default:
        uart_puts("Invalid button pressed\n");
        wait_s(5);
        return;
    }
    if (timer_update(&timer)) {
      snake_move(direction);
    }
  }
}