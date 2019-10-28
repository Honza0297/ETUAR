#ifndef _SHARP1994V0_H
#define _SHARP1994V0_H 1


#define ANALOG_MAX  1024.
#define DEFAULT_VOLTAGE  5
#define SHARP_PIN A0
/*
Function aproximated by linear spline
limits(cm)    Function ( l = distance, v = voltage from <0,3>)
                l = a - b*v !! it is MINUS
(0-3             l = -2.63 + 1.88v) - this is for distance 0-3 cm, unused in this project because i cannot 
                                    find out if it is under 3 or over 3 centimeters in certain situations (measurement
                                    starts after the object is placed etc.)
3-2.3           l = 11.57 - 2.86v
2.3-1.75        l = 13.36 - 3.64v
1.75-1.4        l = 17.00 - 5.71v
1.4-1.1         l = 23.00 - 10.0v
1.1-0.8         l = 26.67 - 13.33v
0.8-0.65        l = 37.33 - 26.67v
0.65-0.42       l = 48.26 - 43.48v
0.42-...        l = 65.00 - 83.33v
*/

float aproximate(float x);
float get_distance_sharp();

#endif