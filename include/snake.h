#ifndef SNAKE_H
#define SNAKE_H

typedef enum {
  DIRECTION_UP = 0,
  DIRECTION_DOWN = 1,
  DIRECTION_RIGHT = 2,
  DIRECTION_LEFT = 3
} direction_t;

typedef struct {
  char x;
  char y;
} point_t;

void snake_init();
void snake_move(direction_t direction);

#endif  // SNAKE_H