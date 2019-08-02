
#ifndef ARDUINO_APDS9960
#define ARDUINO_APDS9960

#include <Wire.h>

enum {
  GESTURE_NONE = -1,
  GESTURE_UP = 0,
  GESTURE_DOWN = 1,
  GESTURE_LEFT = 2,
  GESTURE_RIGHT = 3
};

class APDS9960 {
public:
  APDS9960(TwoWire &wire, int irqPin);
  virtual ~APDS9960();

  bool begin();
  void end();

  int gestureAvailable();
  int readGesture();

  int colorAvailable();
  bool readColor(int& r, int& g, int& b);
  bool readColor(int& r, int& g, int& b, int& c);

  int proximityAvailable();
  int readProximity();

private:
  bool setLEDBoost(uint8_t boost);
  bool setGestureIntEnable(bool en);
  bool setGestureMode(bool en);
  int gestureFIFOAvailable();
  int handleGesture();

  bool enablePower();
  bool disablePower();
  bool enableColor();
  bool disableColor();
  bool enableProximity();
  bool disableProximity();
  bool enableWait();
  bool disableWait();
  bool enableGesture();
  bool disableGesture();

private:
  TwoWire &wire;
  int irqPin;

  bool in;
  bool out;
  int direction;
  int dir_in;
  uint8_t threshold;
  int gesture;

  bool write(uint8_t val);
  bool write(uint8_t reg, uint8_t val);
  bool read(uint8_t reg, uint8_t *val);
  size_t readBlock(uint8_t reg, uint8_t *val, unsigned int len);

private:
#define REG(name, addr) \
  bool get##name(uint8_t *val) { return read(addr,  val); } \
  bool set##name(uint8_t val)  { return write(addr, val); } \
  size_t read##name(uint8_t *val, uint8_t len) { return readBlock(addr, val, len); }
  REG(ENABLE,     0x80)
  REG(ATIME,      0x81)
  REG(WTIME,      0x83)
  REG(AILTL,      0x84)
  REG(AILTH,      0x85)
  REG(AIHTL,      0x86)
  REG(AIHTH,      0x87)
  REG(PILT,       0x89)
  REG(PIHT,       0x8B)
  REG(PERS,       0x8C)
  REG(CONFIG1,    0x8D)
  REG(PPULSE,     0x8E)
  REG(CONTROL,    0x8F)
  REG(CONFIG2,    0x90)
  REG(ID,         0x92)
  REG(STATUS,     0x93)
  REG(CDATAL,     0x94)
  REG(CDATAH,     0x95)
  REG(RDATAL,     0x96)
  REG(RDATAH,     0x97)
  REG(GDATAL,     0x98)
  REG(GDATAH,     0x99)
  REG(BDATAL,     0x9A)
  REG(BDATAH,     0x9B)
  REG(PDATA,      0x9C)
  REG(POFFSET_UR, 0x9D)
  REG(POFFSET_DL, 0x9E)
  REG(CONFIG3,    0x9F)
  REG(GPENTH,     0xA0)
  REG(GEXTH,      0xA1)
  REG(GCONF1,     0xA2)
  REG(GCONF2,     0xA3)
  REG(GOFFSET_U,  0xA4)
  REG(GOFFSET_D,  0xA5)
  REG(GPULSE,     0xA6)
  REG(GOFFSET_L,  0xA7)
  REG(GOFFSET_R,  0xA9)
  REG(GCONF3,     0xAA)
  REG(GCONF4,     0xAB)
  REG(GFLVL,      0xAE)
  REG(GSTATUS,    0xAF)
  REG(IFORCE,     0xE4)
  REG(PICLEAR,    0xE5)
  REG(CICLEAR,    0xE6)
  REG(AICLEAR,    0xE7)
  REG(GFIFO_U,    0xFC)
  REG(GFIFO_D,    0xFD)
  REG(GFIFO_L,    0xFE)
  REG(GFIFO_R,    0xFF)
};

extern APDS9960 APDS;

#endif // ARDUINO_APDS9960
