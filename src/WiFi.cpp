#include "Arduino.h"

#include "WiFi.hpp"
#include "MQTT.hpp"

WiFiClient client;

void setupWiFi() {
  WiFi.mode(WIFI_STA);

  while ( WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect network, SSID: ");
    Serial.println(SSID);
    WiFi.hostname("esp-" MQTT_DEVICE_NAME);
    WiFi.begin(SSID, WIFIPW);

    unsigned long start = millis();
    while(millis() - start < 20000 && WiFi.status() != WL_CONNECTED){
        delay(100);
    }
  }

  Serial.println("\nWifi Conected! \\o/ \n IP Address:");
  Serial.println(WiFi.localIP());
}
