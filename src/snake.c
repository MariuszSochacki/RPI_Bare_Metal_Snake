#include "snake.h"
#include "LCD12864A.h"
#include "bool.h"
#include "rand.h"
#include "timer.h"

#define MAP_SIZE_X 64
#define MAP_SIZE_Y 32

#define SNAKE_INITIAL_LENGTH 10

point_t snake_position[MAP_SIZE_X * MAP_SIZE_Y];
unsigned char snake_length;
char last_direction;
point_t food_position;

char is_empty_space(point_t point) {
  for (int i = 0; i < snake_length; i++) {
    if ((snake_position[i].x == point.x) && (snake_position[i].y == point.y)) {
      return FALSE;
    }
  }
  return TRUE;
}

void snake_display_point(point_t point, char on) {
  lcd_set_point(point.x * 2, point.y * 2, on);
  lcd_set_point(point.x * 2, point.y * 2 + 1, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2 + 1, on);
  lcd_display_area(point.x * 2, point.y * 2, point.x * 2 + 1, point.y * 2 + 1);
}

void spawn_food() {
  food_position.x = rand(0, MAP_SIZE_X);
  food_position.y = rand(0, MAP_SIZE_Y);

  while (!is_empty_space(food_position)) {
    food_position.x++;
    food_position.y = food_position.y + food_position.x / MAP_SIZE_X;
    food_position.x = food_position.x % MAP_SIZE_X;
  }

  snake_display_point(food_position, TRUE);
}

char snake_move(direction_t direction) {
  if ((direction == DIRECTION_DOWN && last_direction == DIRECTION_UP) ||
      (direction == DIRECTION_UP && last_direction == DIRECTION_DOWN) ||
      (direction == DIRECTION_LEFT && last_direction == DIRECTION_RIGHT) ||
      (direction == DIRECTION_RIGHT && last_direction == DIRECTION_LEFT)) {
    direction = last_direction;
  }
  last_direction = direction;

  point_t new_head_position = snake_position[0];

  switch (direction) {
    case DIRECTION_UP:
      new_head_position.y += 1;
      break;
    case DIRECTION_RIGHT:
      new_head_position.x += 1;
      break;
    case DIRECTION_DOWN:
      new_head_position.y -= 1;
      break;
    case DIRECTION_LEFT:
      new_head_position.x -= 1;
      break;
    default:
      break;  // TODO: Assert
  }

  new_head_position.x = new_head_position.x % MAP_SIZE_X;
  new_head_position.y = new_head_position.y % MAP_SIZE_Y;

  if ((new_head_position.x == food_position.x) &&
      (new_head_position.y == food_position.y)) {
    snake_position[snake_length] = snake_position[snake_length - 1];
    snake_length++;

    if (snake_length < MAP_SIZE_X * MAP_SIZE_Y) {
      spawn_food();
    }
  } else if (!is_empty_space(new_head_position)) {
    lcd_invert_color(TRUE);
    wait_ms(1000);
    lcd_invert_color(FALSE);
    wait_ms(1000);
    lcd_invert_color(TRUE);
    wait_ms(1000);
    lcd_invert_color(FALSE);
    wait_ms(1000);

    return TRUE;
  }

  snake_display_point(snake_position[snake_length - 1], FALSE);
  for (int i = snake_length - 1; i > 0; i--) {
    snake_position[i] = snake_position[i - 1];
  }

  snake_position[0].x = new_head_position.x;
  snake_position[0].y = new_head_position.y;

  snake_display_point(snake_position[0], TRUE);
  return FALSE;
}

void snake_init() {
  lcd_fill(0);
  lcd_display();
  snake_length = SNAKE_INITIAL_LENGTH;
  last_direction = DIRECTION_RIGHT;
  for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
    point_t position;
    position.x = MAP_SIZE_X / 2 - i;
    position.y = MAP_SIZE_Y / 2;
    snake_position[i] = position;

    snake_display_point(position, TRUE);
  }
  spawn_food();
}