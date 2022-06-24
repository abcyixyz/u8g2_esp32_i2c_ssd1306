# Esp32使用u8g2库驱动ssd1306

例程同样适用于ssd1315

参考链接 [github nkolban](https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2)

## 有参考链接了为什么还要单独新建立一个项目

按照参考链接中的教程建立、编译、下载，重启后程序运行到`main\u8g2_esp32_hal.c`文件中的`ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));`函数会出现错误。
```sh
I (320) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (330) ssd1306: u8g2_InitDisplay
I (330) u8g2_hal: sda_io_num 5
I (340) u8g2_hal: scl_io_num 18
I (340) u8g2_hal: clk_speed 1000000
I (350) u8g2_hal: i2c_param_config 1
E (350) i2c: i2c_param_config(662): i2c clock choice is invalid, please check flag and frequency
E (360) err: esp_err_t = 258

assert failed: u8g2_esp32_i2c_byte_cb u8g2_esp32_hal.c:140 (0 && "i2c_param_config(I2C_MASTER_NUM, &conf)")
Setting breakpoint at 0x40081929 and returning...
```

在做出以下修改后可以正常运行，但我并没有看出和源程序有何差别。
```c
/*
i2c_config_t conf;
conf.mode = I2C_MODE_MASTER;
ESP_LOGI(TAG, "sda_io_num %d", u8g2_esp32_hal.sda);
conf.sda_io_num = u8g2_esp32_hal.sda;
conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
ESP_LOGI(TAG, "scl_io_num %d", u8g2_esp32_hal.scl);
conf.scl_io_num = u8g2_esp32_hal.scl;
conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
ESP_LOGI(TAG, "clk_speed %d", I2C_MASTER_FREQ_HZ);
conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
ESP_LOGI(TAG, "i2c_param_config %d", conf.mode);
*/
i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = u8g2_esp32_hal.sda,
    .scl_io_num = u8g2_esp32_hal.scl,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,
};			
ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
```

## End
