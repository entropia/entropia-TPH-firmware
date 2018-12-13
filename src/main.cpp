/***************************************************************************
  Authors: /madonius (@madonius)
           GityUpNow
  Organisation: Entropia e.V. ~ CCC Karlsruhe
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "WiFi.hpp"
#include "MQTT.hpp"
#ifdef USE_OTA
  #include "OTA.hpp"
#endif

//Global Constants
#define MEASURE 15000

//Global Variables
unsigned long last = 0;
float bmeData[3];

//Object declarations
Adafruit_BME280 bme;

//Functions prototypes
void readBME(float *bmeData);
void mqtt_connect();
void mqtt_publish(float *bmeData);

void setup() {
  Serial.begin(115200);
  setupWiFi();
  #ifdef USE_OTA
    OTA_init();
  #endif

  if(!bme.begin(0x76))
    Serial.println(F("Could not find a BME280 Sensor!"));

  delay(400);
}


void loop() {
    mqtt_connect();

    //Measure every X seconds
    if((millis() - last) > MEASURE) {
        readBME(bmeData);
        mqtt_publish(bmeData);

        last = millis();
    }

    #ifdef USE_OTA
      ArduinoOTA.handle();
    #endif
}


//Function definitions
void readBME(float* bmeData) {
  float T = bme.readTemperature();
  delay(50);

  float P = bme.readPressure();
  delay(50);

  float H = bme.readHumidity();
  delay(50);

  bmeData[0] = T;
  bmeData[1] = P;
  bmeData[2] = H;
}

void mqtt_publish(float *bmeData) {
  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/T");
  temperature.publish(bmeData[0]);

  Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/P");
  pressure.publish(bmeData[1]);

  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/H");
  humidity.publish(bmeData[2]);
}
