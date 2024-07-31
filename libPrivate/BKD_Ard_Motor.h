/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_MOTOR_H_
#define INC_BKD_ARD_MOTOR_H_

#include "Arduino.h"
#include "../libPublic/BKD_Ard_Motor_User.h"

int runSpeed     = 100;
int rotateSpeed     = 20;

void motor1(int speed) {
#ifdef MECANUM
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0) {
    analogWrite(R_PWM1, abs(speed));
    digitalWrite(L_PWM1, 0);
  }
  else
  {
    digitalWrite(R_PWM1, 0);
    analogWrite(L_PWM1, abs(speed));
  }
#endif
}

void motor2(int speed) {
#ifdef MECANUM
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0)
  {
    analogWrite(R_PWM2, abs(speed));
    digitalWrite(L_PWM2, 0);
  }
  else
  {
    digitalWrite(R_PWM2, 0);
    analogWrite(L_PWM2, abs(speed));
  }
#endif
}

void motor3(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0)
  {
    analogWrite(R_PWM3, abs(speed));
    digitalWrite(L_PWM3, 0);
  }
  else
  {
    digitalWrite(R_PWM3, 0);
    analogWrite(L_PWM3, abs(speed));
  }
}

void motor4(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0)
  {
    analogWrite(R_PWM4, abs(speed));
    digitalWrite(L_PWM4, 0);
  }
  else
  {
    digitalWrite(R_PWM4, 0);
    analogWrite(L_PWM4, abs(speed));
  }
}

void motorShoot(int speed)
{
  if(speed > 230)
  {
    speed = 230;
  }
  if (speed < -230)
  {
    speed = -230;
  }
  analogWrite(pwmMotorShoot, 255 - abs(speed));
  digitalWrite(dirMotorShoot, 0);
}

void testMotor()
{
  while(1)
  {
    motor1(100);
    motor2(0);
    motor3(0);
    motor4(0);
    delay(1000);
    motor1(-100);
    motor2(0);
    motor3(0);
    motor4(0);
    delay(1000);

    motor1(0);
    motor2(100);
    motor3(0);
    motor4(0);
    delay(1000);
    motor1(0);
    motor2(-100);
    motor3(0);
    motor4(0);
    delay(1000);

    motor1(0);
    motor2(0);
    motor3(100);
    motor4(0);
    delay(1000);
    motor1(0);
    motor2(0);
    motor3(-100);
    motor4(0);
    delay(1000);

    motor1(0);
    motor2(0);
    motor3(0);
    motor4(100);
    delay(1000);
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(-100);
    delay(1000);

    motor1(0);
    motor2(0);
    motor3(0);
    motor4(0);
    delay(1000);
  }
}

#endif /* INC_BKD_MOTOR_H_ */
