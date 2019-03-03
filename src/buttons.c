#include "buttons.h"
#include "bool.h"
#include "gpio.h"

#define BUTTON_UP_GPIO 6
#define BUTTON_DOWN_GPIO 26
#define BUTTON_LEFT_GPIO 19
#define BUTTON_RIGHT_GPIO 13

button_t getButtonPress() {
  if (gpio_input(BUTTON_UP_GPIO)) {
    return BUTTON_UP;
  }
  if (gpio_input(BUTTON_DOWN_GPIO)) {
    return BUTTON_DOWN;
  }
  if (gpio_input(BUTTON_LEFT_GPIO)) {
    return BUTTON_LEFT;
  }
  if (gpio_input(BUTTON_RIGHT_GPIO)) {
    return BUTTON_RIGHT;
  }
  return BUTTON_NONE;
}

void setupButtonsGPIO() {
  gpio_setup(BUTTON_UP_GPIO, GPIO_MODE_INPUT, GPIO_PULL_DOWN);
  gpio_setup(BUTTON_DOWN_GPIO, GPIO_MODE_INPUT, GPIO_PULL_DOWN);
  gpio_setup(BUTTON_LEFT_GPIO, GPIO_MODE_INPUT, GPIO_PULL_DOWN);
  gpio_setup(BUTTON_RIGHT_GPIO, GPIO_MODE_INPUT, GPIO_PULL_DOWN);
}