// TODO: Copyright?
#ifndef GPIO_H
#define GPIO_H

#define PI_IOBASE_ADDR 0x3F000000

#define GPFSEL0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200000))
#define GPFSEL1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200004))
#define GPFSEL2 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200008))
#define GPFSEL3 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x0020000C))
#define GPFSEL4 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200010))
#define GPFSEL5 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200014))
#define GPSET0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x0020001C))
#define GPSET1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200020))
#define GPCLR0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200028))
#define GPLEV0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200034))
#define GPLEV1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200038))
#define GPEDS0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200040))
#define GPEDS1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200044))
#define GPHEN0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200064))
#define GPHEN1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200068))
#define GPPUD ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200094))
#define GPPUDCLK0 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x00200098))
#define GPPUDCLK1 ((volatile unsigned int*)(PI_IOBASE_ADDR + 0x0020009C))

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT = 1,
  GPIO_MODE_ALTFUNC5 = 2,
  GPIO_MODE_ALTFUNC4 = 3,
  GPIO_MODE_ALTFUNC0 = 4,
  GPIO_MODE_ALTFUNC1 = 5,
  GPIO_MODE_ALTFUNC2 = 6,
  GPIO_MODE_ALTFUNC3 = 7,
  GPIO_MODE_MAX = 7
} gpio_mode_t;

typedef enum {
  GPIO_PULL_NONE = 0,
  GPIO_PULL_DOWN = 1,
  GPIO_PULL_UP = 2,
  GPIO_PULL_MODE_REMAIN = 2,
  GPIO_PULL_MODE_MAX = 2,
} gpio_pull_mode_t;

/** Sets up the general purpose IO pin.
 * @param gpio Index of the gpio pin
 * @param gpio_mode Function of the GPIO pin
 * @param pull_mode Pull resistor state for the pin
 */
void gpio_setup(unsigned int gpio, gpio_mode_t gpio_mode,
                gpio_pull_mode_t pull_mode);

/** Writes to the GPIO
 * @param gpio Index of the gpio pin
 * @param on Zero if pin is to be set to low-state, non-zero for high-state
 */
void gpio_output(unsigned int gpio, char on);

/** Reads from the GPIO
 * @param gpio Index of the gpio pin
 * @return Zero if state of the output is low, non-zero if it's high
 */
char gpio_input(unsigned int gpio);

#endif  // GPIO_H