// lcd.h
#pragma once

#include "driver/gpio.h"

typedef struct {
    gpio_num_t rs_pin;
    gpio_num_t en_pin;
    gpio_num_t data_pins[4];  
    int is_4bit_mode;
} lcd_config_t;

void lcd_init(lcd_config_t* config);
void lcd_clear();
void lcd_display(const char* text);
void lcd_scroll(const char* text, int speed_ms);

// Optional
void lcd_set_cursor(int row, int col);
void lcd_write_char(char c);
