/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "test_SSD1306_i2c.h"


extern void task_test_SSD1306i2c(void* ignore);

void app_main(void)
{
    xTaskCreatePinnedToCore(&task_test_SSD1306i2c, "task_test_SSD1306i2c", 8048, NULL, 5, NULL, 0);
}
