#ifndef _GYROSCOPE_H
#define _GYROSCOPE_H  1

#include <Arduino.h> 
#include "vectors.h"

/*Converts from raw gyro data to degrees per second*/
#define GYRO_CONVERSION_RATE 8.75/1000.

//I2C gyroscope address
#define GYRO_ADDRESS 0x6b
//Address of ID register
#define WHO_AM_I   0x0F
/*
* |DR1|DR0; output data rate, |BW1|BW0|PD|Zen|Yen|Xen|
* DR = 01
* BW = 10
* PD = 1
* Zen,Xen,Yen = 111
* default = 0b01101111 (outpout rate = 200 Hz, bandwitch 50 Hz, power on, all axis)
*/
#define CTRL1  0x20

/* Filtering, external trigger enable...Default values are OK  */
#define CTRL2    0x21 

/* Interrupt settings, default values are OK*/
#define CTRL3    0x22 

/*|BDU; block data update; 0 = continual, 1 only after read|BLE; 0 = little endian, 1 = big endian|FS0|FS1; full scale selection, 0 default; 245 dps|
*       0|ST2|ST1 = self tests, default = 0|SPI interface mode|
*  default: 0b00000000 
*/
#define CTRL4   0x23 
       
/*
* |BOOT|FIFO_EN|stop_on_FTH||||||
* BOOT - reboot with 1 set here
* FIFO enable, 1 = enable, 0 disable (default)
* stop_on_fth = when FIFO treshold set, here it is enabled
* Default values are OK
*/
#define CTRL5    0x24

/*
* Angular velocity/rate as two´s complement for all axis.
* Every value is in two registers 
*/
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

/* temperature data register, two´s complement*/
#define OUT_TEMP 0x26 

/*
* |-|-|DRDY_GL|0|I2C_disable|SW_RES|0|Low_ODR|
* DRDY_HL - interrupt2 pin active level, default 0
* I2C_dis: 1 = i2c disabled, 0 = i2c enabled
* SW_RES; software reset if 1
* Low_ODR - low output data rate, can be set by combination of Low_odr, DR and BW
*/
#define LOW_ODR 0x39  

class Gyroscope
{
    public:
        Gyroscope(byte address = GYRO_ADDRESS);
        byte get_temperature();
        vector<int16_t> get_raw_data();
        vector<float> get_angular_velocity();
    private:
        int gyro_address; 
        void get_bias(int num_of_measurements = 14);

};
#endif