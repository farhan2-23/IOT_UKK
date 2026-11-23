#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//kredensial WiFi
#define WIFI_SSID "NAMA_WIFI_ANDA"
#define WIFI_PASSWORD "PASSWORD_WIFI_ANDA"

//pinout DHT22
#define DHT_PIN 4
#define DHT_TYPE DHT22

//pinout layar OLED I2C
#define OLDE_SDA 21
#define OLED_SCL 22
#define OLED_I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

//konfigurasi sistem
#define SERIAL_BAUD 115200
#define SENSOR_READ_INTERVAL 2000 //baca sensor setiap 2 detik

#endif //CONFIG_H
