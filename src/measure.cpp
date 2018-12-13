#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "MQTT.hpp"
#include "measure.hpp"

Adafruit_BME280 bme;

bool initBME() {
  if(!bme.begin(BME_ADRESS)) {
    Serial.println(F("Could not find a BME280 Sensor!"));

    return false;
  }

  return true;
}

void measureBME() {
  float T = bme.readTemperature();
  delay(BME_DELAY);

  float P = bme.readPressure();
  delay(BME_DELAY);

  float H = bme.readHumidity();
  delay(BME_DELAY);


  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/T");
  Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/P");
  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/H");

  temperature.publish(T);
  pressure.publish(P);
  humidity.publish(H);
}
