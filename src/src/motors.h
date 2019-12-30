 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  File: sharp1994v0.h                           */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /* This file is a part of authors bachelor thesis */
 /*                                                */
 /* Function prorotypes for motor controlling      */
 /**************************************************/
//TODO:
// Funkce pro jezdeni v kruhu o danem polomeru/prumeru? 
// Lepsi funkce pro zastaveni - skutecne odecitat hodnoty z enkoderu a nastavit takova napeti, aby kola nemela ani snahu se otacet
// Zkontrolovat funkci wait until done - co dela v situaci, kdy jeden motor je už na miste, ale druhy jeste ne? 
//   |-> mela by provest opravu a pockat, dokud to pomalejsi motor nedozene...
// vymyslet lepsi jmeno pro execute_move
 #ifndef _MOTORS_H
 #define _MOTORS_H       1

#define STEPS_AB 3072
#define STEPS_ONE_CHANNEL 768
/*
* Macros for setting the direction
*/
//#define LEFT -1
#define BOTH 0
//#define RIGHT 1

/*
* Macros for setting units into move function
*/
#define DEG 0
#define CM 1

//Wheel circuit (prumer)
#define WHEEL_CIRCUIT 27.9

typedef enum {
    FORWARD, 
    STOP, 
    BACKWARD,
    LEFT, 
    RIGHT
} direction;

/*
* Macros for setting direction
*/
#define DIR_BACK BACKWARD 
#define DIR_FORW FORWARD

/*
* Macros for setting velocity in percent
* - only additional for specified velocity, other values are intended to be typed explicitly. 
*/
#define VEL_NONE 0
#define VEL_HALF 50
#define VEL_FULL 100


void init_motors();
void stop(int motor);

/*
* Function to move motors.
* Param description:
*   value: apropriate value
*   direction: direction of move: forward or backward.
*   velocity: speed of move in percent 0-100, very low values are not suggested.
*/
void move(int value, direction direction, int velocity);

void turn(int side, int angle);

 #endif