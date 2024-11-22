#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <Arduino.h>

String createJSONPayload(float temperature, float humidity, float distance, float oxygenLevel);
void sendData(const String& jsonPayload);

#endif
