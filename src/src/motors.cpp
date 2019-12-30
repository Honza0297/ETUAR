#include <Arduino.h>
#include "motors.h"

#define MOTOR_RIGHT 7
#define MOTOR_LEFT 6

//extern int motor_right;
//extern int motor_left;
byte left_A = 2;
byte right_A = 3;

byte left_B = 53;
byte right_B = 52;

volatile int voltage_left = 110;
volatile int voltage_right = 110;
direction dir = STOP;
volatile bool stop_OK = true;

volatile int steps_right = 0;
volatile int steps_left = 0;

void init_motors()
{
  steps_right = 0;
  steps_left = 0;
  pinMode(left_A, INPUT);
  pinMode(left_B, INPUT);
  pinMode(right_A, INPUT);
  pinMode(right_B, INPUT);
  /*Calibrating motors to stop*/
  dir = BACKWARD;
  stop_OK = false;
  analogWrite(MOTOR_LEFT, voltage_left);
  analogWrite(MOTOR_RIGHT, voltage_right);
  stop(BOTH);
}
void motor_left_interrupt_handler()
{
  stop_OK = false;
  if(dir == FORWARD)
  {
    voltage_left--;
  }
  else
  {
    voltage_left++;
  }

}

void motor_right_interrupt_handler()
{
  stop_OK = false;
  if(dir == FORWARD)
  {
    voltage_right--;
  }
  else
  {
    voltage_right++;
  }
}
void attach_interrupts()
{

  attachInterrupt(digitalPinToInterrupt(left_A), motor_left_interrupt_handler, RISING);
  attachInterrupt(digitalPinToInterrupt(right_A), motor_right_interrupt_handler, RISING);
}

void detach_interrupts()
{
  detachInterrupt(digitalPinToInterrupt(left_A));
  detachInterrupt(digitalPinToInterrupt(right_A));
}

void apply_ATV_constant(int motor)
{
  int ATV_constant = 2;
  switch(motor)
  {
    case BOTH:
        voltage_left += dir == FORWARD ? -ATV_constant : ATV_constant;
        voltage_right += dir == FORWARD ? -ATV_constant : ATV_constant;
      break;
    case LEFT:
      voltage_left += dir == FORWARD ? -ATV_constant : ATV_constant;
      break;
    case RIGHT:
      voltage_right += dir == FORWARD ? -ATV_constant : ATV_constant;
      break;
    default:
      break;
  }
  analogWrite(MOTOR_LEFT, voltage_left);
  analogWrite(MOTOR_RIGHT, voltage_right);
}
void stop(int motor)
{
  if(dir == STOP)
    return;
  attach_interrupts(); 
  switch(motor)
  {
    case LEFT:
      while(42)
      {
        stop_OK = true;
        analogWrite(MOTOR_LEFT, voltage_left);
        delay(50);
        if(stop_OK)
        {
          break;
        }
      }
    break;
    case RIGHT:
      while(42)
      {
        stop_OK = true;
        analogWrite(MOTOR_RIGHT, voltage_right);
        delay(50);
        if(stop_OK)
        {
          break;
        }
      }
      break;
    case BOTH:
      while(42)
      {
        stop_OK = true;
        analogWrite(MOTOR_LEFT, voltage_left);
        analogWrite(MOTOR_RIGHT, voltage_right);
        delay(50);
        if(stop_OK == true)
        {
          break;
        }
      }
    break;
    default:
    break;
  }
  apply_ATV_constant(motor);
  dir = STOP;
  detach_interrupts();
  return;
}
/*
void _set_counter(int dir)
{
  if(dir == RIGHT || dir == BOTH)
  {
    counter_right = 0;
  }
  if (dir == LEFT || dir == BOTH)
  {
    counter_left = 0; 
  }
}
bool is_equal(int a, int b)
{
  if(abs(a-b) < 20) 
    return true; 
  else
    return false ; //quite big tolerance
}
void wait_until_done(int motor, int steps)
{
    int A_old_left = 0;
    int B_old_left = 0;
    int A_new_left = 0;
    int B_new_left = 0;
    int A_old_right = 0;
    int B_old_right = 0;
    int A_new_right = 0;
    int B_new_right = 0;

 if(motor == RIGHT)
 {
  while(!is_equal(counter_right, steps))
  {
    A_new_right = digitalRead(50);
    B_new_right = digitalRead(52);
    if(A_new_right != A_old_right || B_new_right != B_old_right)
    {
      A_old_right = A_new_right;
      B_old_right = B_new_right;
      counter_right++;
    }
  }
 }
 else if (motor == LEFT)
 {
    while(counter_left != steps)
    {
      A_new_left = digitalRead(51);
      B_new_left = digitalRead(53);
      if(A_new_left != A_old_left || B_new_left != B_old_left)
      {
        A_old_left = A_new_left;
        B_old_left = B_new_left;
        counter_left++;
      }
    }
 }
 else if (motor == BOTH)
 {
  while(counter_right != steps || counter_right != steps)
  {
    A_new_right = digitalRead(50);
    B_new_right = digitalRead(52);
    A_new_left = digitalRead(51);
    B_new_left = digitalRead(53);
    if(A_new_right != A_old_right || B_new_right != B_old_right)
    {
      A_old_right = A_new_right;
      B_old_right = B_new_right;
      counter_right++;
    }
    if(A_new_left != A_old_left || B_new_left != B_old_left)
     {
       A_old_left = A_new_left;
       B_old_left = B_new_left;
       counter_left++;
     }
  }
 }
 return;
}
void execute_move(int motor, int steps, int velocity)
{
  switch(motor){
    case BOTH:
      _set_counter(BOTH); 
      analogWrite(motor_right, velocity);
      analogWrite(motor_left, velocity);
      wait_until_done(BOTH, steps);
      analogWrite(;motor_right, 145);
      analogWrite(motor_left, 145);
      _set_counter(BOTH);
      break;
    case RIGHT:
      _set_counter(RIGHT);   
      analogWrite(motor_right, velocity);
      wait_until_done(RIGHT, steps);
      analogWrite(motor_right, 145);
      _set_counter(RIGHT);
      break;
    case LEFT:
     _set_counter(LEFT);
     analogWrite(motor_left, velocity);
     wait_until_done(LEFT, steps);
     analogWrite(motor_left, 145);
     _set_counter(LEFT);
     break;
    default:
      break;
  }
  return;
}
*/
void motor_right_interrupt_handler_move()
{
  steps_right++;
}

