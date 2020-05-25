 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: sharp1994v0.h                           */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* Function prorotypes for controlling distance   */
 /* analog sensor sharp1994.                       */
 /**************************************************/



#ifndef _SHARP1994V0_H
#define _SHARP1994V0_H 1

/* maximum value pro analogRead() */
#define ANALOG_MAX  1024.

/* Vychozi napeti ve V. U nekterych jinych desek je to 3.3 V */
#define DEFAULT_VOLTAGE  5

/* Pin, ke kteremu je senzor pripojeny */
#define SHARP_PIN A0

/**
 * @brief Trida pro ovladani senzoru vzdalenosti Sharp
 * */
class Sharp
{
    public:
        /**
        * @brief Funkce precte hodnotu na pinu SHARP_PIN a normalizuje ji
        * do intervalu <0, DEFAULT_VOLTAGE>.
        * @return normalizovana hodnota. 
        * */
        float get_distance();

        /**
         * @brief Kostra pro doplneni
         * 
         * @return namerenou hodnotu ze senzoru SHARP
         * */
        float zmer_vzdalenost();
    private:
        /**
         * @brief Aproximuje vzdalenost objektu podle napeti na pinu SHARP_PIN pomoci linearniho splajnu.
         * body pro aproximaci jsou vycteny z dokumentace https://www.pololu.com/file/0J157/GP2D120-DATA-SHEET.pdf.

        limits(cm)    Function ( l = distance, v = voltage from <0,3> V, which is max voltage of sharp1994)
                        l = a - b*v 
        (0-3            l = -2.63 + 1.88v) 
        3-2.3           l = 11.57 - 2.86v
        2.3-1.75        l = 13.36 - 3.64v
        1.75-1.4        l = 17.00 - 5.71v
        1.4-1.1         l = 23.00 - 10.0v
        1.1-0.8         l = 26.67 - 13.33v
        0.8-0.65        l = 37.33 - 26.67v
        0.65-0.42       l = 48.26 - 43.48v
        0.42-0.00       l = 65.00 - 83.33v

        Prvni radek je pro vzdalenost 0-3 cm, ktery ale neni pouzity, jelikoz nelze
        rozhodnout, zda je vzdalenost pod 3 cm nebo nad 3 cm (dvema vzdalenostem odpovida stejne napeti).

        Duvod pro linearni splajn: Zadny z predpisu dohledatelnych na internetu ani pokusy o odhad funkcniho predpisu nedavaly
        prilis presne vysledky.
        */
        float approximate(float v);
};

#endif