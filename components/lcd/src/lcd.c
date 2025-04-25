#include "lcd.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

static lcd_config_t lcd_conf;

static void lcd_pulse_enable() {
    gpio_set_level(lcd_conf.en_pin, 1);
    esp_rom_delay_us(1);  
    gpio_set_level(lcd_conf.en_pin, 0);
    esp_rom_delay_us(100);
}

static void lcd_send_nibble(uint8_t nibble) {
    for (int i = 0; i < 4; i++) {
        gpio_set_level(lcd_conf.data_pins[i], (nibble >> i) & 0x01);
    }
    lcd_pulse_enable();
}


static void lcd_send_byte(uint8_t byte, int is_data) {
    gpio_set_level(lcd_conf.rs_pin, is_data);
    lcd_send_nibble(byte >> 4);   // high nibble
    lcd_send_nibble(byte & 0x0F); // low nibble
    vTaskDelay(pdMS_TO_TICKS(2)); // delay for LCD to process
}

static void lcd_cmd(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
}

void lcd_init(lcd_config_t* config) {
    lcd_conf = *config;

    gpio_set_direction(lcd_conf.rs_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcd_conf.en_pin, GPIO_MODE_OUTPUT);
    for (int i = 0; i < 4; i++) {
        gpio_set_direction(lcd_conf.data_pins[i], GPIO_MODE_OUTPUT);
    }

    vTaskDelay(pdMS_TO_TICKS(50));
    lcd_send_nibble(0x03); vTaskDelay(pdMS_TO_TICKS(5));
    lcd_send_nibble(0x03); vTaskDelay(pdMS_TO_TICKS(1));
    lcd_send_nibble(0x03); vTaskDelay(pdMS_TO_TICKS(1));
    lcd_send_nibble(0x02); // Set 4-bit mode
    vTaskDelay(pdMS_TO_TICKS(50));

    lcd_cmd(0x28); // 4-bit, 2 line, 5x8 dots
    lcd_cmd(0x0C); // Display ON, Cursor OFF
    lcd_cmd(0x06); // Entry mode
    lcd_cmd(0x01); // Clear display
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_clear() {
    lcd_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_set_cursor(int row, int col) {
    int row_offsets[] = {0x00, 0x40};
    lcd_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_write_char(char c) {
    lcd_send_byte(c, 1);
}

void lcd_display(const char* text) {
    lcd_clear();
    lcd_set_cursor(0, 0);
    while (*text) {
        lcd_write_char(*text++);
    }
}

void lcd_scroll(const char* text, int speed_ms) {
    char buffer[17];
    int len = strlen(text);
    for (int i = 0; i <= len - 16; i++) {
        strncpy(buffer, text + i, 16);
        buffer[16] = '\0';
        lcd_display(buffer);
        vTaskDelay(pdMS_TO_TICKS(speed_ms));
    }
}     