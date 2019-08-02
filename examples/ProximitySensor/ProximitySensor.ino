#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);

  while (!Serial) {}
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  } else {
    Serial.println("Initialized OK!");
  }
}

void loop() {
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    int proximity = APDS.readProximity(); // 0 => close, 255 => far, -1 => error

    Serial.println(proximity);
  }

  // wait a bit before reading again
  delay(100);
}
