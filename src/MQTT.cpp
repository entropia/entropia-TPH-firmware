#include "MQTT.hpp"
#include "WiFi.hpp"

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVER_PORT, MQTT_USER, MQTT_PASSWORD);

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
