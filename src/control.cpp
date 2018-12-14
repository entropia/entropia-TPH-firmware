#include "Arduino.h"
#include <RCSwitch.h>

#include "control.hpp"

//Personal note: If you know any better solution than this horrible ifdef-mess: please let me know!

//Option-specific variable block
#ifdef USE_CONTROL
  Adafruit_MQTT_Subscribe control(&mqtt, MQTT_TOPIC_CONTROL);
  Adafruit_MQTT_Publish   response(&mqtt, MQTT_TOPIC_RESPONSE);
#endif

#ifdef USE_COMMON
  Adafruit_MQTT_Subscribe commonControl(&mqtt, MQTT_COMMON_CONTROL);
  Adafruit_MQTT_Publish   commonResponse(&mqtt, MQTT_COMMON_RESPONSE);
#endif


//(Optional)Leinwand-Control
#ifdef USE_LEINWAND
  #define USE_CONTROL
  void initLeinwand() {
    pinMode(DOWN_PIN, OUTPUT);
    pinMode(STOP_PIN, OUTPUT);
    pinMode(UP_PIN, OUTPUT);
  }

  //Send a short pulse
  void pulseLeinwand(byte pin){
    digitalWrite(pin, HIGH);
    delay(PULSE_DURATION);
    digitalWrite(pin, LOW);
  }

  //Handle the leinwand
  void leinwandCallback(char *str, uint16_t len) {
    String command = String(str);

    //Simple "leinwand" functions
    if (command.length() == 1) {
      switch (command.charAt(0)) {
        case 'u':
          pulseLeinwand(UP_PIN);
        break;
        case 's':
          pulseLeinwand(STOP_PIN);
        break;
        case 'd':
          pulseLeinwand(DOWN_PIN);
        break;
      }
    }

    response.publish(command.c_str());
    Serial.println("OK-Response published!");
  }
#else
  void initLeinwand();
  void pulseLeinwand(byte pin);
  void leinwandCallback(char* str, uint16_t len) {}
#endif

//(Optional)433-MHz-Control
#ifdef USE_RC
  #define USE_COMMON

  RCSwitch transceiver = RCSwitch();

  void initRC() {
    transceiver.enableTransmit(RC_PIN);
  }

  //Handle the 433MHz-Sockets
  void rcCallback(char* str, uint16_t len) {
    String command = String(str);

    //REV Ritter
    if (command.length() == 5 || command.length() == 6) {
      char char0 = command.charAt(0);

      //Rev Ritter format
      switch (char0) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        {
          int device = command.charAt(1) - '0';
          String state = command.substring(3);

          if (state.equals("ON")) {
            transceiver.switchOn(char0, device);
          } else if (state.equals("OFF")) {
            transceiver.switchOff(char0, device);
          }
        }break;
      }
    //Brennenstuhl
    } else if(command.length() == 13 || command.length() == 14) {
      const char* group  = command.substring(0, 5).c_str();
      const char* device = command.substring(5, 10).c_str();

      if (command.endsWith("ON")) {
        transceiver.switchOn(group, device);
      } else if(command.endsWith("OFF")) {
        transceiver.switchOff(group, device);
      }
    }

    commonResponse.publish(command.c_str());
    Serial.println("OK-Response published");
  }

#else
  void initRC();
  void rcCallback(char* str, uint16_t len) {}
#endif


void controlCallback(char* str, uint16_t len) {
  leinwandCallback(str, len);
 }

void commonCallback(char* str, uint16_t len) {
  commonCallback(str, len);
 }

void initControl() {
  #ifdef USE_CONTROL
    control.setCallback((SubscribeCallbackBufferType)controlCallback);
    mqtt.subscribe(&control);
  #endif

  #ifdef USE_COMMON
    commonControl.setCallback((SubscribeCallbackBufferType)commonCallback);
    mqtt.subscribe(&commonControl);
  #endif
}
