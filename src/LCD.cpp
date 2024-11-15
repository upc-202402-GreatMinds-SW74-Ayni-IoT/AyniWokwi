#include "LCD.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configuración inicial de la pantalla LCD
void LCD::setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AYNI SOLUTIONS...");
  delay(3000);
}

// Mostrar datos en la pantalla LCD
void LCD::displayData(const TempAndHumidity& data, float distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(data.humidity, 1) + "% Dist: " + String(distance, 1) + "cm");
}
