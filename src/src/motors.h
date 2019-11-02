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


/*
* Macros for setting th direction
*/
#define LEFT -1
#define BOTH 0
#define RIGHT 1

/*
* Macros for setting units into move function
*/
#define DEG 0
#define CM 1

//Wheel circuit (prumer)
#define WHEEL_CIRCUIT 27.9

/*
* Macros for setting direction
*/
#define DIR_BACK 0 
#define DIR_FORW 1 

/*
* Macros for setting velocity in percent
* - only additional for specified velocity, other values are intended to be typed explicitly. 
*/
#define VEL_NONE 0
#define VEL_HALF 50
#define VEL_FULL 100
 
/*
* Internal function, sets encoder rotation counter.
*/
void set_counter(int dir);
/*
* Internal function for comparing two values with tolerance (equivalent to abs(a-b) < tolerance)
*/
bool is_equal(int a, int b);

/*
* Internal function, implements active waiting until motors are done
*/
void wait_until_done(int motor, int steps);

/*
* Internal function which executes move (really sends signals).
*/
void execute_move(int motor, int steps, int velocity);

/*
* Function to move motors.
* Param description:
*   wheel: choose wheel (LEFT, RIGHT, BOTH)
*   unit: better "mode": setting if motors will move in cm or turn by degree
*   value: apropriate value
*   dir: direction of move: forward or backward.
*   velocity: speed of move in percent 0-100, very low values are not suggested.
*/
int move(int wheel, int unit, int value, int dir, int velocity);



 #endif