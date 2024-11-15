#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>
#include "DHTesp.h"

class LCD {
public:
  static void setup();
  static void displayData(const TempAndHumidity& data, float distance);
};

#endif
