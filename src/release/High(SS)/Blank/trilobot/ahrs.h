 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: ahrs.h                                  */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/
#ifndef _AHRS_H
#define _AHRS_H       1

#include "vectors.h"
#include "accelerometer.h"
#include "magnetometer.h"
#include "gyroscope.h"

/* K a AlPHA jsou konstanty pro komplementarni filtr */
#define K 0.02 //0.02
#define ALPHA 0.025 //0.025

/* Makra pro snazsi prevod mezi stupni a radiany */
#define TO_DEG(x) x*180/PI
#define TO_RAD(x) x*PI/180

/**
 *  @brief Trida AHRS predstavuje referencni system polohy a smeru zalozeny na senzoru minIMU-v3. 
 *  Teoreticka funkcionalita komplementarniho filtru byla inspirovana bakalarskou praci  Julie Rakovcove:
 *  https://dspace5.zcu.cz/bitstream/11025/23776/1/BP_Rakovcova.pdf, implemetaci zajistoval autor. 
 * */
class AHRS 
{
    public:
        /**
        * @brief Konstruktor. Nastavuje eulerovy uhly na 0,0,0
        * 
        * @param gyro Pouzity gyroskop.
        * @param accel Pouzity kcelerometr,
        * @param mag Pouzity magnetometr
        * */ 
        AHRS(Gyroscope *gyro, Accelerometer *accel, Magnetometer *mag);
        /**
        * @brief Funkce vraci eulerovy uhly, tedy naklon senzoru. Slozky vektoru x,y,z odpovidaji roll, pitch, yaw.
        * */
        vector<float> get_euler_angles();
        /**
         * @brief Funkce aktualizuje soucasny naklon robota pomoci aplikace komplementarniho filtru:
         *  GYRO       -> kvaterniony   -> eulerovy uhly -
         *                                                | -> komplementarni filtr -> konecne eulerovy uhly
         * ACC + MAG   -> dolni propust -> eulerovy uhly -    
         * 
         *  @note podrobneji v textu tutorialu. Implementacni detaily vysvetleny v ahrs.cpp
         * */
        void update_euler_angles();
    private:
        /** @brief Gyroskop pro ziskavani gyroskopickeho odhadu polohy. */
        Gyroscope *gyro;
        /** @brief Akcelerometr a magnetometr pro akcelerometricky odhad polohy. */
        Accelerometer *accel;
        Magnetometer *mag;
        /** @brief Aktualni naklon robota */
        vector<float> euler_angles;
};

 #endif 
 