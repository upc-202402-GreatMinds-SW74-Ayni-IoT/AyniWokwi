#include "DHTSensor.h"

const int DHT_PIN = 15;
DHTesp dhtSensor;

// Configuración del sensor DHT
void DHTSensor::setup() {
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

// Lectura de datos del sensor DHT
TempAndHumidity DHTSensor::read() {
  return dhtSensor.getTempAndHumidity();
}
