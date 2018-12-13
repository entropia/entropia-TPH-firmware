/***************************************************************************
  Authors: /madonius (@madonius)
           GityUpNow
  Organisation: Entropia e.V. ~ CCC Karlsruhe
 ***************************************************************************/
#include "WiFi.hpp"
#include "MQTT.hpp"
#include "measure.hpp"
#include "control.hpp"
#include "OTA.hpp"

//Global Variables
unsigned long last = 0;

void setup() {
  Serial.begin(115200);
  setupWiFi();
  initBME();

  //Optional features. Consult the OTA.hpp and control.hpp
  initControl();
  initOTA();

  delay(400);
}


void loop() {
  mqtt_connect();

  //Measure every X seconds
  if((millis() - last) > MEASURE_DELAY) {
      measureBME();
      last = millis();
  }

  mqtt.processPackets(MQTT_PROCESS_TIME);

  #ifdef USE_OTA
    ArduinoOTA.handle();
  #endif
}
