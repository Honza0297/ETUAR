 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: srf08.h                                 */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* This file contains macros and function         */
 /* prototypes for controlling srf-08 ligh         */
 /* and distance sensor.                           */
 /**************************************************/
 
 #ifndef _SRF08_H
 #define _SRF08_H       1

/*
* Vychozi I2C adresa
*/
#define SRF08_ADDRESS 0x70

/*
* Makra pro nastaveni vzdalenosti
*/
#define INCH 0x50
#define CM 0x51
#define MS 0x52
 
 /*
 * Makra pro pristup k nekterym registrum
 */ 
#define REG_CMD 0x00
#define REG_LIGH 0x01


/**
 * @brief Trida pro ovladani ultrazvukoveho cidla vzdalenosti SRF-08
 * */
class SRF08
{
    public:
        /**
         * @brief Konstruktor. 
         * */
        SRF08();
        /**
        * @brief Funkce ziska vzdalenost ze senzoru SRF-08
        * @return Vzdalenost v pozadovane jednotce nebo -1 pri problemu
        */
        int get_distance(byte unit = CM);
        /**
        * @brief Funkce ziska intenzitu svetla ze senzoru SRF-08.
        * @return Intenzita svetla v rozsahu 0-255.
        */
        byte get_light_intensity();
        /**
         * @brief Kostra funkce pro doplneni behem tutorialu.
         * 
         * @return Intenzitu svetla v intervalu 0-255
         *  */
        byte zmer_svetlo(); 
        /**
         * @brief Kostra pro doplneni
         * 
         * @return Namerena vzdalenost
         * */
        int zmer_vzdalenost();
    private:
        /**
        * @brief Funkce nastavuje mereni pomoci zapisu pozdadovane jednotky do REG_CMD.
        */
        void set_measurement(byte unit = CM);
};

#endif
