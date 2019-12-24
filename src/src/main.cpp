#include <Arduino.h>
#include <Wire.h>

#include "motors.h"
#include "srf08.h"
#include "l3gd20h.h"
#include "sharp1994v0.h"
#include "hcsr04.h"
#include "display.h"

int motor_right = 7;
int motor_left = 6;
bool OK = true;
int val = 0;
byte interruptPin = 2;

void motor_left_interrupt_handler()
{
  OK = false;
  val++;
}

void setup() {
  display_init();
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), motor_left_interrupt_handler, RISING);
}

void loop()
{
  delay(100);
  display_print(10);

  delay(1000);
}