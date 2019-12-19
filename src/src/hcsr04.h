#ifndef _HCSR04_H
#define _HCSR04_H 1

#define TRIGGER_PIN 24
#define ECHO_PIN 26

/*
 * What is this constant?
 * 
 * Well, hcsr04_get_micros() returns microseconds, but we need centimeters in hcsr04_get_cm(). How to do that?
 * Speed of sound in air (20 °C) is 343 m/s, which is 34300 cm/s, which is 0.0343 cm/us. This value has to be divided by 2, 
 * because the echo duration is the time sound needs to go both directions -> the final constant is 0.01715.
 * Now, the only think we have to do is multiply the echo value by this constant. 
 *
 */
#define ECHO_CONSTANT 0.01715
void hcsr04_init();



long hcsr04_get_micros();


long hcsr04_get_cm();


#endif