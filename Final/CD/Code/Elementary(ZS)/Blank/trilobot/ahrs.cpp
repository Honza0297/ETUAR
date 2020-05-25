 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: ahrs.cpp                                 */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/
 
#include "ahrs.h"
#include "gyroscope.h"
#include "accelerometer.h"
#include "magnetometer.h"

AHRS::AHRS(Gyroscope *gyro, Accelerometer *accel, Magnetometer *mag)
{ 
    this->gyro = gyro;
    this->accel = accel;
    this->mag = mag;
    this->euler_angles = {0,0,0};
}

vector<float> AHRS::get_euler_angles()
{
    return this->euler_angles;
}

void AHRS::update_euler_angles()
{
  // TODO okomentovat tohle
  static double time = millis();
  float g_roll = 0, g_pitch = 0, g_yaw = 0;
  static float am_roll = 0 , am_pitch = 0 , am_yaw = 0;
  static float am_roll_old = 0 , am_pitch_old = 0 , am_yaw_old = 0;
  float err_roll = 0, err_pitch = 0, err_yaw = 0;
  static float q[4] = {-1,0,0,0};

  float dt = (millis()-time)/1000;

  vector<float> accel = this->accel->get_acceleration();
  vector<int16_t> mag = this->mag->get_intensity();
  vector<float> gyro = this->gyro->get_angular_velocity();

  am_roll_old = am_roll;
  am_pitch_old = am_pitch;
  am_yaw_old = am_yaw;
  am_roll = atan2(accel.y,-accel.z)*ALPHA + am_roll_old*(1-ALPHA);
  am_pitch = atan2(-accel.x,sqrt(accel.y*accel.y + accel.z * accel.z))*ALPHA + (1-ALPHA)*am_pitch_old;
  am_yaw = -atan2((mag.x*sin(am_roll)*sin(am_pitch) + mag.y*cos(am_roll) + mag.z*sin(am_pitch)*sin(am_roll)),(mag.x*cos(am_roll) - mag.z*sin(am_roll)))*ALPHA + (1-ALPHA)*am_yaw_old;
  am_yaw = am_yaw < 0 ? 2*PI + am_yaw : am_yaw;
  
  gyro.x = TO_RAD(gyro.x);
  gyro.y = TO_RAD(gyro.y);
  gyro.z = TO_RAD(gyro.z);
 
 q[0] += ((-q[1]*gyro.x - q[2]*gyro.y - q[3]*gyro.z)/2)*dt;
 q[1] += ((+q[0]*gyro.x + q[2]*gyro.z - q[3]*gyro.y)/2)*dt;
 q[2] += ((+q[0]*gyro.y - q[1]*gyro.z + q[3]*gyro.x)/2)*dt;
 q[3] += ((+q[0]*gyro.z + q[1]*gyro.y - q[2]*gyro.x)/2)*dt;

 g_roll = atan2(2*(q[0]*q[1] + q[2]*q[3]), 1- 2*(q[1]*q[1] + q[2]*q[2]));
 g_pitch = asin(2*(q[3]*q[1] + q[2]*q[0]));//-asin(2*q[1]*q[3]-2*q[0]*q[2]);//
 g_yaw = atan2(2*q[1]*q[2]+2*q[0]*q[3],pow(q[1],2)+pow(q[0],2)-pow(q[3],2)-pow(q[2],2));//atan2(2*(q[0]*q[3] + q[2]*q[1]), 1- 2*(q[2]*q[2] + q[3]*q[3]));*/

  
  err_roll = K*(am_roll-g_roll);
  err_pitch = K*(am_pitch-g_pitch);
  err_yaw = K*(am_yaw-g_yaw);

  euler_angles.x = TO_DEG(err_roll) > 10 ? g_roll : g_roll + err_roll;
  euler_angles.y = TO_DEG(err_pitch) > 10 ? g_pitch : g_pitch + err_pitch;
  euler_angles.z = TO_DEG(err_yaw) > 10 ? g_yaw : g_yaw + err_yaw;

  time = millis();
}