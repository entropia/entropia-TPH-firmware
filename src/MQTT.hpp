#ifndef MQTT_HPP
#define MQTT_HPP

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define MQTT_SERVER      "mqtt.club.entropia.de"
#define MQTT_SERVER_PORT 1883
#define MQTT_TOPIC       "/public/sensoren/TPH/foo"
#define MQTT_USER        "eve"
#define MQTT_PASSWORD    "entropia"

extern Adafruit_MQTT_Client mqtt;


void mqtt_connect();

#endif
