#include "buttons.h"
#include "bool.h"
#include "gpio.h"

#define BUTTON_UP_GPIO 26
#define BUTTON_DOWN_GPIO 6
#define BUTTON_LEFT_GPIO 13
#define BUTTON_RIGHT_GPIO 19

BUTTON getButtonPress() {
  if (gpio_input(BUTTON_UP_GPIO) == TRUE) {
    return BUTTON_UP;
  }
  if (gpio_input(BUTTON_DOWN_GPIO) == TRUE) {
    return BUTTON_DOWN;
  }
  if (gpio_input(BUTTON_LEFT_GPIO) == TRUE) {
    return BUTTON_LEFT;
  }
  if (gpio_input(BUTTON_RIGHT_GPIO) == TRUE) {
    return BUTTON_RIGHT;
  }
  return BUTTON_NONE;
}

char setupButtonsGPIO() {
  if (gpio_setup(BUTTON_UP_GPIO, GPIO_MODE_INPUT, GPIO_IN_PULL_DOWN) == FALSE) {
    return FALSE;
  }
  if (gpio_setup(BUTTON_DOWN_GPIO, GPIO_MODE_INPUT, GPIO_IN_PULL_DOWN) ==
      FALSE) {
    return FALSE;
  }
  if (gpio_setup(BUTTON_LEFT_GPIO, GPIO_MODE_INPUT, GPIO_IN_PULL_DOWN) ==
      FALSE) {
    return FALSE;
  }
  if (gpio_setup(BUTTON_RIGHT_GPIO, GPIO_MODE_INPUT, GPIO_IN_PULL_DOWN) ==
      FALSE) {
    return FALSE;
  }

  return TRUE;
}