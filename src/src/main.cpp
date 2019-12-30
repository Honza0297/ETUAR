#include <Arduino.h>
#include <Wire.h>

#include "motors.h"
#include "srf08.h"
#include "l3gd20h.h"
#include "sharp1994v0.h"
#include "hcsr04.h"
#include "display.h"



void setup() {
  Serial.begin(9600);
  //display_init();
  init_motors();
}

void loop()
{
  delay(1000);
  turn(LEFT, 90);
  move(30, FORWARD, 80);
}
