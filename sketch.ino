#include "DHTesp.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int DHT_PIN = 15;

DHTesp dhtSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AYNI SOLUTIONS...");
  delay(2000);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad: " + String(data.humidity, 1) + "%");

  delay(2000);
}
