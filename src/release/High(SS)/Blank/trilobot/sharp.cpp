 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: sharp1994v0.cpp                         */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /**************************************************/

#include <Arduino.h>
#include "sharp.h"


/* 
* Arrays limits, a and b are tabelated values for linear spline
* computed by aproximate() function.
*/
float limits[8] = {2.3,  1.75,    1.4,   1.1,   0.8,  0.65,  0.42,   0.0};
float a[8] = {11.57,  13.36,  17.00, 23.00, 26.67, 37.33, 48.26, 65.00};
float b[8] = { 2.86,   3.64,   5.71,  10.0, 13.33, 26.67, 43.48, 83.33};


float Sharp::get_distance()
{
    int value = analogRead(SHARP_PIN);
    float normalized_value = (value/ANALOG_MAX)*DEFAULT_VOLTAGE;
    return this->approximate(normalized_value);
}

float Sharp::approximate(float v)
{
    int i = 0;
    if(v < 0)
        return 0.;
    while(i < 8)
    {
        if(v < limits[i])
        {
            i++;
        }
        else
        {
            break;
        }
    }
    return a[i] - (b[i] * v);
}

float Sharp::zmer_vzdalenost()
{
/*TODO: 
 * precist hodnotu na SHARP_PIN
 * ziskanou hodnotu prevest do rozsahu 0-5
 * Pomoci funkce this->aproximate ziskat hodnotu v cm a vratit ji
  */
  float approximated_value = 0;
  return approximated_value;
}