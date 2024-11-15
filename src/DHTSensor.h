#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include "DHTesp.h"

class DHTSensor {
public:
  static void setup();
  static TempAndHumidity read();
};

#endif
