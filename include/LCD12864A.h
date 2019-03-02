#ifndef LCD16864A_H
#define LCD16864A_H

char setupLCDGPIO();
void lcd_init();
void lcd_on();
void lcd_off();
void lcd_fill(char byte);
void lcd_set_point(unsigned char x, unsigned char y, char on);
void lcd_display();
void lcd_display_area(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void lcd_invert_color(char on);
#endif // LCD16864A_H