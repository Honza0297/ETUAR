#include <Arduino.h>
#include "motors.h"

/*TODO presun do hlavickoveho souboru a udelat makra*/
byte left_A = 2;
byte right_A = 3;

byte left_B = 53;
byte right_B = 52;

volatile int steps_right = 0;
volatile int steps_left = 0;

byte get_speed_from_percentage(int speed);

void motor_right_interrupt_handler();
void motor_left_interrupt_handlere();
void attach_interrupts();
void detach_interrupts();



void init_motors()
{
  pinMode(left_A, INPUT);
  pinMode(left_B, INPUT);
  pinMode(right_A, INPUT);
  pinMode(right_B, INPUT);

  Serial1.begin(MOTOR_BAUDRATE);
  stop();
}

void move(int value, int speed)
{
  /*Pokud je vzdalenost zaporna, upravime do ocekavaneho vstupu*/
  if(value < 0)
  {
    value *= -1;
    speed *= -1;
  }
  int steps_to_go = (int)(value/WHEEL_CIRCUIT*STEPS_ONE_CHANNEL);
  attach_interrupts();
  move(speed);
  while(1)
  {
    if(steps_left == steps_to_go || steps_right == steps_to_go) 
      break;
  }
  stop();
  detach_interrupts();

}

void move(int speed)
{
  byte control_byte = get_speed_from_percentage(speed);
  Serial1.write(control_byte);
  Serial1.write(control_byte+127); 
}

void turn(int angle, int speed)
{
  int steps_to_go = (int) ((40 * PI * angle / 360) / WHEEL_CIRCUIT * STEPS_ONE_CHANNEL);
  attach_interrupts();
  
  if(angle > 0)
    turn_right(speed);
  else if(angle < 0)
    turn_left(speed);

  while(1)
  {
    if(steps_left == steps_to_go || steps_right == steps_to_go) 
      break;
  }
  stop();
  detach_interrupts();
}

void turn_left(int speed)
{
  byte control_byte = get_speed_from_percentage(speed);
  Serial1.write(control_byte+127);
}

void turn_right(int speed)
{
  byte control_byte = get_speed_from_percentage(speed);
  Serial1.write(control_byte);
}

void circle(int diameter)
{
  /*TODO*/
  turn_right(90);
}

void stop()
{
  Serial1.write(STOP_BYTE);
}

byte get_speed_from_percentage(int speed)
{
  if(speed > 100 || speed < -100)
    return 0x00;

  byte control_byte = 0x00;
  
  /* Mezni hodnoty reseny explicitne. Zamezi se problemum
    typu round vs floor vs truncate*/
  switch(speed)
  {
    case -100:
      control_byte = 1;
      break;
    case 0:
      control_byte = 64;
      break;
    case 100:
      control_byte = 127;
      break;
    default:
      /*
       * normalizace do rozsahu 0-200 */
      speed += 100;
      /*truncate + 0.5 = round*/ 
      control_byte = (byte) (127./200*speed + 0.5); 
      break;
  }
  Serial.println(control_byte);
  return control_byte;
}




void motor_right_interrupt_handler()
{
  steps_right++;
}

void motor_left_interrupt_handler()
{
  steps_left++;
}

void attach_interrupts()
{
 attachInterrupt(digitalPinToInterrupt(right_A), motor_right_interrupt_handler, RISING);
 attachInterrupt(digitalPinToInterrupt(left_A), motor_left_interrupt_handler, RISING);
}

void detach_interrupts()
{
 detachInterrupt(digitalPinToInterrupt(left_A));
 detachInterrupt(digitalPinToInterrupt(right_A));
 steps_right = 0;
 steps_left = 0;
}