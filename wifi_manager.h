#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "config.h"

static bool wifiConnected = false;
static String localIPAddress = "0.0.0.0";

inline bool connectToWiFi() {
  Serial.println();
  Serial.println("[WiFi] Menghubingkan ke: ");
  Serial.println(WiFi_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    localIPAddress = WiFi.localIP().toString();
    Serial.println("[WiFi] Berhasil terhubung!");
    Serial.print("[WiFi] Alamat Dashboard: http://");
    Serial.println(localIPAddress);
    return true;
  } else {
    wifiConnected = false;
    Serial.println("[WiFi ERROR] Gagal terhubung ke WiFi!");
    return false;
  }
}

inline bool checkWiFiStatus() {
  wifiConnected = (WiFi.status() == WL_CONNECTED);
  if (wifiConnected) localIPAddress = WiFi.localIP().toString();
  return wifiConnected;
}

#endif //WIFI_MANAGER_H
