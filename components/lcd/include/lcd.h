#ifndef LCD_H
#define LCD_H

// LCD Pin Definitions
#define LCD_PIN_RS    GPIO_NUM_4
#define LCD_PIN_EN    GPIO_NUM_5
#define LCD_PIN_D4    GPIO_NUM_18
#define LCD_PIN_D5    GPIO_NUM_19
#define LCD_PIN_D6    GPIO_NUM_21
#define LCD_PIN_D7    GPIO_NUM_22

// LCD Functions
void lcd_init(void); // Initialize the LCD display in 4-bit mode
void lcd_write_char(char c); // Write a single character to the LCD display
void lcd_display_text(const char* str); // Display a string on the LCD
void lcd_send_command(uint8_t cmd); // Send a command to the LCD

#endif