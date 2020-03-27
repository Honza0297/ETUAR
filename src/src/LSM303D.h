
#ifndef _LSM303D_H
#define _LSM303D_H 1

#include <Arduino.h> 
#include "datatypes.h"

#define G  9.8
#define TO_DEG(x) x*180/PI
#define TO_RAD(x) x*PI/180

//I2C accel and magnetometer address
#define ACCEL_ADDRESS 0x1d
#define MAG_ADRESS 0x1d

#define OUT_X_L_A 0x28
#define OUT_X_L_M 0x08

/*
 * @brief Function set default values to make accelerometer and mygnetometer
 * working
*/
void acc_mag_set_default();

/* 
 * @brief Gets the angle between North and Trilo's heading when turned on 
 * or called mag_get_default_vector()
 * */
float get_origin();

float accel_get_avg_speed(float sec, float step = 100);
void mag_get_boundaries();

float heading(vector<int16_t> values, vector<float> a);
vector<float> accel_get_values();

vector<int16_t> mag_get_values();
void mag_get_default_vector();


void acc_get_bias();
void update_position_euler();
void update_position_simple();
vector<float> get_position();
#endif