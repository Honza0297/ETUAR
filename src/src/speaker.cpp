#include "speaker.h"
#include <Arduino.h>

void enable_speaker()
{
  pinMode(SPEAKER_PIN, OUTPUT);
}

void disable_speaker()
{
  pinMode(SPEAKER_PIN, INPUT);
}

void beep(int note, int duration)
{
  tone(SPEAKER_PIN, note);
  delay(duration);
  noTone(SPEAKER_PIN);
  delay(50);
  
}

void imperial_march()
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