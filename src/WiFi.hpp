#ifndef WIFI_HPP
#define WIFI_HPP

#include <ESP8266WiFi.h>

#define SSID   "entropolis"
#define WIFIPW "Iliketr41nz!"


extern WiFiClient client;

void setupWiFi();

#endif
