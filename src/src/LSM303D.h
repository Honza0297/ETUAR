
#ifndef _LSM303D_H
#define _LSM303D_H 1

#include <Arduino.h> 
#include "datatypes.h"


//I2C accel and magnetometer address
#define ACCEL_ADDRESS 0x1d
#define MAG_ADRESS 0x1d

#define OUT_X_L_A 0x28
#define OUT_X_L_M 0x08

vector<float> accel_get_values();

vector<int16_t> mag_get_values();

void set_default();
#endif