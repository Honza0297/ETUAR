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
#define STEPS_ONE_CHANNEL (int) STEPS_AB/4


/*
* Macros for setting units into move function
*/
#define DEG 0
#define CM 1

#define MOTOR_BAUDRATE 9600

#define STOP_BYTE 0x00
//Wheel circuit (prumer)
#define WHEEL_CIRCUIT 27.9

void init_motors();
/*
* Function to move motors.
* Param description:
*/
void move(int value, int speed);

void move(int speed);

void turn(int angle, int speed);

void turn_left(int speed);

void turn_right(int speed);

void circle(int diameter);

void stop();
 #endif