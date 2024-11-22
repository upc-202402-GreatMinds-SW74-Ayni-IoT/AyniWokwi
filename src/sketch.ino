#include "DHTSensor.h"
#include "DistanceSensor.h"
#include "WiFiHandler.h"
#include "HttpHandler.h"
#include "LCD.h"
#include "OxygenSensor.h"
#include "RelayModule.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

struct RecommendedLimits {
    float recommendedTemperature;
    float recommendedHumidity;
	float recommendedOxygen;
    float recommendedWaterlevel;
};

RecommendedLimits recommendedLimits;

void fetchRecommendedLimits() {
    HTTPClient http;
    http.begin("https://ayni-edge.sfo1.zeabur.app/api/v1/limitations/by-id/1");

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println("Datos obtenidos del endpoint:");
        Serial.println(payload);

        DynamicJsonDocument doc(256);
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
            recommendedLimits.recommendedTemperature = doc["recommendedTemperature"];
            recommendedLimits.recommendedHumidity = doc["recommendedHumidity"];
            recommendedLimits.recommendedOxygen = doc["recommendedOxygen"];
            recommendedLimits.recommendedWaterlevel = doc["recommendedWaterlevel"];
        } else {
            Serial.println("Error al parsear el JSON.");
        }
    } else {
        Serial.print("Error al realizar la solicitud GET: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void controlActuators(float currentTemperature, float currentHumidity, float currentWaterLevel, float currentOxygen) {
    bool activateRelay = false;

    if (currentTemperature > recommendedLimits.recommendedTemperature) {
        Serial.println("La temperatura está por encima del límite recomendado. Encendiendo el actuador.");
        activateRelay = true;
    }

    if (currentHumidity < recommendedLimits.recommendedHumidity) {
        Serial.println("La humedad está por debajo del límite recomendado. Encendiendo el actuador.");
        activateRelay = true;
    }

    if (currentWaterLevel < recommendedLimits.recommendedWaterlevel) {
        Serial.println("El nivel de agua está por debajo del límite recomendado. Encendiendo el actuador.");
        activateRelay = true;
    }

    if(currentOxygen < recommendedLimits.recommendedOxygen) {
        Serial.println("El nivel de oxígeno está por debajo del límite recomendado. Encendiendo el actuador.");
        activateRelay = true;
    }

    RelayModule::setState(activateRelay);
}

void setup() {
    Serial.begin(115200);

    connectWiFi("Wokwi-GUEST", "", 6);
    DHTSensor::setup();
    DistanceSensor::setup();
    OxygenSensor::setup();
    LCD::setup();
    RelayModule::setup();

    fetchRecommendedLimits();
}

void loop() {
    TempAndHumidity data = DHTSensor::read();
    float distance = DistanceSensor::read();
    float oxygenLevel = OxygenSensor::read();

    if (!isnan(data.temperature) && !isnan(data.humidity)) {
        LCD::displayData(data, distance, oxygenLevel);
        controlActuators(data.temperature, data.humidity, distance, oxygenLevel);

        Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
        Serial.println("Humedad: " + String(data.humidity, 1) + "%");
        Serial.println("Distancia: " + String(distance, 2) + "cm");
        Serial.println("Nivel de oxígeno: " + String(OxygenSensor::read()) + "L");

        String jsonPayload = createJSONPayload(data.temperature, data.humidity, distance, oxygenLevel);
        sendData(jsonPayload);
    } else {
        Serial.println("Error al leer los datos del sensor DHT.");
    }

    delay(5000);
}
