 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: display.h                               */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#ifndef _DISPLAY16X2_H
#define _DISPLAY16X2_H  1


#include "LiquidCrystal_I2C.h"
#define DISPLAY_ENABLE true

/* Adresa displeje muze byt ruzna*/
#define DISPLAY_ADDRESS_PRIMARY 0x3F
#define DISPLAY_ADDRESS_FALLBACK 0x20 //nebo cokoli 0x20 az 0x27
#define DISPLAY_ADDRESS DISPLAY_ADDRESS_PRIMARY

/** 
 * @brief Trida/wrapper pro I2C displej.
 * Cilem je maximalni zjedndueni prace s displejemi za cenu velmi omezeneho vyuziti.
 * */
class Display
{
    public:
        /**
         *  @brief Inicializuje instanci LiquidCrystal_I2C displeje a pripravi ho k pouziti.
        */
        Display();
        /**
         * @brief Smaze prvni radek a vytiskne pozadovanou promennou.
         * Co je template? jednoducha pomucka z C++. Jelikoz chci tisknout X datovych typu, udelam si "sablonu",
         * diky ktere mohu vytisknout libovolny datovy typ (ktery podporuje i obaleny displej). 
         * */
        template <typename T> void print_first_line(const T to_print)
        {
            display->setCursor(0,0);
            display->print("                "); //emuluje smazani jednoho radku
            display->setCursor(0,0);
            display->print(to_print);
        }
        /**
         * @brief Smaze druhy radek a vytiskne pozadovanou promennou.
         * Co je template? jednoducha pomucka z C++. Jelikoz chci tisknout X datovych typu, udelam si "sablonu",
         * diky ktere mohu vytisknout libovolny datovy typ (ktery podporuje i obaleny displej). 
         * */
        template <typename T> void print_second_line(const T to_print)
        {
            display->setCursor(0,1);
            display->print("                "); //emuluje smazani jednoho radku
            display->setCursor(0,1);
            display->print(to_print);
        }
        /**
         * @brief Vymaze cely displej.
         * */
        void clear();
    private:
        /** Displej, ktery je touto tridou obalovan */
        LiquidCrystal_I2C *display;
};

#endif