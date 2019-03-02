#include "snake.h"
#include "LCD12864A.h"
#include "bool.h"

#define MAP_SIZE_X 64
#define MAP_SIZE_Y 32

#define SNAKE_

point_t snake_position[MAP_SIZE_X * MAP_SIZE_Y];
char snake_length;
char last_direction;

void snake_display_point(point_t point, char on) {
  lcd_set_point(point.x * 2, point.y * 2, on);
  lcd_set_point(point.x * 2, point.y * 2 + 1, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2 + 1, on);
  lcd_display_area(point.x * 2, point.y * 2, point.x * 2 + 1, point.y * 2 + 1);
}

void snake_move(direction_t direction) {
  if ((direction == DIRECTION_DOWN && last_direction == DIRECTION_UP) ||
      (direction == DIRECTION_UP && last_direction == DIRECTION_DOWN) ||
      (direction == DIRECTION_LEFT && last_direction == DIRECTION_RIGHT) ||
      (direction == DIRECTION_RIGHT && last_direction == DIRECTION_LEFT)) {
    direction = last_direction;
  }
  last_direction = direction;

  snake_display_point(snake_position[snake_length - 1], FALSE);
  for (int i = snake_length - 1; i > 0; i--) {
    snake_position[i] = snake_position[i - 1];
  }

  switch (direction) {
    case DIRECTION_UP:
      snake_position[0].y += 1;
      break;
    case DIRECTION_RIGHT:
      snake_position[0].x += 1;
      break;
    case DIRECTION_DOWN:
      snake_position[0].y -= 1;
      break;
    case DIRECTION_LEFT:
      snake_position[0].x -= 1;
      break;
    default:
      break;  // TODO: Assert
  }

  snake_position[0].x = snake_position[0].x % MAP_SIZE_X;
  snake_position[0].y = snake_position[0].y % MAP_SIZE_Y;

  snake_display_point(snake_position[0], TRUE);
}

void snake_init() {
  snake_length = 10;
  last_direction = DIRECTION_RIGHT;
  for (int i = 0; i < 10; i++) {
    point_t position;
    position.x = MAP_SIZE_X / 2 - i;
    position.y = MAP_SIZE_Y / 2;
    snake_position[i] = position;

    snake_display_point(position, TRUE);
  }
}