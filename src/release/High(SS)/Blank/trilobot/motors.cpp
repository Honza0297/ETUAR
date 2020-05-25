 /************************************************ */
 /*  Educational tutorial for Arduino in robotics  */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice*/
 /*  File: motors.cpp                              */
 /*  Author: Jan Beran                             */
 /*  Date: autumn 2019                             */
 /*                                                */
 /* This file is a part of author´s bachelor thesis*/
 /*                                                */
 /**************************************************/


#include <Arduino.h>
#include "motors.h"

/**
 * Promenne nutne pro spravne fungovani preruseni.
 * */
volatile int steps_right = 0;
volatile int steps_left = 0;

/**
 * Prototypy funkci pro ovladani preruseni
 * */
void motor_right_interrupt_handler();
void motor_left_interrupt_handler();
void attach_interrupts();
void detach_interrupts();

Motors::Motors()
{
  pinMode(LEFT_A, INPUT);
  pinMode(LEFT_B, INPUT);
  pinMode(RIGHT_A, INPUT);
  pinMode(RIGHT_B, INPUT);

  Serial1.begin(MOTOR_BAUDRATE);
  this->stop();
  steps_left = 0;
  steps_right = 0;
}


byte Motors::get_speed_from_percentage(int speed)
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
      /* Normalizace do rozsahu 0-200 */
      speed += 100;
      /* truncate + 0.5 = round*/ 
      control_byte = (byte) (127./200*speed + 0.5); 
      break;
  }
  Serial.println(control_byte);
  return control_byte;
}

void Motors::move(int distance, int speed)
{
  /*Pokud je vzdalenost zaporna, upravime do ocekavaneho vstupu*/
  if(distance < 0)
  {
    distance *= -1;
    speed *= -1;
  }
  int steps_to_go = (int)(distance/WHEEL_CIRCUIT*STEPS_ONE_CHANNEL);
  attach_interrupts();
  this->move(speed);
  while(1)
  {
    if(steps_left == steps_to_go || steps_right == steps_to_go) 
      break;
  }
  this->stop();
  detach_interrupts();

}

void Motors::move(int speed)
{
  byte control_byte = get_speed_from_percentage(speed);
  Serial1.write(control_byte);
  Serial1.write(control_byte+127); 
}

void Motors::turn(int angle, int speed)
{
  int steps_to_go = (int) ((40 * PI * angle / 360) / WHEEL_CIRCUIT * STEPS_ONE_CHANNEL);
  attach_interrupts();
  
  if(angle > 0)
    this->turn_right(speed);
  else if(angle < 0)
    this->turn_left(speed);

  while(1)
  {
    if(steps_left == steps_to_go || steps_right == steps_to_go) 
      break;
  }
  this->stop();
  detach_interrupts();
}

void Motors::turn_left(int speed)
{
  byte control_byte = Motors::get_speed_from_percentage(speed);
  Serial1.write(control_byte+127);
}

void Motors::turn_right(int speed)
{
  byte control_byte = Motors::get_speed_from_percentage(speed);
  Serial1.write(control_byte);
}

void Motors::circle(int diameter, bool countercloockwise)
{
  /*TODO*/
  return;
}

void Motors::stop()
{
  Serial1.write(STOP_BYTE);
}

void Motors::jed_rovne(int distance, int speed)
{
  int steps_to_go = 0/*TODO potrebne kroky*/;
  byte driving_byte;
  driving_byte = Motors::get_speed_from_percentage(speed);
  attach_interrupts();
  /*TODO odeslat kontrolní bajt do obou motoru*/
  /*Toto si vysvetlime mimo kod*/
  while(1)
  {
    if(steps_left == steps_to_go ||
    steps_right == steps_to_go) 
      break;
  }
  /*TODO zastavit motory*/
  detach_interrupts();
}

void Motors::zatoc(int angle, int speed)
{
  int steps_to_go = 0/*TODO pocet kroku, ktere musime urazit */;
  attach_interrupts();
  byte driving_byte;
  driving_byte = Motors::get_speed_from_percentage(speed);
 /*TODO zatoceni podle znamenka u parametru angle*/

  while(1)
  {
    if(steps_left == steps_to_go ||
      steps_right == steps_to_go) 
      break;
  }
  /*TODO zastavit dany motor */
  detach_interrupts();
}


/************************************/
/* Funkce pro ovladni preruseni     */
/************************************/

/** @brief Funkce pro obsluhu preruseni z praveho motoru */
void motor_right_interrupt_handler()
{
  steps_right++;
}

/** @brief Funkce pro obsluhu preruseni z leveho motoru */
void motor_left_interrupt_handler()
{
  steps_left++;
}

/** @brief Funkce zapne preruseni na pinech enkoderu */
void attach_interrupts()
{
 attachInterrupt(digitalPinToInterrupt(RIGHT_A), motor_right_interrupt_handler, RISING);
 attachInterrupt(digitalPinToInterrupt(LEFT_A), motor_left_interrupt_handler, RISING);
}

/** @brief Funkce vypne preruseni na pinech enkoderu a vynuluje citaci poctu kroku. */
void detach_interrupts()
{
 detachInterrupt(digitalPinToInterrupt(LEFT_A));
 detachInterrupt(digitalPinToInterrupt(RIGHT_A));
 steps_right = 0;
 steps_left = 0;
}