/************************************************ */
/*  Educational tutorial for Arduino in robotics  */
/*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
/*  File: accelerometer.h                         */
/*  Author: Jan Beran                             */
/*  Date: March 2020                              */
/*                                                */
/* This file is a part of author´s bachelor thesis*/
/*                                                */
/**************************************************/
#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H       1

#include <Arduino.h>
#include "vectors.h"

/* Adresa akcelerometru*/
#define ACCEL_ADDRESS 0x1d

/* Zacatek dat z akcelerometru*/
#define OUT_X_L_A 0x28

/* Konverze ze surovych dat do m/s**2 pri default hodnotach*/
#define ACCEL_CONVERSION_RATE 0.061/1000. 


/* Trida pro ovladani akcelerometru */
class Accelerometer
{
    public:
        /**
         * Konstruktor. Nastavi zakladni hodnoty do regitru a jisti bias.
         * */ 
        Accelerometer(byte address = ACCEL_ADDRESS);
        /**
         * Funkce vraci surova data primo vyctena z registru akcelerometru.
         * */
        vector<int16_t> get_raw_data();
        /**
         *  Funkce vrai konvertovana data do m/s**2
         * */
        vector<float> get_acceleration();
    private:
        /**
         * Funkce zjisti odchylky mereni od nuloveho stavu. 
         * Pri nejim provadeni je vyzadovano, aby se s robotem nepohybovalo.
         * */
        void set_bias();
        /* Hodnoty biasu */
        vector<float> accel_bias;
        /* Adresa akcelerometru */
        byte accel_address;
};

 #endif 
