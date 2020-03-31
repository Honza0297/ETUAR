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


#include "additional/LiquidCrystal_I2C.h"
#define DISPLAY_ENABLE true

/* Adresa displeje muze byt ruzna TODO */
#define DISPLAY_ADDRESS_PRIMARY 0x3F
#define DISPLAY_ADDRESS_FALLBACK 0x20 //nebo cokoli 0x20 az 0x27
#define DISPLAY_ADDRESS  DISPLAY_ADDRESS_PRIMARY

class Display
{
    public:
        Display();
        template <typename T> void print_first_line(T to_print);
        template <typename T> void print_second_line(T to_print);
        void clear();
    private:
        LiquidCrystal_I2C *display;
};

#endif