void motor_left_interrupt_handler_move()
{
  steps_left++;
}

void attach_interrupts_move()
{
 attachInterrupt(digitalPinToInterrupt(right_A), motor_right_interrupt_handler_move, RISING);
 attachInterrupt(digitalPinToInterrupt(left_A), motor_left_interrupt_handler_move, RISING);
}

void detach_interrupts_move()
{
 detachInterrupt(digitalPinToInterrupt(MOTOR_LEFT));
 detachInterrupt(digitalPinToInterrupt(MOTOR_RIGHT));
}


void turn(int side, int angle)
{
  int steps = (int) ((40 * PI * angle / 360) / WHEEL_CIRCUIT * STEPS_ONE_CHANNEL);
  attach_interrupts_move();
  
  if(side == RIGHT)
  {
    voltage_right = 210;
    dir = side;
    analogWrite(MOTOR_RIGHT, voltage_right);
    while(1)
    {
      if(steps == steps_right)
      {
        break;
      }
    }
    stop(RIGHT);
    steps_right = 0;
  }
  else if (side == LEFT)
  {
    voltage_left = 210;
    dir = side;
    analogWrite(MOTOR_LEFT, voltage_left);
    while(1)
    {
      if(steps == steps_left)
      {
        break;
      }
    }
    stop(LEFT);
    steps_left = 0;
  }  
  else
  {
   /*Do nothing*/
  }

  
  
  
}

void move(int value, direction direction, int velocity)
{
  dir = direction; /*Set global variable*/
  int steps = (int) (value / WHEEL_CIRCUIT * STEPS_ONE_CHANNEL);  /*Compute steps needed to reach destination*/     
  
  /*Set voltage - inaccurate because real middle/stop value is different (+- 10)*/
  int voltage = 127; 
  if(dir == FORWARD)
  {
    voltage += (int) (velocity / 100. * 127);  //dot to force float division
  }
  else if (dir == BACKWARD)
  {
    voltage -= (int)(velocity / 100. * 127);
  }
  voltage_left = voltage;
  voltage_right = voltage;
  
  /*Attach interrupts for move feedback and start move*/
  attach_interrupts_move();
  analogWrite(MOTOR_LEFT, voltage_left);
  analogWrite(MOTOR_RIGHT, voltage_right);
  Serial.println(steps);

  /*
    Moving cycle. 
    Maybe it can seem strange, but here the interrupt comes! 
    They change the values of steps_left and steps_right until the movement is done.
  */
  while(1)
  {
    if(steps == steps_left || steps == steps_right)
    {
      break;
    }
  }

  /*detaching interrupts*/
  detach_interrupts_move();
  Serial.println("Move finished");

  /*Stop the motors*/
  stop(BOTH);

  /*Zeroing interrupt counters for next use.*/
  steps_left = 0;
  steps_right = 0;

  return;
}
