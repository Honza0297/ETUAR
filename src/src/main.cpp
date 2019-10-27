#include <Arduino.h>
#include <Wire.h>
#include "motors.h"
#include "srf08.h"
#include "l3gd20h.h"

int motor_right = 7;
int motor_left = 6;



/*
* for motors test
* analogWrite(motor_right,145);
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
*/
/*
for srf08 test

set_measurment(CMD_CM);
delay(70);
Serial.print(get_distance());
Serial.print("\n");
delay(500);
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);


  Wire.begin();
  init_gyro();
  
  
}

void loop() {
  
  vector<int16_t> values = gyro_get_values();
  Serial.write("Udaje z gyra (deg/s): x: ");
  Serial.print((int)values.x*8.75/1000);
  Serial.write(", y: ");
  Serial.print((int)values.y*8.75/1000);
  Serial.write(", z: ");
  Serial.print((int)values.z*8.75/1000);
  Serial.write("\n");
  delay(100);
}