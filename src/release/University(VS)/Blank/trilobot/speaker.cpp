 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: speaker.cpp                             */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#include "speaker.h"
#include <Arduino.h>

Speaker::Speaker(int pin)
{
  this->speaker_pin = pin;
  this->disable();
}
void Speaker::enable()
{
  pinMode(this->speaker_pin, OUTPUT);
}

void Speaker::disable()
{
  pinMode(this->speaker_pin, INPUT);
}

void Speaker::beep(int note, int duration)
{
  tone(this->speaker_pin, note);
  delay(duration);
  noTone(this->speaker_pin);
  delay(50);
  
}

void Speaker::imperial_march()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gis, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);

  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gisH, 325);
  beep(gH, 175);
  beep(fisH, 125);
  beep(fH, 125);    
  beep(fisH, 250);
 
  delay(325);
 
  beep(ais, 250);
  beep(disH, 500);
  beep(dH, 325);  
  beep(cisH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}