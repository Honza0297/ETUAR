 #ifndef _ACCELEROMETER_H
 #define _ACCELEROMETER_H       1

#include <Arduino.h>
#include "vectors.h"
#define ACCEL_ADDRESS 0x1d

#define OUT_X_L_A 0x28

#define ACCEL_CONVERSION_RATE 0.061/1000. 


class Accelerometer
{
    public: 
        Accelerometer(byte address = ACCEL_ADDRESS);
        vector<int16_t> get_raw_data();
        vector<float> get_acceleration();
    private:
        void set_bias();
        vector<float> accel_bias;
        byte accel_address;
};


 #endif 