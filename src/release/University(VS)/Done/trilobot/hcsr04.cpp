 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: hcsr04.cpp                              */
 /*  Author: Jan Beran                             */
 /*  Date: March 2020                              */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/
#include <Arduino.h>
#include "hcsr04.h"


HCSR04::HCSR04()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIGGER_PIN, LOW);
}

long HCSR04::get_microseconds()
{
    long echo =  0;
    //this is only for sure - we wrote  LOW to TRIGGER_PIN in init, but anything could happen. This gives us certain state.  
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    //We set TRIGGER_PIN to HIGH for 5 microseconds, which is signal for HC-SR04 to measure and send data
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIGGER_PIN, LOW);

    //pulseIn gets the 
    echo = pulseIn(ECHO_PIN, HIGH);
    return echo;
}

long HCSR04::get_distance()
{
    long echo = this->get_microseconds();
    return echo*ECHO_CONSTANT;
}

long HCSR04::zmer_vzdalenost()
{/* Pro jistotu na chvili nastavime stav LOW */
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    
    long echo = pulseIn(ECHO_PIN, HIGH);
    long return_value = echo * 0.0343;
    return return_value;
}