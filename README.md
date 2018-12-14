# A Sensor reading the values from an BME280 and publishing them to a MQTT-Server

## Geting started
We would recommend using [platformio](https://platformio.org)

Clone the project, configure the credentials and choose the wanted features.

Compiling the binary is as simple as `platformio run` in the top directory.

Afterwards: Connect to the ESP via UART, reset it into flash mode and flash with  `platformio run -t upload`

## Credentials

Two files have to be edited:
* src/MQTT.hpp
* src/WiFihpp

Please adjust the default configuration in them to match your setup.

## Optional features
#### OTA

For using the OTA-Feature the following steps are required:
1. Open the OTA.hpp
1. Uncomment the 'USE_OTA' define
1. Enter your OTA-Username
1. Enter your OTA-Password

(Note: It is also required to include the OTA-Password and optionally the OTA-Hostname/IP in the platformio.ini to use OTA)
#### 433-MHz Sockets
For controlling 433-MHz-Sockets with the ESP the following steps are required:
1. Open the control.hpp
1. Uncomment the 'USE_RC' define

The pin for the 433-Transceiver is defined as 'RC_PIN' in the control.hpp

#### Leinwand-Control
For using the ESP as the leinwand-controller the following steps are required:
1. Open the control.hpp
1. Uncomment the 'USE_LEINWAND' define

The pins for the leinwand are defined as 'DOWN_PIN', 'UP_PIN' and 'STOP_PIN' in the control.hpp

