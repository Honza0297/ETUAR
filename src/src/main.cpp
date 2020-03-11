#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>

#include "motors.h"
#include "srf08.h"
#include "l3gd20h.h"
#include "sharp1994v0.h"
#include "hcsr04.h"
#include "display.h"
#include "speaker.h"
#include "LSM303D.h"

bool gyro_ok = false;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  display_init();
  gyro_get_bias();
  set_default();
}


void loop()
{ 
  
  
  vector<int16_t> values = mag_get_values();
  Serial.print("X: ");
  Serial.print(values.x*0.16);
  Serial.print(" Y: ");
  Serial.print(values.y*0.16);
  Serial.print(" Z: ");
  Serial.println(values.z*0.16);
  delay(100);
  }
  
  

  


