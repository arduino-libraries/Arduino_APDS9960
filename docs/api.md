# ArduinoAPDS9960 library

## Methods

### `begin()`

Initialize the APDS gesture sensor.

#### Syntax

```
APDS.begin()
```

#### Parameters

None.

#### Returns

1 on success, 0 on failure.

#### Example

```
if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
}
```

#### See also

* [end()](#end)
* [gestureAvailable()](#gestureavailable)
* [readGesture()](#readgesture)
* [colorAvailable()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `end()`

Deactivate the APDS gesture sensor.

#### Syntax 

```
APDS.end()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
APDS.end();
```

#### See also

* [begin()](#begin)
* [gestureAvailable()](#gestureavailable)
* [readGesture()](#readgesture)
* [colorAvailable()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `gestureAvailable()`

Checks if the sensor has detected gestures. The detected gesture can be read using the `APDS.readGesture()` function. This function also enables the gesture sensor when called for the first time.

#### Syntax 

```
APDS.gestureAvailable()
```

#### Parameters

None.

#### Returns

1 if a gesture has been detected, otherwise 0.

#### Example

```
if (APDS.gestureAvailable()) {
    // a gesture was detected
    int gesture = APDS.readGesture();
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [readGesture()](#readgesture)
* [colorAvailable()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `readGesture()`

Read the gesture detected from the sensor. You can check if a gesture has been detected using the `APDS.gestureAvailable()` function.

#### Syntax 

```
APDS.readGesture()
```

#### Parameters

None.

#### Returns

The detected gesture. Can be one of the following values:

* GESTURE_UP: “up” gesture.
* GESTURE_DOWN: “down” gesture.
* GESTURE_LEFT: “left” gesture.
* GESTURE_RIGHT: “right” gesture.
* GESTURE_NONE: the gesture doesn’t match any of the above.

#### Example

```
/*
  APDS-9960 - Gesture Sensor

  This example reads gesture data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense board and prints any detected gestures to the Serial Monitor.

  Gesture directions are as follows:
  - UP:    from USB connector towards antenna.
  - DOWN:  from antenna towards USB connector.
  - LEFT:  from analog pins side towards digital pins side.
  - RIGHT: from digital pins side towards analog pins side.

  The circuit:
  - Arduino Nano 33 BLE Sense. 

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }

  // For setGestureSensitivity(...), a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected by the sensor). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed by the sensor).
  // Default value is 80.

  //APDS.setGestureSensitivity(80);

  Serial.println("Detecting gestures ...");
}

void loop() {
  if (APDS.gestureAvailable()) {
    // A gesture was detected, read and print to Serial Monitor.
    int gesture = APDS.readGesture();

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
        // Ignore.
        break;
    }
  }
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [colorAvailable()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `colorAvailable()`

Check if a color reading is available from the sensor. The color reading can be retrieved using the `APDS.readColor(...)` function.

#### Syntax 

```
APDS.colorAvailable()
```

#### Parameters

None.

#### Returns

1 if a color has been read, otherwise 0.

#### Example

```
// Check if a color reading is available:
if (APDS.colorAvailable()) {
    int r, g, b;
    
    // Read the color:
    APDS.readColor(r, g, b);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `readColor()`

Retrieve the color read from the sensor. You can check if a color has been read by the sensor and may be retrieved using the `APDS.colorAvailable()` function.

#### Syntax 

```
Int r, g, b;
APDS.readColor(r, g, b);
Int a;
APDS.readColor(r, g, b, a);
```

#### Parameters

This function requires 3 or 4 integer variables as arguments where the read color will be stored:

* _r_: the red component of the read color.
* _g_: the green component of the read color.
* _b_: the blue component of the read color.
* _a_. the ambient light intensity. 

#### Returns

None. 

#### Example

```
/*
  APDS-9960 - Color Sensor

  This example reads color data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints the color RGB (red, green, blue) values
  to the Serial Monitor once a second.

  The circuit:
  - Arduino Nano 33 BLE Sense.

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
}

void loop() {
  // Check if a color reading is available.
  while (!APDS.colorAvailable()) {
    delay(5);
  }

  int r, g, b;

  // Read the color.
  APDS.readColor(r, g, b);

  // Print the values:
  Serial.print("r = ");
  Serial.println(r);
  Serial.print("g = ");
  Serial.println(g);
  Serial.print("b = ");
  Serial.println(b);
  Serial.println();

  // Wait a bit before reading again.
  delay(1000);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [colorAvailable()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `colorAvailable()`

Check if a color reading is available from the senor. The color reading can be retrieved using the `APDS.readColor(...)` function. This function also enables the color sensor when called for the first time.

#### Syntax 

```
APDS.colorAvailable()
```

#### Parameters

None.

#### Returns

1 if a color has been read, otherwise 0.

#### Example

```
// Check if a color reading is available.
if (APDS.colorAvailable()) {
    int r, g, b;

    // Read the color.
    APDS.readColor(r, g, b);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `proximityAvailable()`

Check if a proximity reading is available from the senor. The proximity reading can be retrieved using the `APDS.readProximity()` function. This function also enables the proximity sensor when called for the first time.

#### Syntax 

```
APDS.proximityAvailable()
```

#### Parameters

None.

#### Returns

1 if a proximity has been read, otherwise 0

#### Example

```
// Check if a proximity reading is available.
if (APDS.proximityAvailable()) {
    int proximity = APDS.readProximity();
    Serial.println(proximity);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [colorAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `readProximity()`

Retrieve the proximity read from the sensor. You can check if a proximity has been read by the sensor and may be retrieved using the `APDS.proximityAvailable()` function.

#### Syntax 

```
APDS.readProximity()
```

#### Parameters

None.

#### Returns

The detected proximity that may range from 0 to 255 where 0 is the closest and 255 is the farthest. The function returns -1 in case of error.

#### Example

```
/*
  APDS-9960 - Proximity Sensor

  This example reads proximity data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor
  every 100 ms.

  The circuit:
  - Arduino Nano 33 BLE Sense.

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
}

void loop() {
  // Check if a proximity reading is available.
  if (APDS.proximityAvailable()) {
    // Read the proximity where:
    // - 0   => close
    // - 255 => far
    // - -1  => error
    int proximity = APDS.readProximity();

    // Print value to the Serial Monitor.
    Serial.println(proximity);
  }

  // Wait a bit before reading again.
  delay(100);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [colorAvailable()](#proximityavailable)
* [proximityAvailable](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `setGestureSensitivity()`

Sets APDS gesture sensor sensitivity.

#### Syntax 

```
APDS.setGestureSensitivity(sensitivity)
```

#### Parameters

* _sensitivity_: The desired gesture sensitivity a value between 1 and 100 is required. Higher values makes the gesture recognition more sensible but less accurate (a wrong gesture may be detected), lower values makes the gesture recognition more accurate but less sensible (some gestures may be missed). The default sensitivity value is 80.

#### Returns

None.

#### Example

```
APDS.setGestureSensitivity(90);
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [colorAvailable()](#proximityavailable)
* [proximityAvailable](#readproximity)
* [readProximity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `setInterruptPin()`

Sets APDS chip interrupt pin. The library tries to set the correct interrupt pin automatically based on the available board data. This function may be used in case the default pin is not correct or not available. The sensor is read even if the interrupt pin is not set or automatically found; setting the interrupt pin manually, if not automatically found, will increase performance.

#### Syntax 

```
APDS.setInterruptPin(pin)
```

#### Parameters

* _pin_: the board pin where the sensor interrupt pin is connected, or -1 if not connected.

#### Returns

None.

#### Example

```
APDS.setInterruptPin(x);
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#readgesture)
* [readGesture()](#coloravailable)
* [readColor()](#readcolor)
* [colorAvailable()](#proximityavailable)
* [proximityAvailable](#readproximity)
* [readProximity()](#setgesturesensitivity)
* [setGestureSensitivity()](#setinterruptpin)
* [setLEDBoost()](#setledboost)

### `setLEDBoost()`

Sets APDS LED boost to increase the power of the infra-red LED emitters embedded into the sensor. Up to 3 times of the nominal power may be set.

#### Syntax 

```
APDS.setLEDBoost(boost_mode)
```

#### Parameters

* _boost_mode_: a number, between 0 and 3, that specify the desired power increase. 0 sets boost to 100% (this is the default power value), 1 sets boost to 150%, 2 sets boost to 200% and 3 sets boost to 300%. 

#### Returns

1 on success, 0 on failure

#### Example

```
// Set LED output to maximum power.
APDS.setLEDBoost(3);
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [gestureAvailable()](#gestureavailable)
* [readGesture()](#readgesture)
* [colorAvailable()](#coloravailable)
* [readColor()](#readcolor)
* [proximityAvailable()](#proximityavailable)
* [readProximity()](#readproximity)
* [setGestureSensitivity()](#setgesturesensitivity)
* [setInterruptPin()](#setinterruptpin)