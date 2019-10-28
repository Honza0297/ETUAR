#include <Arduino.h>
#include "sharp1994v0.h"

float limits[8] = {2.3,  1.75,    1.4,   1.1,   0.8,  0.65,  0.42,   0.0};
float a[8] = {11.57,  13.36,  17.00, 23.00, 26.67, 37.33, 48.26, 65.00};
float b[8] = { 2.86,   3.64,   5.71,  10.0, 13.33, 26.67, 43.48, 83.33};

//TODO
float get_distance_sharp()
{
    int value = analogRead(SHARP_PIN);
    float normalized_value = (value/ANALOG_MAX)*DEFAULT_VOLTAGE;
    return aproximate(normalized_value);

}

float aproximate(float v)
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