#include "OxygenSensor.h"
#include <Arduino.h>

const int OXYGEN_SENSOR_PIN = 32; // Pin conectado al SIG del potenciómetro

void OxygenSensor::setup() {
    pinMode(OXYGEN_SENSOR_PIN, INPUT);
}

float OxygenSensor::read() {
    // Leer el valor analógico del potenciómetro (0-4095 en ESP32)
    int rawValue = analogRead(OXYGEN_SENSOR_PIN);

    // Convertir el valor a un porcentaje (0-100%)
    float oxygenLevel = (rawValue / 4095.0) * 100.0;

    return oxygenLevel;
}
