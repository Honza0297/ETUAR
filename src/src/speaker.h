 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: speaker.h                               */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

#ifndef _SPEAKER_H
#define _SPEAKER_H  1


/* Vychozi pin reproduktoru */ 
#define SPEAKER_PIN 8

/* Noty */
const int ces = 245;
const int c = 262;
const int cis = 277;

const int des = cis;
const int d = 294;
const int dis =  311;

const int es = dis;
const int e = 330;
const int eis = 349;

const int fes = e;
const int f = eis;
const int fis = 370;

const int ges = fis;
const int g = 392;
const int gis = 415;

const int as = gis;
/* tzv. komorni a*/
const int a = 440;
const int ais = 466;


const int b = ais;

const int h = 494;

const int cesH = h;
const int cH = 523;
const int cisH = 554;

const int desH = cisH;
const int dH = 587;
const int disH = 622;

const int esH = disH;
const int eH = 659;
const int eisH = 698;

const int fesH = eH;
const int fH = eisH;
const int fisH = 740;

const int gesH = fisH;
const int gH = 784;
const int gisH = 831;

const int asH = gisH;
const int aH = 880;
const int aisH = 932;


/**
 * Trida pro ovladani reproduktoru 
 * */
class Speaker
{
    public:
        /**
         * Konsturktor.  Priradi pin konkretni instanici reproduktoru a vypne ho.
         * */       
        Speaker(int pin = SPEAKER_PIN);
        /**
         * Zahraje imperial march ze Star Wars jako ukazku. 
         * Funkce inspirovana zde: https://gist.github.com/nicksort/4736535
         * */ 
        void imperial_march();
        /**
         * Zapne reproduktor. Pri zapnutem reproduktoru, ktery nehraje zadny ton, se 
         * ozyva neprijemny zvuk.
         * */
        void enable();
        /**
         * Vypne mikrofon. Doporucuje se volat pokazde, kdyz neni reproduktor aktivne pouzivan
         * */
        void disable();
        /**
         * Funkce pro jednodussi zahrani noty. 
         * Prejato z  https://gist.github.com/nicksort/4736535
         * */
        void beep(int note, int duration);

    protected:
        /**
         * Pin, na kterem je pripojena konkretni instance reproduktoru.
         * */
        int speaker_pin;
};

#endif

