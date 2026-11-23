#include "config.h"
#include "dht_sensor.h"
#include "oled_display.h"
#include "wifi_manager.h"
#include "async_server.h"

float currentTemp = 0.0;
float currentHum = 0.0;
unsigned long bootMillis = 0;
static unsigned long lastSensorMillis = 0;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  bootMillis = millis();

  Serial.println();
  Serial.println("====================================");
  Serial.println("   PROYEK 4: DHT22 ASYNC WEB DASHBOARD");
  Serial.println("====================================");

  //1. inisialisasi OLED
  initOLED();
  showConnectingWIFI(WIFI_SSID);

  //2. inisialisasi sensor DHT22
  initDHT();

  //3. mount file system LittleFS
  initLittleFS();

  //4. koneksi ke WiFi
  bool connected = connectToWiFi();

  //5. inisialisasi Asynchronus Web Server
  if (connected) {
    initAsyncWebServer();
  }

  //6. baca data awal
  readDHT(currentTemp, currentHum);
  drawDashboard(currentTemp, currentHum, connected, localIPAddress);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSensorMillis >= SENSOR_READ_INTERVAL) {
    lastSensorMillis = now;

    if (readDHT(currentTemp, currentHum)) {
      Serial.print("[ASYNC NODE] Suhu:");
      Serial.print(currentTemp,1);
      Serial.print("°F | Hum:");
      Serial.print(currentHum,1);
      Serial.println("%");
      
      drawDashboard(currentTemp, currentHum, wifiConnected, localIPAddress);
    }
  }
}
