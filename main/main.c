#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd.h"

void app_main(void) {
    lcd_init();  // Initialize LCD
    lcd_display_text("Melvin Joshua"); // Display LCD text

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
      lcd_send_command(0x18);  // Set cursor position
    }
}