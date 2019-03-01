#include "bool.h"
#include "gpio.h"
#include "timer.h"

#define SCL_GPIO 4
#define SI_GPIO 17
#define A0_GPIO 27
#define RESET_GPIO 22
#define CS_GPIO 5

#define COMMAND_DISPLAY_OFF 0xAE
#define COMMAND_ADC_NORMAL 0xA0
#define COMMAND_OUTPUT_MODE_NORMAL 0xC0
#define COMMAND_SET_BIAS_19 0xA2
// For explanation see:
// http://www.newhavendisplay.com/app_notes/ST7565P.pdf page 31
#define COMMAND_POWER_CIRCUIT_FULL 0x2F
#define COMMAND_RESISTOR_RATIO_6 0x26
// Should be followed with a value as said at page 47
#define COMMAND_ELECTRONIC_VOLUME_SET 0x81
#define COMMAND_COLUMN_ADDRESS_SET_H 0x10
#define COMMAND_COLUMN_ADDRESS_SET_L 0x00
#define COMMAND_DISPLAY_ON 0xAF

char setupLCDGPIO() {
  if (gpio_setup(SCL_GPIO, GPIO_MODE_OUTPUT, GPIO_IN_PULL_NONE) == FALSE) {
    return FALSE;
  }
  if (gpio_setup(SI_GPIO, GPIO_MODE_OUTPUT, GPIO_IN_PULL_NONE) == FALSE) {
    return FALSE;
  }
  if (gpio_setup(A0_GPIO, GPIO_MODE_OUTPUT, GPIO_IN_PULL_NONE) == FALSE) {
    return FALSE;
  }
  if (gpio_setup(RESET_GPIO, GPIO_MODE_OUTPUT, GPIO_IN_PULL_NONE) == FALSE) {
    return FALSE;
  }
  if (gpio_setup(CS_GPIO, GPIO_MODE_OUTPUT, GPIO_IN_PULL_NONE) == FALSE) {
    return FALSE;
  }

  return TRUE;
}

/*
Sub Command
Reset P3.7
Reset P3.4
For Writecount = 1 To 8
 Rotate A , Left , 1
 Reset P3.1
 P1 = A
 Set P3.1
Next Writecount
Set P3.7
*/

void sendCommand(char command) { gpio_output(A0_GPIO, 0); }

void sendData(char data) { gpio_output(A0_GPIO, 1); }

void sendBytes(char bytes) {
  int i;
  for (i = 7; i >= 0; i++) {
    gpio_output(SCL_GPIO, 0);
    wait_us(5);
    char bit = bytes & 0x80;
    bytes = bytes << 1;
    gpio_output(SI_GPIO, bit);
    wait_us(5);
    gpio_output(SCL_GPIO, 1);
  }
}

void lcd_init() {
  gpio_output(CS_GPIO, 0);
  gpio_output(RESET_GPIO, 0);

  wait_ms(500);
  gpio_output(RESET_GPIO, 1);

  sendCommand(COMMAND_DISPLAY_OFF);
  sendCommand(COMMAND_SET_BIAS_19);
  sendCommand(COMMAND_ADC_NORMAL);
  sendCommand(COMMAND_POWER_CIRCUIT_FULL);
  sendCommand(COMMAND_RESISTOR_RATIO_6);
  sendCommand(COMMAND_OUTPUT_MODE_NORMAL);
  sendCommand(COMMAND_DISPLAY_ON);
}