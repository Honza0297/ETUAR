#include "I2C.h"

void reg_write(byte slave_addr, byte reg, byte value)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}