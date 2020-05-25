 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: hcsr04.h                                */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#ifndef _HCSR04_H
#define _HCSR04_H 1

/* Triger a echo pin */
#define TRIGGER_PIN 24
#define ECHO_PIN 26


/**
 * @brief Trida pro ovlaani ultrazvukoveho senzoru HC-SR04 
 * */
class HCSR04
{
    public:
        /**
         * Konstruktor
         * */
        HCSR04();
        /**
         * @brief Vrati namerenou dobu od odeslani vlny po jeji navrat v mikrosekundach
         * */
        long get_microseconds();
        /**
         * @brief Funkce vrati vzdalenost objektu v centimetrech
         * */
        long get_distance();
        /**
         * @brief Kostra funkce pro doplneni v tutorialu.
         * 
         * @return Namerena vzdalenost
         * */
        long zmer_vzdalenost();
    private:
};
/**
 * Konverzni konstanta pro prevod ms -> cm
 * What is this constant?
 * 
 * Well, hcsr04_get_micros() returns microseconds, but we need centimeters in hcsr04_get_cm(). How to do that?
 * Speed of sound in air (20 °C) is 343 m/s, which is 34300 cm/s, which is 0.0343 cm/us. This value has to be divided by 2, 
 * because the echo duration is the time sound needs to go both directions -> the final constant is 0.01715.
 * Now, the only think we have to do is multiply the echo value by this constant. 
 *
 */
#define ECHO_CONSTANT 0.01715

#endif