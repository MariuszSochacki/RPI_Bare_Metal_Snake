#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum {
  BUTTON_NONE,
  BUTTON_UP,
  BUTTON_RIGHT,
  BUTTON_DOWN,
  BUTTON_LEFT
} BUTTON;
BUTTON getButtonPress();
char setupButtonsGPIO();

#endif  // BUTTONS_H