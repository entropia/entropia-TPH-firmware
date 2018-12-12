/***************************************************************************
  Authors: /madonius (@madonius)
           GityUpNow
  Organisation: Entropia e.V. ~ CCC Karlsruhe
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include "WiFi_credentials.hpp"
#include "MQTT_credentials.hpp"
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
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVER_PORT, MQTT_USER, MQTT_PASSWORD);

//Functions prototypes
void setupWiFi();
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
void setupWiFi() {
  WiFi.mode(WIFI_STA);

  while ( WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect network, SSID: ");
    Serial.println(SSID);
    WiFi.begin(SSID, WIFIPW);

    unsigned long start = millis();
    while(millis() - start < 20000 && WiFi.status() != WL_CONNECTED){
        delay(100);
    }
  }

  Serial.println("\nWifi Conected! \\o/ \n IP Address:");
  Serial.println(WiFi.localIP());
}


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

void mqtt_connect() {
  // Stop if already connected.
  if(mqtt.connected()){
    return;
  }

  Serial.print(F("Connecting to MQTT... "));

  int8_t ret;
  uint8_t retries = 3;
  while((ret = mqtt.connect()) != 0){ // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(F("Retrying MQTT connection in 5 seconds..."));

       mqtt.disconnect();
       delay(5000);  // wait 5 seconds

       retries--;
       if(retries == 0){
         while (1); // basically die and wait for WDT to reset me
       }
  }
  Serial.println(F("MQTT Connected!"));
}

void mqtt_publish(float *bmeData) {
  Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/T");
  temperature.publish(bmeData[0]);

  Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/P");
  pressure.publish(bmeData[1]);

  Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC "/H");
  humidity.publish(bmeData[2]);
}
