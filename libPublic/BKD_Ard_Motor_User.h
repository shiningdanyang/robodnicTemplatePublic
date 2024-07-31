/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_MOTOR_USER_H_
#define INC_BKD_ARD_MOTOR_USER_H_
#include "Arduino.h"
#define R_PWM1  11
#define L_PWM1  12
#define R_PWM2  9
#define L_PWM2  10
#define R_PWM3  7
#define L_PWM3  8
#define R_PWM4  6
#define L_PWM4  5

int speedMode    = 1;
int runSpeed1    = 70;/////////////////////////////////////////////
int rotSpeed1    = 40;
int runSpeed2    = 115;////////////////////////////////////////////
int rotSpeed2    = 50;
int runSpeed3    = 160;////////////////////////////////////////////
int rotSpeed3    = 60;

#endif /* INC_BKD_MOTOR_PREDEF_H_ */
