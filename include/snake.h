#ifndef SNAKE_H
#define SNAKE_H
#include "buttons.h"

typedef enum {
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_RIGHT,
  DIRECTION_LEFT
} direction_t;

typedef struct {
  char x;
  char y;
} point_t;

/** Initializes the snake game
 * Clears the LCD screen and puts on the starting state of the snake on it
 */
void snake_init();

/** Notifies the game to update it's logic
 * @param button The button that is pressed now or BUTTON_NONE
 * @return Zero if game finished. Non-zero if not finished.
 */
char snake_update(button_t button);

#endif  // SNAKE_H