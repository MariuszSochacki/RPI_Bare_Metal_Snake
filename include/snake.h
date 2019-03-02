#ifndef SNAKE_H
#define SNAKE_H

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

void snake_init();
char snake_move(direction_t direction);

#endif  // SNAKE_H