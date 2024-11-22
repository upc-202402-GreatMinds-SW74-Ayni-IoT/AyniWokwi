#include "DHTSensor.h"

const int DHT_PIN = 15;
DHTesp dhtSensor;

void DHTSensor::setup() {
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

TempAndHumidity DHTSensor::read() {
  return dhtSensor.getTempAndHumidity();
}
