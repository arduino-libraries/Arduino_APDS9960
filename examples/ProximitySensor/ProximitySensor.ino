/*
  APDS9960 - Proximity Sensor

  This example reads proximity data from the on-board APDS9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor
  every 100ms.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
}

void loop() {
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    int proximity = APDS.readProximity();

    // print value to the Serial Monitor
    Serial.println(proximity);
  }

  // wait a bit before reading again
  delay(100);
}
