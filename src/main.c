#include "LCD12864A.h"
#include "bool.h"
#include "buttons.h"
#include "gpio.h"  // TODO: Remove
#include "timer.h"
#include "uart.h"

// TODO: Move somewhere else
void *__stack_chk_guard = (void *)0xA5A5A5A5;
void __stack_chk_fail(void) { uart_puts("Stack protector fail!"); }

void main() {
  uart_init();

  if (setupButtonsGPIO() == TRUE) {
    uart_puts("Set up buttons\n");
  } else {
    uart_puts("Failed to set up buttons\n");
  }

  if (setupLCDGPIO() == TRUE) {
    uart_puts("Set up LCD\n");
  } else {
    uart_puts("Failed to set up LCD\n");
  }

  lcd_init();
  uart_puts("LCD initialized\n");

  while (1) {
    BUTTON button = getButtonPress();
    switch (button) {
      case BUTTON_UP:
        lcd_on();
        uart_puts("LCD on\n");
        break;
      case BUTTON_DOWN:
        lcd_off();
        uart_puts("LCD off\n");
        break;
      case BUTTON_LEFT:
        uart_puts("Button left pressed\n");
        break;
      case BUTTON_RIGHT:
        uart_puts("Button right pressed\n");
        break;
      case BUTTON_NONE:
        continue;
      default:
        uart_puts("Invalid button pressed?\n");
        wait_s(5);
        break;
    }
    wait_ms(250);
  }
}