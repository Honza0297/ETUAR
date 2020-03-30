#ifndef _I2C_H
#define _I2C_H 1

#include <Arduino.h>
#include <Wire.h>

void reg_write(byte slave_addr, byte reg, byte value);

#endif