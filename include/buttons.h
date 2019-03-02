#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum {
  BUTTON_NONE = 0,
  BUTTON_UP = 1,
  BUTTON_RIGHT = 2,
  BUTTON_DOWN = 3,
  BUTTON_LEFT = 4
} button_t;
button_t getButtonPress();
char setupButtonsGPIO();

#endif  // BUTTONS_H