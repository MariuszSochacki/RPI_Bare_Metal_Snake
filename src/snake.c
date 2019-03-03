#include "snake.h"
#include "LCD12864A.h"
#include "assert.h"
#include "bool.h"
#include "rand.h"
#include "timer.h"

#define MAP_SIZE_X 64
#define MAP_SIZE_Y 32

#define SNAKE_INITIAL_LENGTH 10
#define SNAKE_SLOWEST_UPDATE_MS 700

typedef enum {
  SNAKE_GAME_STATE_DIFFICULTY_SELECT,
  SNAKE_GAME_STATE_PLAYING
} snake_game_state_t;

static point_t snake_position[MAP_SIZE_X * MAP_SIZE_Y];
static unsigned char snake_length;
static direction_t last_direction;
static point_t food_position;
static timer_t timer;
static snake_game_state_t game_state;
static char difficulty;
static button_t last_button;

static direction_t button_to_direction(button_t button) {
  if (button == BUTTON_UP) return DIRECTION_UP;
  if (button == BUTTON_RIGHT) return DIRECTION_RIGHT;
  if (button == BUTTON_DOWN) return DIRECTION_DOWN;
  if (button == BUTTON_LEFT) return DIRECTION_LEFT;

  ABORT("Illegal button");
  return button_to_direction(DIRECTION_DOWN);  // Silence warning
}

static char is_empty_space(point_t point) {
  for (int i = 0; i < snake_length; i++) {
    if ((snake_position[i].x == point.x) && (snake_position[i].y == point.y)) {
      return FALSE;
    }
  }
  return TRUE;
}

static void snake_display_point(point_t point, char on) {
  lcd_set_point(point.x * 2, point.y * 2, on);
  lcd_set_point(point.x * 2, point.y * 2 + 1, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2, on);
  lcd_set_point(point.x * 2 + 1, point.y * 2 + 1, on);
  lcd_display_area(point.x * 2, point.y * 2, point.x * 2 + 1, point.y * 2 + 1);
}

static void spawn_food() {
  food_position.x = rand(0, MAP_SIZE_X);
  food_position.y = rand(0, MAP_SIZE_Y);

  while (!is_empty_space(food_position)) {
    food_position.x++;
    food_position.y = food_position.y + food_position.x / MAP_SIZE_X;
    food_position.x = food_position.x % MAP_SIZE_X;
  }
}

char snake_update(button_t button) {
  last_button = (button != BUTTON_NONE) ? button : last_button;
  if (!timer_update(&timer)) {
    return TRUE;
  }

  if (game_state == SNAKE_GAME_STATE_DIFFICULTY_SELECT) {
    if (button == BUTTON_RIGHT) {
      difficulty++;
    } else if (button == BUTTON_LEFT) {
      difficulty--;
    } else if (button != BUTTON_NONE) {
      timer_init(&timer, SNAKE_SLOWEST_UPDATE_MS / difficulty);
      game_state = SNAKE_GAME_STATE_PLAYING;
      lcd_fill(0);
      lcd_display();
      last_direction = DIRECTION_RIGHT;
      last_button = BUTTON_NONE;
      return TRUE;
    }

    difficulty = (difficulty < 1) ? 1 : difficulty;
    difficulty = (difficulty > 10) ? 10 : difficulty;

    for (char i = 1; i <= 10; i++) {
      point_t point;
      point.x = 5 + (i - 1) * 6;
      point.y = MAP_SIZE_Y / 2;
      snake_display_point(point, (difficulty >= i));
    }

    last_button = BUTTON_NONE;
    return TRUE;
  }

  direction_t direction;

  if (last_button == BUTTON_NONE ||
      ((last_button == BUTTON_DOWN && last_direction == DIRECTION_UP) ||
       (last_button == BUTTON_UP && last_direction == DIRECTION_DOWN) ||
       (last_button == BUTTON_LEFT && last_direction == DIRECTION_RIGHT) ||
       (last_button == BUTTON_RIGHT && last_direction == DIRECTION_LEFT))) {
    direction = last_direction;
  } else {
    direction = button_to_direction(last_button);
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
      ABORT("Illegal direction");
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

    return FALSE;
  }

  snake_display_point(snake_position[snake_length - 1], FALSE);
  for (int i = snake_length - 1; i > 0; i--) {
    snake_position[i] = snake_position[i - 1];
  }

  snake_position[0].x = new_head_position.x;
  snake_position[0].y = new_head_position.y;

  snake_display_point(snake_position[0], TRUE);
  snake_display_point(food_position, TRUE);
  last_button = BUTTON_NONE;
  return TRUE;
}

void snake_init() {
  game_state = SNAKE_GAME_STATE_DIFFICULTY_SELECT;
  difficulty = 5;
  lcd_fill(0);
  lcd_display();
  snake_length = SNAKE_INITIAL_LENGTH;
  last_direction = DIRECTION_RIGHT;
  for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
    point_t position;
    position.x = MAP_SIZE_X / 2 - i;
    position.y = MAP_SIZE_Y / 2;
    snake_position[i] = position;
  }
  spawn_food();
  last_button = BUTTON_NONE;
  timer_init(&timer, 150);
}