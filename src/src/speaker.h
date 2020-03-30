#ifndef _SPEAKER_H
#define _SPEAKER_H  1


//default speaker pin
#define SPEAKER_PIN 8

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



class Speaker
{
    public:        
        Speaker(int pin = SPEAKER_PIN);
        void imperial_march();
        void enable();
        void disable();
        void beep(int note, int duration);

    protected:
        int speaker_pin;
};

#endif

