 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: gyroscope.cpp                           */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#include <Wire.h>
#include "gyroscope.h"
#include "I2C.h"

vector<float> BIAS = {300,-1600,100};



Gyroscope::Gyroscope(byte address)
{
  this->gyro_address = address;
  reg_write(this->gyro_address, LOW_ODR, 0x00);
  reg_write(this->gyro_address, CTRL4, 0x00);
  reg_write(this->gyro_address, CTRL1, 0x6F);
  delay(10);
  this->get_bias();
}

void Gyroscope::get_bias(int num_of_measurements)
{
  BIAS = {0,0,0};
  vector<int16_t> vals = {0,0,0};
  for(int i = 0; i < num_of_measurements; i++)
  {
   vector<int16_t> temp = get_raw_data();
    vals.x += temp.x;
    vals.y += temp.y;
    vals.z += temp.z;
    delay(5);
  }

  BIAS.x = vals.x/num_of_measurements;
  BIAS.y = vals.y/num_of_measurements;
  BIAS.z = vals.z/num_of_measurements;

  /*Serial.print(BIAS.x);
  Serial.print(" ");
  Serial.print(BIAS.y);
  Serial.print(" ");
  Serial.print(BIAS.z);
  Serial.print(" ");
  Serial.println("");*/
  
}

vector<float> Gyroscope::get_angular_velocity()
{
  vector<int16_t> values = this->get_raw_data();
  vector<float> return_vec;
  return_vec.x = (values.x-BIAS.x)*GYRO_CONVERSION_RATE;
  return_vec.y = (values.y-BIAS.y)*GYRO_CONVERSION_RATE;
  return_vec.z = (values.z-BIAS.z)*GYRO_CONVERSION_RATE;
  
  /*In degrees per second*/
  return return_vec;
}

vector<int16_t> Gyroscope::get_raw_data()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(OUT_X_L | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS, 6);
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

byte Gyroscope::get_temperature()
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.write(OUT_TEMP | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru
  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS, 1);
  while(Wire.available() < 1);
  
  byte temp = Wire.read();
  /* built-in temp sensor is not intended to use for ambient temperature measurement. 
   * However, it CAN be used for that, if BIAS is revealed by try-and-mistake as it
   * is not specified in the datasheet. */
  return 36-temp;
}