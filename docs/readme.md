# ArduinoAPDS9960 library

The ArduinoAPDS9960 library allows you to use the [APDS9960](https://docs.broadcom.com/docs/AV02-4191EN) sensor available on the Arduino&reg; Nano 33 BLE Sense to read gestures, color, light intensity and proximity. The gestures readings are based on the detection of the movement of the hand over four photodiodes inside the sensor, while proximity is read by the amount of infrared light reflected by something (anything that reflects IR) back to the sensor. Color is given as a 16-bit value for R, G, B and white components; if the light that hits the sensor is the ambient one and not a reflection on some object, it is possible to calculate the color temperature, otherwise it is possible to detect the color of the object that is reflecting light onto the sensor.

To use this library:

```
#include <Arduino_APDS9960.h>
```
