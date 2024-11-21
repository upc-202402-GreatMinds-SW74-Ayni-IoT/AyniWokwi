#include "RelayModule.h"
#include <Arduino.h>

const int RELAY_PIN = 14;

// Configuración inicial del Relay
void RelayModule::setup() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Inicialmente apagado
}

// Cambiar el estado del Relay
void RelayModule::setState(bool state) {
    digitalWrite(RELAY_PIN, state ? HIGH : LOW);
    if (state) {
        Serial.println("Relay encendido.");
    } else {
        Serial.println("Relay apagado.");
    }
}
