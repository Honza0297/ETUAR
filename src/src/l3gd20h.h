 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: l3gd20h.h                               */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* Function prorotypes for gyroscope l3gd2Oh      */
 /* from minIMU sensor. Detailed specification can */
 /* be seen in documentation [0]                   */
 /**************************************************/

#ifndef _L3GD20H_H
#define _L3GD20H_H 1

#include <Arduino.h> 
#include "datatypes.h"

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
* When high pass filter is enabled, reference value is here, unused in this project.
*/
#define REFERENCE 0x25 

/* temperature data register, two´s complement*/
#define OUT_TEMP 0x26 


/*
* |ZYXOR| ZOR| YOR| XOR| ZYXDA | ZDA |YDA| XDA|
* ZYXOR: X, Y, Z -axis data overrun. Default value: 0(0: no overrun has occurred; 1: new data has overwritten the previous one before it was read)
* ZOR: Z axis data overrun. Default value: 0 (0: no overrun has occurred; 1: a new data for the Z-axis has overwritten the previous one)
* YOR: Y axis data overrun. Default value: 0 (0: no overrun has occurred; 1: a new data for the Y-axis has overwritten the previous one)
* XOR X axis data overrun. Default value: 0(0: no overrun has occurred; 1: a new data for the X-axis has overwritten the previous one)
* ZYXDA: X, Y, Z -axis new data available. Default value: 0(0: a new set of data is not yet available; 1: a new set of data is available)
* ZDA: Z axis new data available. Default value: 0 (0: a new data for the Z-axis is not yet available; 1: a new data for the Z-axis is available)
* YDA: Y axis new data available. Default value: 0 (0: a new data for the Y-axis is not yet available;1: a new data for the Y-axis is available)
* XDA: X axis new data available. Default value: 0 (0: a new data for the X-axis is not yet available; 1: a new data for the X-axis is available)
*/
#define STATUS 0x27


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

/*
* FIFO mode, default is bypass mode = 0000 = no FIFO
* Default values OK for this project.
*/
#define FIFO_CTRL  0x2E 

/* Unused in this project*/
#define FIFO_SRC   0x2F 


#define IG_CFG 0x30 //interrupt register, unused in this project
#define IG_SRC 0x31 //interrupt register, unused in this project
#define IG_THS_XH 0x32  //interrupt register, unused in this project
#define IG_THS_XL 0x33  //interrupt register, unused in this project
#define IG_THS_YH 0x34  //interrupt register, unused in this project
#define IG_THS_YL 0x35  //interrupt register, unused in this project
#define IG_THS_ZH 0x36  //interrupt register, unused in this project
#define IG_THS_ZL 0x37  //interrupt register, unused in this project
#define IG_DURATION 0x38  //interrupt register, unused in this project

/*
* |-|-|DRDY_GL|0|I2C_disable|SW_RES|0|Low_ODR|
* DRDY_HL - interrupt2 pin active level, default 0
* I2C_dis: 1 = i2c disabled, 0 = i2c enabled
* SW_RES; software reset if 1
* Low_ODR - low output data rate, can be set by combination of Low_odr, DR and BW
*/
#define LOW_ODR 0x39  



/*
* Function return vector of current angular rate for all three axes. 
* If sensor is not available, returns zeroes. 
*/
vector<int16_t> gyro_get_values();

/*
* Init function which prepares gyroscope for collecting data.
*/
void gyro_get_bias();

int8_t gyro_get_temperature();

/* normalizes to deg/s */
vector<float> gyro_normalize(vector<int16_t> values);

#endif
