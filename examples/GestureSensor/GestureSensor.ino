
#include <Arduino_APDS9960.h>

#define APDS9960_INT_PIN 26 // Needs to be an interrupt pin

APDS9960 apds(Wire1, APDS9960_INT_PIN);

void setup() {
  Serial.begin(9600);

  while (!Serial) {}
  if (!apds.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  } else {
    Serial.println("Initialized OK!");
  }
}
void loop() {
  if (apds.gestureAvailable()) {
    Serial.println(apds.readGesture());
  }
}
