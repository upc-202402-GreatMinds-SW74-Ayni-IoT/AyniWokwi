#include "DHTSensor.h"
#include "WiFiHandler.h"
#include "LCD.h"
#include "HTTPHandler.h"
#include "DistanceSensor.h"
#include <WiFi.h>

void setup() {
    Serial.begin(115200);

    // Configuración WiFi
    connectWiFi("Wokwi-GUEST", "", 6);

    // Configuración del sensor DHT
    DHTSensor::setup();

    // Configuración del sensor ultrasónico
    DistanceSensor::setup();

    // Configuración de la pantalla LCD
    LCD::setup();

    Serial.println("Sistema inicializado");
}

void loop() {
  Serial.println("Iniciando loop");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conexión establecida");
        TempAndHumidity data = DHTSensor::read();
        float distance = DistanceSensor::read();

        Serial.println("Datos leídos");
        Serial.println(data.temperature);
        Serial.println(data.humidity);
        Serial.println(distance);

        if (!isnan(data.temperature) && !isnan(data.humidity)) {
            // Mostrar datos en la pantalla LCD
            LCD::displayData(data, distance);

            // Crear el JSON y enviar datos
            String jsonPayload = createJSONPayload(data.temperature, data.humidity, distance);
            sendData(jsonPayload);
        } else {
            Serial.println("Error al leer los datos");
        }

        delay(5000);
    } else {
        Serial.println("Error de conexión WiFi");
    }
}
