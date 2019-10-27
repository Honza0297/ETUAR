#include <Arduino.h>
#include "motors.h"

int motor_right = 7;
int motor_left = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);
  
}


void loop() {
  analogWrite(motor_right,145);
  analogWrite(motor_left,145);
   delay(2000);
   move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
   delay(5000);
}
