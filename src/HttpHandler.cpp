#include "HTTPHandler.h"
#include <HTTPClient.h>

// Crear JSON con los datos
String createJSONPayload(float temperature, float humidity, float distance) {
    return "{\"cropId\": 1, \"temperature\":" + String(temperature, 2) + ",\"humidity\":" + String(humidity, 1) + ",\"oxygen\": 0, \"waterLevel\":" + String(distance, 1) + "}";
}

// Enviar datos al servidor
void sendData(const String& jsonPayload) {
  Serial.println("Enviando datos al servidor");
    HTTPClient http;
    http.begin("https://ayni-edge.sfo1.zeabur.app/api/v1/status/1");
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT(jsonPayload);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.print("Error en la solicitud PUT: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
