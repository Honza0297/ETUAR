#include <Arduino.h>
#include <Wire.h>
#include "l3gd20h.h"

void gyro_reg_write(byte reg, byte value)
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void init_gyro()
{
gyro_reg_write(LOW_ODR, 0x00);
gyro_reg_write(CTRL4, 0x00);
gyro_reg_write(CTRL1,0x6F);
}

int io_timeout = 0;  // 0 = no timeout
bool did_timeout = false;

vector<int16_t> gyro_get_values()
{
  vector<int16_t> return_vec;
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(OUT_X_L | (1 << 7)); //TODO
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS, (byte)6);
  while(Wire.available() < 6)
  {

  }
  
  //TODO check if data available
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();

  // combine high and low bytes
  return_vec.x = (int16_t)(xh << 8) | xl;
  return_vec.y = (int16_t)(yh << 8) | yl;
  return_vec.z = (int16_t)(zh << 8) | zl;
  return return_vec;
}
