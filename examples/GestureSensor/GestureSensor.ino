
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
    int gesture = apds.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;

      default:
        // ignore
        break;
    }
  }
}
