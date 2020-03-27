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
#include "additional/TimerThree.h"

/*Function for periodic interrupt*/
void periodic_interrupt_handler();
volatile bool isTime = false;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  display_init();
  //init_motors();
  gyro_init();
  //mag_get_boundaries(); //zatim nepouzivat - chce to vylepsit
  acc_get_bias();
  gyro_get_bias();
  acc_mag_set_default();
  mag_get_default_vector();
  Timer3.initialize(100000); // = 0.1 s
  Timer3.attachInterrupt(periodic_interrupt_handler);
}





void loop()
{

 /*Periodic code, +- every 100 ms by now (check Timer3.initialize in setup())*/ 
if(isTime)
  {
    isTime = false;

    update_position_simple();
    //update_position_euler();
    
    vector<float> angles = get_position(); 
    Serial.print("X: ");
    Serial.print(angles.x);
    Serial.print(" Y: ");
    Serial.print(angles.y);
    Serial.print(" Z: ");
    Serial.println(angles.z);
  }



  //noInterrupts();
  /*unsigned long oldTime = micros();
  if(millis()-time > 50) //loop at 20 Hz
  {
    time = millis(); //restart
    vector<float> gyro_data = gyro_normalize(gyro_get_values());
    vector<float> check = accel_get_values();
    if(check.z > -0.88) //dont integrate if accelerometer says that you are not horizontally rotating - lepsi mozna porovnavat rozdil odchylky
    {
      angles.x += 0.05*gyro_data.x;
      angles.y += 0.05*gyro_data.y;
    }
    angles.z = heading(mag_get_values(), accel_get_values())-get_origin();

    Serial.print("X: ");
    Serial.print(angles.x);
    Serial.print(" Y: ");
    Serial.print(angles.y);
    Serial.print(" Z: ");
    Serial.println(angles.z);
  }*/
  
  
  
  
  
  
  /*
  if(ok)
  {
   // gyro_get_bias();
    ok = false;
  }
  vector<int16_t> val = gyro_get_values();

  Serial.print(val.x);
  Serial.print(" ");
  Serial.print(val.y);
  Serial.print(" ");
  Serial.print(val.z);
  Serial.print(" ");
  Serial.println("");

  vector<float> val2 = gyro_normalize(val);

  Serial.print(val2.x);
  Serial.print(" ");
  Serial.print(val2.y);
  Serial.print(" ");
  Serial.print(val2.z);
  Serial.print(" ");
  Serial.println("");
  delay(100);

*/
  /*
  //Test rychlosti
  
  Serial.println("######################################");
  float vals[50];
  for (int i = 0; i < 50; i++)
  {
    vals[i] = accel_get_avg_speed(100, 10);
  }
  for (int i = 0; i < 50; i++)
  {
   Serial.print(vals[i]);
  Serial.println(" m/s");
  }
  Serial.println("######################################");
  
  */
  
  /*
    kod pro kompas a tedy pro heading
  float smer = heading(mag_get_values(), accel_get_values());
  Serial.println(smer);
  delay(50);*/
  /*
  // kod pro gyroskop
  delay(100);
  if(!gyro_ok)
  {
    gyro_get_bias(); // volat v setupu
    gyro_ok = true;
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

void periodic_interrupt_handler()
{
  isTime=true;
}