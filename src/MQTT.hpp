#ifndef MQTT_HPP
#define MQTT_HPP

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define MQTT_PROCESS_TIME 10

//Server-Settings
#define MQTT_SERVER          "mqtt.club.entropia.de"
#define MQTT_SERVER_PORT     1883
#define MQTT_PREFIX          "/public/sensoren/TPH/"

//Device/Access-Settings
#define MQTT_DEVICE_NAME     "foo"
#define MQTT_USER            "eve"
#define MQTT_PASSWORD        "entropia"

//Not required by default
//Concatination
#define MQTT_TOPIC           MQTT_PREFIX MQTT_DEVICE_NAME
#define MQTT_CONTROL_TOPIC   MQTT_TOPIC "/control"
#define MQTT_RESPONSE_TOPIC  MQTT_TOPIC "/response"

#define MQTT_COMMON_TOPIC    MQTT_PREFIX "common"
#define MQTT_COMMON_CONTROL  MQTT_COMMON_TOPIC "/control"
#define MQTT_COMMON_RESPONSE MQTT_COMMON_TOPIC "/response"

extern Adafruit_MQTT_Client mqtt;


void mqtt_connect();

#endif
