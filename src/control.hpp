#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "MQTT.hpp"

//Optional features. Uncomment to activate
//#define USE_RC
//#define USE_LEINWAND

#ifdef USE_LEINWAND
  #define USE_CONTROL
#endif
#ifdef USE_RC
  #define USE_COMMON
#endif

//RC(433)-Control
#define   RC_PIN 16

void initRC();
void rcCallback(char* str, uint16_t len);


//Leinwand-Control
#define PULSE_DURATION 50
#define DOWN_PIN 13
#define STOP_PIN 12
#define   UP_PIN 14

void initLeinwand();
void pulseLeinwand(byte pin);
void leinwandCallback(char* str, uint16_t len);


void controlCallback();
void commonCallback();
void initControl();

#endif
