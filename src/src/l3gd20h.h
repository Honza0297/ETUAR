#ifndef _L3GD20H_H
#define _L3GD20H_H

#include <Arduino.h> // for byte data type

#define GYRO_ADDRESS 0x6b

#define WHO_AM_I   0x0F 
#define CTRL1  0x20 // D20, 4200D
        /*|DR1|DR0; output data rate, |BW1|BW0|PD|Zen|Yen|Xen|*/
        //DR = 01
        //BW = 10
        //PD = 1
        //Zen,Xen,Yen = 111
        //default = 0b01101111 (outpout rate = 200 Hz, bandwitch 50 Hz, power on, all axis)
#define CTRL2    0x21 // unused here, sets filtering, external trigger enable..., defaults are OK
#define CTRL3    0x22 // interrupt setting, defaults are OK
#define CTRL4   0x23 
        /*|BDU; block data update; 0 = continual, 1 only after read|BLE; 0 = little endian, 1 = big endian|FS0|FS1; full scale selection, 0 default; 245 dps|
        0|ST2|ST1 = self tests, default = 0|SPI interface mode|*/
        //default: 0b00000000
#define CTRL5    0x24 // defaults are OK
       /*|BOOT|FIFO_EN|stop_on_FTH||||||*/
       //BOOT - reboot with 1
       //FIFO enable, 1 = enable, 0 disable (default)
       //stop_on_fth = when FIFO treshold set, here it is enabled
#define REFERENCE 0x25 //when high pass filter is enabled, reference value is here, unused in this project
#define OUT_TEMP 0x26 //temperature data, two´s complement
#define STATUS 0x27
/*|ZYXOR| ZOR| YOR| XOR| ZYXDA | ZDA |YDA| XDA|
ZYXOR: X, Y, Z -axis data overrun. Default value: 0(0: no overrun has occurred; 1: new data has overwritten the previous one before it was read)
ZOR: Z axis data overrun. Default value: 0 (0: no overrun has occurred; 1: a new data for the Z-axis has overwritten the previous one)
YOR: Y axis data overrun. Default value: 0 (0: no overrun has occurred; 1: a new data for the Y-axis has overwritten the previous one)
XOR X axis data overrun. Default value: 0(0: no overrun has occurred; 1: a new data for the X-axis has overwritten the previous one)
ZYXDA: X, Y, Z -axis new data available. Default value: 0(0: a new set of data is not yet available; 1: a new set of data is available)
ZDA: Z axis new data available. Default value: 0 (0: a new data for the Z-axis is not yet available; 1: a new data for the Z-axis is available)
YDA: Y axis new data available. Default value: 0 (0: a new data for the Y-axis is not yet available;1: a new data for the Y-axis is available)
XDA: X axis new data available. Default value: 0 (0: a new data for the X-axis is not yet available; 1: a new data for the X-axis is available)*/

#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
/*Angular velocity/rate as two´s complement for all axis */

#define FIFO_CTRL  0x2E // default are OK 
/*FIFO mode, default bypass mode = 0000 = no FIFO*/
#define FIFO_SRC   0x2F //unused in this project


#define IG_CFG 0x30 //interrupt register, unused in this project
#define IG_SRC 0x31 //interrupt register, unused in this project
#define IG_THS_XH 0x32  //interrupt register, unused in this project
#define IG_THS_XL 0x33  //interrupt register, unused in this project
#define IG_THS_YH 0x34  //interrupt register, unused in this project
#define IG_THS_YL 0x35  //interrupt register, unused in this project
#define IG_THS_ZH 0x36  //interrupt register, unused in this project
#define IG_THS_ZL 0x37  //interrupt register, unused in this project
#define IG_DURATION 0x38  //interrupt register, unused in this project

#define LOW_ODR 0x39  
/*|-|-|DRDY_GL|0|I2C_disable|SW_RES|0|Low_ODR|
DRDY_HL - interrupt2 pin active level, default 0
I2C_dis: 1 = i2c disabled, 0 = i2c enabled
SW_RES; software reset if 1
Low_ODR - low output data rate, can be set by combination of Low_odr, DR and BW
*/
template <typename T> struct vector
{
    T x, y, z;
};

vector<int16_t> gyro_get_values();
void init_gyro();
void gyro_reg_write(byte reg, byte value);

#endif
