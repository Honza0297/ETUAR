 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: srf08.cpp                               */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /**************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "srf08.h"

void set_measurement(byte unit)
{
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(REG_CMD);
  Wire.write(unit);
  Wire.endTransmission();
  delay(100);
}

int get_distance()
{
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(0x02);                           
  Wire.endTransmission();

  Wire.requestFrom(SRF08_ADDRESS, 2); 
  while(Wire.available() < 0);
  byte high =  Wire.read();
  byte low =  Wire.read();
  uint16_t number = 0;
  number = (uint16_t)(high << 8)+low;
  return number;
}

byte get_light_intensity()
{
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(0x01);                         
  Wire.endTransmission();

  Wire.requestFrom(SRF08_ADDRESS, 1); 
  while(Wire.available() < 0);
  
  byte light_intensity = Wire.read(); 
  return light_intensity;
}