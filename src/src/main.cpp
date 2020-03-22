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
  //init_motors();
  gyro_init();
  //mag_get_boundaries();

}

bool ok = false;
void loop()
{

  float smer = heading(mag_get_values(), accel_get_values());
  Serial.println(smer);
  delay(50);
  /*
  // kod pro gyroskop
  delay(100);
  if(!ok)
  {
    gyro_get_bias();
    ok = true;
  }
    
  
  vector<float> vals = gyro_normalize(gyro_get_values());
  Serial.print("VALS(degrees per second): X: ");
  Serial.print(vals.x);
  Serial.print(", Y: ");
  Serial.print(vals.y);
  Serial.print(", Z: ");
  Serial.println(vals.z);
  delay(20);*/
}