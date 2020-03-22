
#include "LSM303D.h"
#include <Wire.h>

void writeReg(byte reg, byte value)
{
  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void set_default()
{
    writeReg(0x21, 0x00);

    // 0x57 = 0b01010111
    // AODR = 0101 (50 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
    writeReg(0x20, 0x57);

    // Magnetometer

    // 0x64 = 0b01100100
    // M_RES = 11 (high resolution mode); M_ODR = 001 (6.25 Hz ODR)
    writeReg(0x24, 0x64);

    // 0x20 = 0b00100000
    // MFS = 01 (+/- 4 gauss full scale)
    writeReg(0x25, 0x20);

    // 0x00 = 0b00000000
    // MLP = 0 (low power mode off); MD = 00 (continuous-conversion mode)
    writeReg(0x26, 0x00);
}

vector<float> accel_get_values()
{
  vector<float> return_vec;

  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(OUT_X_L_A | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(ACCEL_ADDRESS, (byte)6);
  while(Wire.available() < 6);
  
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();
   

  return_vec.x = (float)((xh << 8) + xl)*0.061/1000.;
  return_vec.y = (float)((yh << 8) + yl)*0.061/1000.;
  return_vec.z = (float)((zh << 8) + zl)*0.061/1000.;
  return return_vec;
}

vector<int16_t> mag_get_values()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(MAG_ADRESS);
  Wire.write(OUT_X_L_M | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(MAG_ADRESS, (byte)6);
  while(Wire.available() < 6);
  
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();
   

  return_vec.x = (int16_t)((xh << 8) + xl);
  return_vec.y = (int16_t)((yh << 8) + yl);
  return_vec.z = (int16_t)((zh << 8) + zl);
  return return_vec;
}
