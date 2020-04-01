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

/* I2C adresa magnetometru (shodna s akcelerometrem) */
#define MAG_ADDRESS 0x1d

/* Zacatek vystupnich dat akcelerometru */
#define OUT_X_L_M 0x08

/**
 * Trida pro ovladani magnetometru
*/
class Magnetometer
{
    public:
        /**
         * Konstruktor. Nastavi vychozi hodnoty do registru magnetometru a urci vychozi uhel mezi predkem
         * robota a severem, kvuli cemuz potrebuje acelerometr
         * */
        Magnetometer(Accelerometer *accel, byte address = MAG_ADDRESS);
        /**
         * Vrati hodnotu intenzity magnetickeho pole pro vsechny tri osy XYZ.
         * */
        vector<int16_t> get_intensity();
        /**
         * Vrati uhel mezi predkem robota a severem.
         * */
        float heading(Accelerometer *accel);
    private:
        /** I2C adresa konkretni instance magnetometru.
         * */
        byte mag_address;
        /**
         * Minimum hodnot magneticke intenzity
         * */
        vector<int16_t> mag_min;
        /** Maximum hodnot magneticke intenzity.
         * */
        vector<int16_t> mag_max;
        /**
         * Vychozi uhel mezi predkem robota a severem.
         * */
        float origin_from_N = 0;
        /**
         * Nastavi nova minima a maxima hodnot intenzity. Je nutne, aby se s robotem
         * behem nastavovani hybalo!
         * */
        void set_limits();
        /**
         * Nastavi vychozi uhel mezi severem a predkem robota. Volano v konstruktoru.
         * */
        void set_origin_angle(Accelerometer *accel);
};

 #endif