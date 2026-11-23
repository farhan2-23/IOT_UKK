#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static bool oledAvailable = false;

inline bool initOLED() {
    Wire.begin(OLDE_SDA, OLED_SCL);
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println("[OLED ERROR] Gagal initialisasi SSD1306!");
        oledAvailable = false;
        return false;
}
oledAvailable = true;
oled.clearDisplay();
oled.setTextColor(SSD1306_WHITE);
return true;
}

inline void showConnectingWIFI(const char* ssid) {
    if (!oledAvailable) return;
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 10);
    oled.println("Menghubungkan ke WiFi...");
    oled.println("--------------------------");
    oled.print("SSID: ");
    oled.println(ssid);
    oled.display();
}

inline void drawDashboardOled(float temp, float hum, bool isOnline, const String& ipStr) {
    if (!oledAvailable) return;
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.println("DASHBOARD IOT");
    oled.println("--------------------------");
    oled.print("Suhu: ");
    oled.print(temp, 1);
    oled.println(" °F");
    oled.print("Hum: ");
    oled.print(hum, 1);
    oled.println(" %");
    oled.println("--------------------------");
    oled.print("Status: ");
    oled.println(isOnline ? "ONLINE" : "OFFLINE");
    oled.print("IP: ");
    oled.println(ipStr);
    oled.display();
}
