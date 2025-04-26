#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Define LCD control pins
#define LCD_PIN_RS    GPIO_NUM_4
#define LCD_PIN_EN    GPIO_NUM_5
#define LCD_PIN_D4    GPIO_NUM_18
#define LCD_PIN_D5    GPIO_NUM_19
#define LCD_PIN_D6    GPIO_NUM_21
#define LCD_PIN_D7    GPIO_NUM_22

// Short delay function (using FreeRTOS vTaskDelay)
void lcd_delay_ms(int ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));  // Convert milliseconds to FreeRTOS ticks
}

// Send a 4-bit nibble to LCD
void lcd_send_nibble(uint8_t nibble) {
    gpio_set_level(LCD_PIN_D4, (nibble >> 0) & 0x01);
    gpio_set_level(LCD_PIN_D5, (nibble >> 1) & 0x01);
    gpio_set_level(LCD_PIN_D6, (nibble >> 2) & 0x01);
    gpio_set_level(LCD_PIN_D7, (nibble >> 3) & 0x01);

    // Pulse EN pin to send data
    gpio_set_level(LCD_PIN_EN, 1);  // Set EN high
    lcd_delay_ms(1);  // Wait for a short time
    gpio_set_level(LCD_PIN_EN, 0);  // Set EN low
    lcd_delay_ms(1);  // Wait for a short time
}

// Send a full byte (2 nibbles) to LCD
void lcd_send_byte(uint8_t byte, bool is_data) {
    gpio_set_level(LCD_PIN_RS, is_data);  // Set RS to data or command

    lcd_send_nibble(byte >> 4);  // Send the high nibble
    lcd_send_nibble(byte & 0x0F);  // Send the low nibble

    lcd_delay_ms(10);  // Wait for the LCD to process
}

// Initialize LCD
void lcd_init() {
    // Set GPIO pins as output
    gpio_set_direction(LCD_PIN_RS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_EN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D7, GPIO_MODE_OUTPUT);

    lcd_delay_ms(20);  // Wait for power to stabilize

    // LCD initialization sequence
    lcd_send_nibble(0x03);  // Function set
    lcd_delay_ms(10);
    lcd_send_nibble(0x03);  // Function set
    lcd_delay_ms(10);
    lcd_send_nibble(0x03);  // Function set
    lcd_delay_ms(10);
    lcd_send_nibble(0x02);  // Set 4-bit mode
    lcd_send_byte(0x28, false); // Set 4-bit mode, 2-line display, 5x8 dots 
    lcd_send_byte(0x0C, false); // Display on, cursor off, blink off 
    lcd_send_byte(0x01, false); // Clear display 
    lcd_delay_ms(10);
    lcd_send_byte(0x06, false); // Entry mode set
}

// Write a single character to LCD
void lcd_write_char(char c) {
    lcd_send_byte(c, true);
}

// Display a full string on the LCD screen
void lcd_display_text(const char* str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

// Send a command instruction to the LCD
void lcd_send_command(uint8_t cmd) {
    lcd_send_byte(cmd, false);
}