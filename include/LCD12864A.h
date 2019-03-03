#ifndef LCD16864A_H
#define LCD16864A_H

/** Initializes the LCD
 */
void lcd_init();

/** Turns the LCD on
 */
void lcd_on();

/** Turns the LCD off
 */
void lcd_off();

/** Fills the pixel buffer with a given pattern.
 * @param byte The pattern to be used for each column in each page. Ex. 0x0 to
 * clear the whole screen or 0xFF to light up the whole screen
 */
void lcd_fill(char byte);

/** Sets a single pixel in the LCD buffer
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @param on State of the pixel. Zero for unlit, non-zero for lit
 */
void lcd_set_point(unsigned char x, unsigned char y, char on);

/** Sends the display buffer to the LCD
 */
void lcd_display();

/** Sends a part of the display buffer to the LCD
 * @param x1 X coordinate of the bottom-left point
 * @param y1 Y coordinate of the bottom-left point
 * @param x2 X coordinate of the top-right point
 * @param y2 Y coordinate of the top-right point
 */
void lcd_display_area(unsigned char x1, unsigned char y1, unsigned char x2,
                      unsigned char y2);

/** Inverts the state of all pixels
 * @param on Zero for normal, non-zero for inverted
 */
void lcd_invert_color(char on);
#endif  // LCD16864A_H