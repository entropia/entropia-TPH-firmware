/***************************************************************************
  Authors: /madonius (@madonius)
           GityUpNow
  Organisation: Entropia e.V. ~ CCC Karlsruhe
 ***************************************************************************/
#include "WiFi.hpp"
#include "MQTT.hpp"
#include "measure.hpp"
#ifdef USE_OTA
  #include "OTA.hpp"
#endif

//Global Variables
unsigned long last = 0;

void setup() {
  Serial.begin(115200);
  setupWiFi();
  initBME();

  #ifdef USE_OTA
    OTA_init();
  #endif

  delay(400);
}


void loop() {
  mqtt_connect();

  //Measure every X seconds
  if((millis() - last) > MEASURE_DELAY) {
      measureBME();
      last = millis();
  }

  #ifdef USE_OTA
    ArduinoOTA.handle();
  #endif
}
