#include <stdio.h>
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"  

void app_main() {

    // Initialize the LCD with configuration
    lcd_config_t config = {
        .rs_pin = GPIO_NUM_21,
        .en_pin = GPIO_NUM_22,
        .data_pins = {GPIO_NUM_19, GPIO_NUM_18, GPIO_NUM_17, GPIO_NUM_16}, 
        .is_4bit_mode = 1
    };

    lcd_init(&config);
    vTaskDelay(pdMS_TO_TICKS(100));

    // Display a message
    lcd_display("Melvin Joshua R");

}
