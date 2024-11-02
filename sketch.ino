#include "DHTesp.h"
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>

const int DHT_PIN = 15;
DHTesp dhtSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  WiFi.begin("Wokwi-GUEST", "",6);
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("Connected");

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AYNI SOLUTIONS...");
  delay(3000);

  Serial.println("Simulación de entorno Wokwi");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){
    TempAndHumidity data = dhtSensor.getTempAndHumidity();

    if (!isnan(data.temperature) && !isnan(data.humidity)) {
      Serial.println("Temp: " + String(data.temperature, 2) + "°C");
      Serial.println("Humidity: " + String(data.humidity, 1) + "%");
      Serial.println("---");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: " + String(data.temperature, 2) + "C");
      lcd.setCursor(0, 1);
      lcd.print("Humedad: " + String(data.humidity, 1) + "%");

      String jsonPayload = "{\"cropId\": 1, \"temperature\":" + String(data.temperature, 2) +
                           ",\"humidity\":" + String(data.humidity, 1) +
                           ",\"oxygen\": 0, \"waterLevel\": 0}";

      delay(30000);

      HTTPClient http;
      http.begin("https://ayni-edge.sfo1.zeabur.app/api/v1/status");
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(jsonPayload);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error en la solicitud POST: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }

    delay(2000);
  }
}
