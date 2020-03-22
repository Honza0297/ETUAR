 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: l3gd20h.h                               */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /**************************************************/
#include <Wire.h>
#include "l3gd20h.h"

vector<float> BIAS = {0,0,0};

void gyro_reg_write(byte reg, byte value)
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void gyro_init()
{
  gyro_reg_write(LOW_ODR, 0x00);
  gyro_reg_write(CTRL4, 0x00);
  gyro_reg_write(CTRL1,0x6F);
  delay(10);
  gyro_get_bias();
}

void gyro_get_bias(int measurements = 14)
{
  delay(100);
  BIAS = {0,0,0};
  vector<int16_t> vals;
  for(int i = 0; i < measurements; i++)
  {
   vector<int16_t> temp = gyro_get_values();
    vals.x += temp.x;
    vals.y += temp.y;
    vals.z += temp.z;
    delay(5);
  }

  BIAS.x = vals.x/measurements*8.75/1000.;
  BIAS.y = vals.y/measurements*8.75/1000.;
  BIAS.z = vals.z/measurements*8.75/1000.-5;
  
}

vector<float> gyro_normalize(vector<int16_t> values)
{
  vector<float> return_vec;
  return_vec.x = values.x*8.75/1000.-BIAS.x;
  return_vec.y = values.y*8.75/1000.-BIAS.y;
  return_vec.z = values.z*8.75/1000.-BIAS.z;
  return return_vec;
}

vector<int16_t> gyro_get_values()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(OUT_X_L | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS, (byte)6);
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

int8_t gyro_get_temperature()
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(OUT_TEMP | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS, (byte)1);
  while(Wire.available() < 1);
  
  int8_t temp = Wire.read();
  /* built-in temp sensor is not intended to use for ambient temperature measurement. 
   * However, it CAN be used for that, if BIAS is revealed by try-and-mistake as it
   * is not specified in the datasheet. */
  return 36-temp;
}