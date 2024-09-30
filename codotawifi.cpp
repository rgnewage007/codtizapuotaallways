#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>



void setup() {
  Serial.begin(115200);
 
    WiFiManager wifiManager;
    wifiManager.autoConnect("IOTdoor");
    delay(500);
 
  
  // Inicializar OTA
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    // Nota: si estás actualizando el sistema de archivos, `ESP.restart()` es obligatorio.
    Serial.println("Inicio de actualización: " + type);
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nFin de actualización");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error [%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Error de autenticación");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Error al comenzar");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Error de conexión");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Error al recibir");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Error al finalizar");
    }
  }); 
   ArduinoOTA.setPassword((const char *)"1234");
  ArduinoOTA.begin();

  Serial.println("OTA listo");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); 
  
  pinMode(LED_BUILTIN, OUTPUT);
}

 

// the loop function runs over and over again forever
void loop() {
  ArduinoOTA.handle();

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
