#include "WiFiHandler.h"
#include <WiFi.h>

// Conexión a WiFi
void connectWiFi(const char* ssid, const char* password, int channel) {
    WiFi.begin(ssid, password, channel);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}
