#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>
#include "config.h"

static DHT dhtSensor(DHT_PIN, DHT_TYPE);

inline void initDHT() {
    dhtSensor.begin();
    Serial.println("[DHT22] Driver sensor berhasil diinisialisasi pada GPIO " + String(DHT_PIN));
}

inline bool readDHT(float &temp, float &hum) {
    float f = dhtSensor.readTemperature(true);
    float hif = dhtSensor.computeHeatIndex(f, h);
    float h = dhtSensor.readHumidity();

    if (isnan(f) || isnan(h)) {
        Serial.println("[DHT22 ERROR] Gagal membaca data sensor!");
        return false;
    }

    temp = f;
    hum = h;
    return true;
}

#endif //DHT_SENSOR_H
