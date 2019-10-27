 #ifndef _MOTORS_H
 #define _MOTORS_H       1

#define LEFT -1
#define BOTH 0
#define RIGHT 1
/*
* Macros for setting units into move function
*/
#define DEG 0
#define CM 1

//Wheel circuit
#define WHEEL_CIRCUIT 27.9

#define DIR_BACK 0 
#define DIR_FORW 1 

#define VEL_NONE 0
#define VEL_HALF 50
#define VEL_FULL 100
 

void set_counter(int dir);
bool is_equal(int a, int b);
void wait_until_done(int motor, int steps);
void execute_move(int motor, int steps, int velocity);
int move(int wheel, int unit, int value, int dir, int velocity);



 #endif