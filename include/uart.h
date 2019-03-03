#ifndef UART_H
#define UART_H

/** Initializes the mini-uUART of the RPI
 */
void uart_init();

/** Sends a single character over UART
 * @param c Character to be sent
 */
void uart_send(unsigned int c);

/** Reads a single character from UART
 * @return Character read
 */
char uart_getc();

/** Sends a string over UART
 * @param s Null terminated string to be sent
 */
void uart_puts(const char *s);

#endif // UART_H