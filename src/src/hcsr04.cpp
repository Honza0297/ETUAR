
#include <Arduino.h>
#include "hcsr04.h"


void hcsr04_init()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIGGER_PIN, LOW);
}


long hcsr04_get_micros()
{
    long echo = 0;
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

long hcsr04_get_cm()
{
    long echo = hcsr04_get_micros();
    return echo*ECHO_CONSTANT;
}