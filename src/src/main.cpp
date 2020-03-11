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

bool gyro_ok = false;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  display_init();
  gyro_get_bias();
}


void loop()
{ 
  
  vector<float> values = gyro_normalize(gyro_get_values());
  Serial.print("X: ");
  Serial.print((int)values.x);
  Serial.print(" Y: ");
  Serial.print((int)values.y);
  Serial.print(" Z: ");
  Serial.println((int)values.z);
  delay(100);
  }
  
  

  


