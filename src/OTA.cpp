/*
 This file is based on the BasicOTA-Sketch from the esp8266-Arduino-Project
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"

#include "OTA.hpp"

#ifdef USE_OTA
  void initOTA(){
      //OTA-Credentials
      ArduinoOTA.setHostname(OTA_USERNAME);
      ArduinoOTA.setPassword(OTA_PASSWORD);

      //Update
      ArduinoOTA.onStart([]() {
              Serial.println("Start");
          });

          ArduinoOTA.onEnd([]() {
              Serial.println("\nEnd");
          });

          ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
              Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
          });

          ArduinoOTA.onError([](ota_error_t error) {
              Serial.printf("Error[%u]: ", error);
              if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed" + String(OTA_PASSWORD));
              else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
              else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
              else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
              else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });

      ArduinoOTA.begin();
  }
#else
  void initOTA() {}
#endif
