 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: srf08.cpp                               */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "srf08.h"

SRF08::SRF08()
{
  Wire.begin();
}

void SRF08::set_measurement(byte unit)
{
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(REG_CMD);
  Wire.write(unit);
  Wire.endTransmission();
  /*V dokumentaci se pise 60 ms, ale to nemusi stacit*/
  delay(100);
}

int SRF08::get_distance(byte unit)
{
  this->set_measurement(unit);

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

byte SRF08::get_light_intensity()
{
  this->set_measurement();

  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(0x01);                         
  Wire.endTransmission();

  Wire.requestFrom(SRF08_ADDRESS, 1); 
  while(Wire.available() < 0);
  
  byte light_intensity = Wire.read(); 
  return light_intensity;
}

byte SRF08::zmer_svetlo()
{ 
  this->set_measurement(); /* Zahajeni mereni */
  /*Pozadame SRF-08 o informaci 
  pocinajici REGISTREM FOTOCIDLA*/
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(0x00/*TODO REGISTR FOTOCIDLA*/);
  Wire.endTransmission();

  /*Pozadame pouze o jeden bajt...*/
  Wire.requestFrom(SRF08_ADDRESS, 1); 
  /*... a pockame, dokud nebude dostupny*/
  while(Wire.available() < 0);

  /*TODO: precist hodnotu a vratit ji.
    * Nasledujici radky pouze zajisti, ze se kod 
    * zkompiluje, po doplneni smazat.*/
  byte value = 0;
  return value;
}

int SRF08::zmer_vzdalenost()
{
  /*Navazeme komunikaci*/
  Wire.beginTransmission(SRF08_ADDRESS);
  /*Napiseme, kam chceme zapisovat...*/
  Wire.write(REG_CMD); /* expanduje do 0x00 */
  /*...a co chceme zapisovat.*/
  Wire.write(0x00/*TODO spravna jednotka k nalezeni ve slajdech*/);
  /*Nakonec ukoncime prenos*/
  Wire.endTransmission();
  
  /* TODO: pockat 100 ms*/
  
  /* Zajimaji nas data od registru 0x02*/
  Wire.beginTransmission(SRF08_ADDRESS);
  Wire.write(0x02);                           
  Wire.endTransmission();
  /* TODO precist data, spojit je a vratit*/
  
  uint16_t return_value = 0;
  return return_value;
}