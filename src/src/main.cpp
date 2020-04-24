#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <math.h>

#include "motors.h"
#include "srf08.h"

#include "gyroscope.h"

#include "sharp1994v0.h"
#include "hcsr04.h"
#include "display.h"
#include "speaker.h"

#include "accelerometer.h"
#include "magnetometer.h"
#include "ahrs.h"

#include "additional/TimerThree.h"


#include "vectors.h"


/* Zda se bude pouzivat 20 Hz podsmycka v loop */
#define WITH_20HZ_LOOP true
/* Zda se bude pouzivat AHRS */
#define WITH_AHRS WITH_20HZ_LOOP && false

/* Funkce pro nastaveni preruseni pri 20 Hz smycce*/
volatile bool isTime = false;
void periodic_interrupt_handler()
{
  isTime=true;
}   

Display *display;
Speaker *speaker;

Motors *motors;

HCSR04 *hcsr04;
Sharp *sharp;
SRF08 *srf08;


Gyroscope *gyro;
Accelerometer *accel;
Magnetometer *mag;

AHRS *ahrs;

void setup() {
  /* Zahajeni komunikace po Seriove lince a I2C*/
  Serial.begin(9600);
  Wire.begin();
  
  /* Prvotni nastaveni vsech komponent */
  display = new Display();
  speaker = new Speaker();

  motors = new Motors();

  hcsr04 = new HCSR04();  
  sharp = new Sharp();
  srf08 = new SRF08();


  gyro = new Gyroscope();
  accel = new Accelerometer();
  mag = new Magnetometer(accel);

  
  /* Pokud budeme pouzivat 20Hz smycku, nastavi se i to*/
  if(WITH_20HZ_LOOP)
  {
    Timer3.initialize(50000); // = 0.05 s =+- 20 Hz
    Timer3.attachInterrupt(periodic_interrupt_handler);

    /* Pokud budeme pouzivat AHRS, nastavi se */
    if(WITH_AHRS)
    {
      ahrs = new AHRS(gyro, accel, mag);
    }
  }  
  
} /* konec setup() */


void loop()
{
  /*********************************/
  /*******MISTO PRO VAS KOD*********/
  /*********************************/



 /**
  * Vse v teto casti programu ma byt vykonavano pravidelne pri +-20 Hz
  * Pokud je loop() prilis dlouhy, neni 20 Hz garantovano! 
  * */ 
 if(isTime)
 {
  isTime = false;
 } /*Konec isTime*/
} /* konec loop() */
