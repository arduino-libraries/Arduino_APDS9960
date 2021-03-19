/*
  APDS9960 - Proximity Sensor, Interrupt

  This example reads proximity data from the on-board APDS9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor then if
  the measure its outside the interrupt thresholds it will trigger an interrupt.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

int interrupt_pin = 2;    // pin connected to the Interrupt pin from the sensor

// Thresholds to trigger the interrupt
unsigned int lower_threshold = 0;
unsigned int higher_threshold = 150;

// Flag to know if the interrupt has been triggered
int interrupt_flag = 0;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  // Attach interrupt
  attachInterrupt(interrupt_pin, assert_flag, FALLING);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }

  //Enable the proximity Interrupt generation on the Interrupt pin
  APDS.enableProximityInterrupt();
  // Config the Thresholds
  APDS.setProximityLowThreshold(lower_threshold);
  APDS.setProximityHighThreshold(higher_threshold);
}

void loop() {
  // Output the proximity
  if (APDS.proximityAvailable()) {
    Serial.println(APDS.readProximity());
  }

  // If the interrupt flag has been asserted, clear the interrupt of the sensor
  if ( interrupt_flag == 1 ) {
    Serial.println("Flagged!");

    delay(1000);

    interrupt_flag = 0;
    APDS.clearProximityInterrupt();
    Serial.println("Flag and interrupt clear");
    delay(500);
  }

  delay(100);
}

void assert_flag() {
  interrupt_flag = 1;
}