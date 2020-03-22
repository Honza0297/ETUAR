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

void set_measurment(byte unit)
{
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(REG_CMD);
  Wire.write(unit);
  Wire.endTransmission();
  delay(100);
}

int get_distance()
{
  Wire.requestFrom(SRF08_ADDRESS, 4); //TODO test na dostupnost
  Wire.read(); //light sensor value thrown away in this case
  byte high =  Wire.read();
  byte low =  Wire.read();
  uint16_t number = 0;
  number = (uint16_t)(high << 8)+low;
  return number;
}

byte get_light_intensity()
{
  Wire.requestFrom(SRF08_ADDRESS, 4); //TODO test na dostupnost
  byte light_intensity = Wire.read(); 
  return light_intensity;
}