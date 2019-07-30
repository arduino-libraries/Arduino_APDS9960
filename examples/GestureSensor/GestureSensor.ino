
#include <Arduino_APDS9960.h>

#define APDS9960_INT_PIN 26 // Needs to be an interrupt pin

APDS9960 apds(Wire1);
volatile bool apdsNeedsAttention = false;

void setup() {
  Serial.begin(9600);
  pinMode(APDS9960_INT_PIN, INPUT);
  attachInterrupt(APDS9960_INT_PIN, apdsInterruptRoutine, FALLING);

  while (!Serial) {}
  if (!apds.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  } else {
    Serial.println("Initialized OK!");
  }
  if (apds.startGestureSensor()) {
    Serial.println("Gesture sensor is now running");
  } else {
    Serial.println("Something went wrong during gesture sensor init!");
  }
  apds.dump();
}

void apdsInterruptRoutine() {
  apdsNeedsAttention = true;
}

void loop() {
  if (apdsNeedsAttention) {
    apdsNeedsAttention = false;
    apds.handleGesture();
  }
}
