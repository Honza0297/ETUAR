 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: motors.h                                */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/

//TODO:
// Funkce pro jezdeni v kruhu o danem polomeru/prumeru? 
 #ifndef _MOTORS_H
 #define _MOTORS_H       1

/* Pocet kroku enkoderu pri vyuziti obou kanalu */
#define STEPS_AB 3072
/* Pocet kroku enkoderu pri pouziti jednoho kanalu */
#define STEPS_ONE_CHANNEL (int) STEPS_AB/4

/* Rychlost prenosu po seriove lince pro ovladani motoru */
#define MOTOR_BAUDRATE 9600

/* Zastavujici byte */
#define STOP_BYTE 0x00

/* Obvod hnanych kol robota */
#define WHEEL_CIRCUIT 27.9

/* Piny pro kanaly enkoderu */
#define LEFT_A 2
#define LEFT_B 53

#define RIGHT_A 3
#define RIGHT_B 52

/**
 * Trida Motors slouzi pro ovladani motoru pomoci Sabertooth 2x5
*/
class Motors
{
    public:
        /**
         *  Konstruktor. Zahaji komunikaci po Seriove lince, nastavi spravny pinMode pro piny ekonderu
         *  a nastavi promenne steps_left a steps_right na nulu.
        */
        Motors();
        /**
         *  Funkce slouzi pro pohyb robota rovne. Pro pohyb dozadu staci nastavit zapornou hodnotu rychlosti NEBO vzdalenosti.  
         * @param distance vzdalenost v cm
         * @param speed rychlost v procentech
         */
        void move(int distance, int speed);
        /**
         * Funkce pro pohyb dopredu bez zastaveni.
         * @param speed rychlost pohybu
         */
        void move(int speed);
        /**
         * Funkce slouzici pro zataceni. Pro zataceni doprava zadavejte kladny, pro zataceni doleva zaporny uhel. 
         * @param angle uhel pro zatoceni ve stupnich
         * @param speed rychlost v procentech
         */ 
        void turn(int angle, int speed);
        /**
         * Funkce pro jezdeni do kruhu o danem polomeru 
         * @param diameter polomer kruhu v cm, pocitano od vnejsiho kola do stredu otaceni. 
         * @param counterclokwise pokud je true, otaceni probiha proti smeru hodinovych rucicek, jinak po smeru
         */
        void circle(int diameter, bool counterclokwise=false);
        /**
         * Funkce vrati rychlost ve spravnem rozsahu z procentualniho vyjadreni rychlosti
         * @param speed rychlost v procentech
         */ 
        static byte get_speed_from_percentage(int speed);
        /**
         * Funkce zastavi oba motory
         * */
        void stop();
    private:
        /**
         * Funkce pro nekonecne zataceni doleva.
         * */
        void turn_left(int speed);
        /**
         * Funkce pro nekonecne zataceni doprava.
         * */
        void turn_right(int speed);   
};
 #endif