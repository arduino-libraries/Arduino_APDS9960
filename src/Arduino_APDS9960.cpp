#include <Arduino_APDS9960.h>

bool APDS9960::begin() {
  wire.begin();
    
  // Check ID register
  uint8_t id;
  if (!getID(&id)) return false;
  if (id!=0xAB) return false;
    
  // Disable everything
  if (!setENABLE(0x00)) return false;

  return true;
}

bool APDS9960::startGestureSensor() {
  if (!setWTIME(0xFF)) return false;
  if (!setGPULSE(0x8F)) return false; // 16us, 16 pulses // default is: 0x40 = 8us, 1 pulse
  if (!setPPULSE(0x8F)) return false; // 16us, 16 pulses // default is: 0x40 = 8us, 1 pulse
  if (!setGestureIntEnable(true)) return false;
  if (!setGestureMode(true)) return false;
  if (!enablePower()) return false;
  if (!enableWait()) return false;
  if (!enableProximity()) return false;
  if (!enableGesture()) return false;
  return true;
}

// Sets the LED current boost value:
// 0=100%, 1=150%, 2=200%, 3=300%
bool APDS9960::setLEDBoost(uint8_t boost) {
  uint8_t r;
  if (!getCONFIG2(&r)) return false;
  r &= 0b11001111;
  r |= (boost << 4) & 0b00110000;
  return setCONFIG2(r);
}

bool APDS9960::setGestureIntEnable(bool en) {
    uint8_t r;
    if (!getGCONF4(&r)) return false;
    if (en) {
      r |= 0b00000010;
    } else {
      r &= 0b11111101;
    }
    return setGCONF4(r);
}

bool APDS9960::setGestureMode(bool en)
{
    uint8_t r;
    if (!getGCONF4(&r)) return false;
    if (en) {
      r |= 0b00000001;
    } else {
      r &= 0b11111110;
    }
    return setGCONF4(r);
}

bool APDS9960::enablePower() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r |= 0b00000001;
  return setENABLE(r);
}

bool APDS9960::disablePower() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r &= 0b11111110;
  return setENABLE(r);
}

bool APDS9960::enableProximity() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r |= 0b00000100;
  return setENABLE(r);
}

bool APDS9960::disableProximity() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r &= 0b11111011;
  return setENABLE(r);
}

bool APDS9960::enableWait() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r |= 0b00001000;
  return setENABLE(r);
}

bool APDS9960::disableWait() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r &= 0b11110111;
  return setENABLE(r);
}

bool APDS9960::enableGesture() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r |= 0b01000000;
  return setENABLE(r);
}

bool APDS9960::disableGesture() {
  uint8_t r;
  if (!getENABLE(&r)) return false;
  r &= 0b10111111;
  return setENABLE(r);
}

#define APDS9960_ADDR 0x39

bool APDS9960::write(uint8_t val) {
  wire.beginTransmission(APDS9960_ADDR);
  wire.write(val);
  return wire.endTransmission() == 0;
}

bool APDS9960::write(uint8_t reg, uint8_t val) {
  wire.beginTransmission(APDS9960_ADDR);
  wire.write(reg);
  wire.write(val);
  return wire.endTransmission() == 0;
}

bool APDS9960::read(uint8_t reg, uint8_t *val) {
  if (!write(reg)) return false;
  wire.requestFrom(APDS9960_ADDR, 1);
  if (!wire.available()) return false;
  *val = wire.read();
  return true;
}

size_t APDS9960::readBlock(uint8_t reg, uint8_t *val, unsigned int len) {
    size_t i = 0;
    if (!write(reg)) return 0;
    wire.requestFrom(APDS9960_ADDR, len);
    while (wire.available()) {
      if (i == len) return 0;
      val[i++] = wire.read();
    }
    return i;
}

int APDS9960::gestureAvailable() {
  uint8_t r;
  if (!getGSTATUS(&r)) return -1;
  if ((r & 0x01) == 0x00) return -2;
  if (!getGFLVL(&r)) return -3;
  return r;
}

bool in = false;
bool out = false;
int direction = 0;
int dir_in = 0;
int APDS9960::handleGesture() {
  while (true) {
    int available = gestureAvailable();
    if (available <= 0) return 0;

    if (available > 0) {
      uint8_t fifo_data[128];
      uint8_t bytes_read = readGFIFO_U(fifo_data, available * 4);
      if (bytes_read == 0) return 0;

      if (bytes_read >= 4) {
        for (int i = 0; i < bytes_read;) {
          uint8_t u,d,l,r;
          u = fifo_data[i++];
          d = fifo_data[i++];
          l = fifo_data[i++];
          r = fifo_data[i++];
          if (u==0 && d==0 && l==0 && r==0) {
            out = true;
            if (direction != 0) {
              Serial.print(" OUT ");
              Serial.print(direction);
              if (dir_in == 1 && direction == 2) {
                Serial.print(" DOWN!");
              }
              if (dir_in == 2 && direction == 1) {
                Serial.print(" UP!");
              }
              if (dir_in == 3 && direction == 4) {
                Serial.print(" RIGHT!");
              }
              if (dir_in == 4 && direction == 3) {
                Serial.print(" LEFT!");
              }
              Serial.println();
              dir_in = 0;
              direction = 0;
            }
            continue;
          }

          if (u>l && u>r && u>d) {
            direction = 1;
          }
          if (d>l && d>r && d>u) {
            direction = 2;
          }
          if (l>r && l>u && l>d) {
            direction = 3;
          }
          if (r>l && r>u && r>d) {
            direction = 4;
          }

          if (u==255 && d==255 && l==255 && r==255) {
            in = true;
            if (direction != 0) {
              Serial.print(" IN ");
              Serial.print(direction);
              dir_in = direction;
              direction = 0;
            }
            continue;
          }

          // Serial.print(u);
          // Serial.print(",");
          // Serial.print(d);
          // Serial.print(",");
          // Serial.print(l);
          // Serial.print(",");
          // Serial.println(r);
        }
      }
    }
  }
}
