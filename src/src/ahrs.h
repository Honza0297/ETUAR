 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: ahrs.h                                  */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/
#ifndef _AHRS_H
#define _AHRS_H       1

#include "vectors.h"
#include "accelerometer.h"
#include "magnetometer.h"
#include "gyroscope.h"

#define K 0.02 //0.02
#define ALPHA 0.025 //0.025
#define TO_DEG(x) x*180/PI
#define TO_RAD(x) x*PI/180

class AHRS 
{
    public:
        AHRS(Gyroscope *gyro, Accelerometer *accel, Magnetometer *mag);
        vector<float> get_euler_angles();
        void update_euler_angles();
    private:
        Gyroscope *gyro;
        Accelerometer *accel;
        Magnetometer *mag;
        vector<float> euler_angles;
};

 #endif 