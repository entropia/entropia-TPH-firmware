# A Sensor reading the values from an BME280 and publishing them to a MQTT-Server

## Geting started
We would recommend using [platformio](https://platformio.org)

After installation, compiling the binary is as simple as `platformio run` in the
top directory.

Connect the ESP, reset it into flash mode and flash with  `platformio run -t upload`

### Credentials

Two files are required:
* src/MQTT_credentials.hpp
* src/WiFi_credentials.hpp

Move them from their respective .default-file and adjust them to your config

#### Optional

If you want to use OTA, following files are required:
* src/OTA_credentials.hpp

Move them from their respective .default-file and adjust them to your config
You also have to include the following line in your main.cpp: <br>
```#include "OTA_credentials.hpp"```
