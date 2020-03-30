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

 #ifndef _MOTORS_H
 #define _MOTORS_H       1

#define STEPS_AB 3072
#define STEPS_ONE_CHANNEL (int) STEPS_AB/4

#define MOTOR_BAUDRATE 9600

#define STOP_BYTE 0x00

//Wheel circuit (prumer)
#define WHEEL_CIRCUIT 27.9


#define LEFT_A 2
#define LEFT_B 53

#define RIGHT_A 3
#define RIGHT_B 52

class Motors
{
    public:
        Motors();
        void move(int distance, int speed);
        void move(int speed);
        void turn(int angle, int speed);
        void circle(int diameter);
        static byte get_speed_from_percentage(int speed);
        void stop();
    private:
        void turn_left(int speed);
        void turn_right(int speed);   
};
 #endif