#include "LCD12864A.h"
#include "bool.h"
#include "gpio.h"
#include "timer.h"

#define SCL_GPIO 4
#define SI_GPIO 17
#define A0_GPIO 27
#define RESET_GPIO 22
#define CS_GPIO 5

#define CMD_DISPLAY_ON 0xAF
#define CMD_DISPLAY_OFF 0xAE
#define CMD_ADC_NORMAL 0xA0
#define CMD_OUTPUT_MODE_NORMAL 0xC0
#define CMD_SET_BIAS_19 0xA2
// For explanation see:
// http://www.newhavendisplay.com/app_notes/ST7565P.pdf page 31
#define CMD_POWER_CIRCUIT_FULL 0x2F
#define CMD_RESISTOR_RATIO_6 0x26
// Should be followed with a value as said at page 47
#define CMD_ELECTRONIC_VOLUME_SET 0x81
#define CMD_SET_PAGE 0xB0
#define CMD_SET_COLUMN_H 0x10
#define CMD_SET_COLUMN_L 0x00
#define CMD_SET_LINE_0 0x40

#define LCD_WIDTH 128
#define LCD_HEIGHT 64
#define PAGE_COUNT 8
#define PIXEL_MAP_SIZE (LCD_WIDTH * PAGE_COUNT)

char pixel_map[PIXEL_MAP_SIZE];

char setupLCDGPIO() {
  if (!gpio_setup(SCL_GPIO, GPIO_MODE_OUTPUT, GPIO_PULL_UP)) {
    return FALSE;
  }
  if (!gpio_setup(SI_GPIO, GPIO_MODE_OUTPUT, GPIO_PULL_UP)) {
    return FALSE;
  }
  if (!gpio_setup(A0_GPIO, GPIO_MODE_OUTPUT, GPIO_PULL_UP)) {
    return FALSE;
  }
  if (!gpio_setup(RESET_GPIO, GPIO_MODE_OUTPUT, GPIO_PULL_UP)) {
    return FALSE;
  }
  if (!gpio_setup(CS_GPIO, GPIO_MODE_OUTPUT, GPIO_PULL_UP)) {
    return FALSE;
  }

  return TRUE;
}

void sendBytes(char bytes) {
  int i;
  for (i = 7; i >= 0; i--) {
    gpio_output(SCL_GPIO, 0);
    wait_us(5);
    char bit = bytes & 0x80;
    bytes = bytes << 1;
    gpio_output(SI_GPIO, bit);
    wait_us(5);
    gpio_output(SCL_GPIO, 1);
  }
}

void sendCommand(char command) {
  gpio_output(A0_GPIO, 0);
  sendBytes(command);
}
void sendData(char data) {
  gpio_output(A0_GPIO, 1);
  sendBytes(data);
}

void lcd_init() {
  gpio_output(CS_GPIO, 0);
  gpio_output(RESET_GPIO, 0);

  wait_ms(500);
  gpio_output(RESET_GPIO, 1);
  wait_ms(500);
  sendCommand(CMD_SET_BIAS_19);
  sendCommand(CMD_ADC_NORMAL);
  sendCommand(CMD_POWER_CIRCUIT_FULL);
  sendCommand(CMD_RESISTOR_RATIO_6);
  sendCommand(CMD_OUTPUT_MODE_NORMAL);
  lcd_fill(0);
}

void lcd_on() { sendCommand(CMD_DISPLAY_ON); }

void lcd_off() { sendCommand(CMD_DISPLAY_OFF); }

void lcd_fill(char byte) {
  for (int i = 0; i < PIXEL_MAP_SIZE; i++) {
    pixel_map[i] = byte;
  }
}

void lcd_set_point(unsigned char x, unsigned char y, char on) {
  char page = y / PAGE_COUNT;
  char offset_y = y % PAGE_COUNT;
  if (on) {
    pixel_map[x + page * LCD_WIDTH] =
        pixel_map[x + page * LCD_WIDTH] | (1 << offset_y);
  } else {
    pixel_map[x + page * LCD_WIDTH] =
        pixel_map[x + page * LCD_WIDTH] & ~(1 << offset_y);
  }
}

void lcd_display() {
  for (char page = 0; page < PAGE_COUNT; page++) {
    sendCommand(CMD_SET_PAGE | page);
    sendCommand(CMD_SET_COLUMN_H);
    sendCommand(CMD_SET_COLUMN_L);
    for (char x = 0; x < LCD_WIDTH; x++) {
      sendData(pixel_map[x + page * LCD_WIDTH]);
    }
  }
}

void lcd_display_area(unsigned char x1, unsigned char y1, unsigned char x2,
                      unsigned char y2) {
  //sendCommand(CMD_SET_LINE_0 + x1);
  for (char page = y1 / PAGE_COUNT; page <= y2 / PAGE_COUNT; page++) {
    sendCommand(CMD_SET_PAGE | page);
    sendCommand(CMD_SET_COLUMN_H | ((x1 >> 4) & 0xf));
    sendCommand(CMD_SET_COLUMN_L | (x1 & 0xf));
    for (char x = x1; x <= x2; x++) {
      sendData(pixel_map[x + page * LCD_WIDTH]);
    }
  }
}
/*
void lcd_display_page(char page) {
  sendCommand(CMD_SET_PAGE | page);
  sendCommand(CMD_SET_COLUMN_H);
  sendCommand(CMD_SET_COLUMN_L);
  for (char x = LCD_WIDTH/2; x < LCD_WIDTH; x++) {
    sendData(pixel_map[x + page * LCD_WIDTH]);
  }
}
*/