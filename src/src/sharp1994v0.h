 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: sharp1994v0.h                           */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* Function prorotypes for controlling distance   */
 /* analog sensor sharp1994.                       */
 /**************************************************/

#ifndef _SHARP1994V0_H
#define _SHARP1994V0_H 1

// maximum value from analogRead() function
#define ANALOG_MAX  1024.

//default analog voltage. When using 3.3V board (some Arduino types), set value to 3.3
#define DEFAULT_VOLTAGE  5

//To what pin is sensor connected
#define SHARP_PIN A0



/*
Aprocimates value from analogRead() function by linear spline. 
Points estimated from referencial characteristics in sharp documentation [0]
[0] TODO link to documentation

limits(cm)    Function ( l = distance, v = voltage from <0,3> V, which is max voltage of sharp1994)
                l = a - b*v 
(0-3            l = -2.63 + 1.88v) 
3-2.3           l = 11.57 - 2.86v
2.3-1.75        l = 13.36 - 3.64v
1.75-1.4        l = 17.00 - 5.71v
1.4-1.1         l = 23.00 - 10.0v
1.1-0.8         l = 26.67 - 13.33v
0.8-0.65        l = 37.33 - 26.67v
0.65-0.42       l = 48.26 - 43.48v
0.42-0.00       l = 65.00 - 83.33v

The first row is for distance 0-3 cm, unused in this project because i cannot 
find out if it is under 3 or over 3 centimeters in certain situations (measurement
starts after the object is placed etc.). Additionally, sensor minimal recommended 
distance is 3 cm. 


Reason for linear splines: characteristics is very difficult to aproximate by a single function
and available aproxiamtions were very difficult to compute on such a weak MCU.
Return value: distance in cm or 0 if vale is < 0. 
*/
float aproximate(float value);

/*
* Function analog reads vlaue on pin set by SHARP_PIN and normalizes it
* to interval <0, DEFAULT_VOLTAGE>.
* Return value: normalized value 
*/
float get_distance_sharp();

#endif