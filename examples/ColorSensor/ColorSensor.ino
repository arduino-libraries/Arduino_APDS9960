#include <Arduino_APDS9960.h>

APDS9960 apds(Wire1);

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
  // check if a color reading is available
  if (apds.colorAvailable()) {
    int r, g, b;

    // read the color
    apds.readColor(r, g, b);

    // print the values
    Serial.print("r = ");
    Serial.println(r);
    Serial.print("g = ");
    Serial.println(g);
    Serial.print("b = ");
    Serial.println(b);
    Serial.println();
  }

  // wait a bit before reading again
  delay(1000);
}
