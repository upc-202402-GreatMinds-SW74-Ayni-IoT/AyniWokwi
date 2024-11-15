#include "DistanceSensor.h"
#include <Arduino.h>

const int TRIG_PIN = 13;
const int ECHO_PIN = 12;

// Configuración del sensor ultrasónico
void DistanceSensor::setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

// Lectura de distancia en centímetros
float DistanceSensor::read() {
    // Enviar pulso de 10 microsegundos en el pin TRIG
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Medir el tiempo que tarda el pulso en regresar al pin ECHO
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Convertir el tiempo a distancia en centímetros
    float distance = duration * 0.034 / 2;
    return distance;
}
