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
  //Timer3.initialize(100000); // = 0.1 s
  //Timer3.attachInterrupt(periodic_interrupt_handler);
}




double time = 0;
float roll = 0, pitch = 0, yaw = 0;
float q[4] = {-1,0,0,0};
void loop()
{ 
  
  float dt = (millis()-time)/1000;

  vector<float> accel = accel_get_values();
  /*accel.x = -accel.z*(sin(roll)*sin(yaw) - cos(roll)*cos(yaw)*sin(pitch));
  accel.y = -accel.z * (cos(yaw)*sin(roll) + cos(roll)*cos(yaw)*sin(pitch));
  accel.z = -accel.z * (cos(pitch)*cos(roll));*/

  vector<int16_t> mag = mag_get_values();
  //vector<float> mag = m;
 /* mag.x = cos(yaw)*cos(pitch)*m.x + (cos(roll)*sin(yaw)+cos(yaw)*sin(roll)*sin(pitch))*m.y + (sin(roll)*sin(yaw) - cos(roll)*cos(yaw)*sin(pitch))*m.z;
  mag.y = -cos(pitch)*sin(yaw)*m.x + (cos(yaw)*cos(roll)+sin(pitch)*sin(roll)*sin(yaw))*m.y +  cos(roll)*cos(yaw)*sin(pitch)*m.z;
  mag.z = sin(pitch)*m.x - cos(pitch)*sin(roll)*m.y + (cos(pitch)*cos(roll))*m.z;*/

  roll = atan2(accel.y,-accel.z);
  pitch = atan2(-accel.x,sqrt(accel.y*accel.y + accel.z * accel.z));
  yaw = -atan2((mag.x*sin(roll)*sin(pitch) + mag.y*cos(roll) + mag.z*sin(pitch)*sin(roll)),(mag.x*cos(roll) - mag.z*sin(roll)));
  //yaw = yaw < 0 ? 2*PI + yaw : yaw;
  /*
  //docela slušná iomplementace gyro XYZ yaw pitch roll
  vector<float> gyro = gyro_normalize(gyro_get_values());
  gyro.x = TO_RAD(gyro.x);
  gyro.y = TO_RAD(gyro.y);
  gyro.z = TO_RAD(gyro.z);
 
 q[0] += ((-q[1]*gyro.x - q[2]*gyro.y - q[3]*gyro.z)/2)*dt;
 q[1] += ((+q[0]*gyro.x + q[2]*gyro.z - q[3]*gyro.y)/2)*dt;
 q[2] += ((+q[0]*gyro.y - q[1]*gyro.z + q[3]*gyro.x)/2)*dt;
 q[3] += ((+q[0]*gyro.z + q[1]*gyro.y - q[2]*gyro.x)/2)*dt;

 roll = atan2(2*(q[0]*q[1] + q[2]*q[3]), 1- 2*(q[1]*q[1] + q[2]*q[2]));
 pitch = asin(2*(q[3]*q[1] + q[2]*q[0]));//-asin(2*q[1]*q[3]-2*q[0]*q[2]);//
 yaw = atan2(2*q[1]*q[2]+2*q[0]*q[3],pow(q[1],2)+pow(q[0],2)-pow(q[3],2)-pow(q[2],2));//atan2(2*(q[0]*q[3] + q[2]*q[1]), 1- 2*(q[2]*q[2] + q[3]*q[3]));*/
 /*roll += (gyro.x*cos(yaw)/cos(pitch) -  sin(yaw)/cos(pitch)*gyro.y)*dt;

 pitch += (sin(yaw)*gyro.x - cos(yaw)*gyro.y)*dt;

 yaw += (- cos(yaw)*sin(pitch)/cos(pitch)*gyro.x + sin(pitch)*sin(yaw)/cos(pitch)*gyro.y + gyro.z)*dt;*/
  Serial.print("X: ");
  Serial.print(TO_DEG(roll));
  Serial.print(" Y: ");
  Serial.print(TO_DEG(pitch));
  Serial.print(" Z: ");
  Serial.println(TO_DEG(yaw));
  time = millis(); //set timer
  while(millis()-time < 20); //f = 50 Hz+-
 
 
 
 
 
 
 
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