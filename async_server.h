#ifndef ASYNC_SERVER_H
#define ASYNC_SERVER_H

#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "config.h"

static AsyncWebServer server(80);

extern float currentTemp;
extern float currentHum;
extern bool wifiConnected;
extern unsigned long bootMillis;

inline bool initLittleFS() {
    if (!LittleFS.begin(true)) {
        Serial.println("[LittleFS ERROR] Gagal mount file system flash!");
        return false;
    }
    Serial.println("[LittleFS] File system flash berhasil dimuat.");
    return true;
}

inline void initAsyncWebServer() {
    //1. layani file statis
    asyncServer.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    
    //2. endpoint rest api
    asyncServer.on("/api/now", HTTP_GET, [](AsyncWebServerRequest *request) {
        JsonDocument doc;
        
        if (isnan(currentTemp) || isnan(currentHum)) {
            doc["temp"] = nullptr;
            doc["hum"] = nullptr;
        } else {
            doc["temp"] = round(currentTemp * 10) / 10.0;
            doc["hum"] = round(currentHum * 10) / 10.0;
        }

        doc["online"] = wifiConnected;
        doc["rssi"] = WiFi.RSSI();
        doc["uptime"] = (millis() - bootMillis) / 1000;
        doc["ip"] = WiFi.localIP().toString();
        doc["ssid"] = WiFi.SSID();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    //3. fallback jika halaman tidak ditemukan
    asyncServer.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "404 Not Found pada ESP32 Async Web Server");
    });

    asyncServer.begin();
    Serial.println("[ASYNC HTTP] Server aktif dan siap melayani request di background.");
}

#endif //ASYNC_SERVER_H
