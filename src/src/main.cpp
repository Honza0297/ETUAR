#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>

#include "motors.h"
#include "srf08.h"

//#include "l3gd20h.h" //deprecated
#include "gyroscope.h"

#include "sharp1994v0.h"
#include "hcsr04.h"
#include "display.h"
#include "speaker.h"

//#include "LSM303D.h"
#include "accelerometer.h"
#include "magnetometer.h"
#include "ahrs.h"

#include "additional/TimerThree.h"

float roll, pitch, yaw;


/*Function for periodic interrupt*/
void periodic_interrupt_handler();
volatile bool isTime = false;

Display *display = new Display();
Speaker *speaker = new Speaker();

Motors *motors = new Motors();

HCSR04 *hcsr04 = new HCSR04();
Sharp *sharp = new Sharp();
SRF08 *srf08 = new SRF08();


Gyroscope *gyro = new Gyroscope();
Accelerometer *accel = new Accelerometer();
Magnetometer *mag = new Magnetometer(accel);

AHRS *ahrs = new AHRS(gyro, accel, mag);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Timer3.initialize(50000); // = 0.05 s =+- 20 Hz
  Timer3.attachInterrupt(periodic_interrupt_handler);
}





/*float g_roll = 0, g_pitch = 0, g_yaw = 0;
float am_roll = 0 , am_pitch = 0 , am_yaw = 0;
float am_roll_old = 0 , am_pitch_old = 0 , am_yaw_old = 0;
float roll = 0, pitch = 0, yaw = 0;
float err_roll = 0, err_pitch = 0, err_yaw = 0;
float q[4] = {-1,0,0,0};*/
double time = 0;
void loop()
{  
 //time = millis();

 //update_position_euler();
  delay(2000);
  motors->move(30,50);
  delay(2000);

  /*Serial.print("X: ");
  Serial.print(TO_DEG(roll));
  Serial.print(" Y: ");
  Serial.print(TO_DEG(pitch));
  Serial.print(" Z: ");
  //Serial.println(heading(mag_get_values(), accel_get_values()));
  Serial.println(TO_DEG(yaw));
  //while(millis()-time < 50); //f = 20 Hz+-
 delay(20);*/
 
 
 
 
 
 
 /*Periodic code, +- every 100 ms by now (check Timer3.initialize in setup())*/ 
if(isTime)
  {
    isTime = false;
    ahrs->update_euler_angles();
  }
/*
    update_position_simple();
    //update_position_euler();
    
    vector<float> angles = get_position(); 
    Serial.print("X: ");
    Serial.print(angles.x);
    Serial.print(" Y: ");
    Serial.print(angles.y);
    Serial.print(" Z: ");
    Serial.println(angles.z);
  }*/



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