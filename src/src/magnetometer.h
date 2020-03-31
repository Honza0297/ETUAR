 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: magnetometer.h                          */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

 
#ifndef _MAGNETOMETER_H
#define _MAGNETOMETER_H       1

#include <Arduino.h>
#include "vectors.h"
#include "accelerometer.h"

#define MAG_ADDRESS 0x1d

#define OUT_X_L_M 0x08

class Magnetometer
{
    public:
        Magnetometer(Accelerometer *accel, byte address = MAG_ADDRESS);
        vector<int16_t> get_intensity();
        float heading(Accelerometer *accel);
    private:
        byte mag_address;
        vector<int16_t> mag_min;
        vector<int16_t> mag_max;
        float origin_from_N = 0;
        void set_limits();
        void set_origin_angle(Accelerometer *accel);
};

 #endif