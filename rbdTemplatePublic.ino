/*
     Created on: Oct 19, 2022
     Author: ShiningDanyang
     Please respect the autor and do not take it as your own
*/
#define BKD_GAMEPAD
#define MECANUM
#define IMU
 #define KINEMATIC_EASY
// #define DEBUG
// #define TEST

#ifndef MECANUM
#define DIFFERENTIAL
#endif

#include "BKD_Ard_Motor.h"
#include "BKD_Ard_Gamepad.h"
#include "BKD_Ard_IO.h"
#ifdef KINEMATIC_EASY
#include "BKD_Ard_KinematicEasy.h"
#else
#include "BKD_Ard_Kinematic.h"
#endif

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to BKD-Phoenix ecosystem");
#ifdef TEST
  testMotor();
#endif

  setupGamepad();
  setupGpio();

#ifndef KINEMATIC_EASY
  setupKinematic();
#endif

#ifndef KINEMATIC_EASY
  speedMode = 3;
  runSpeed = 200;
  rotateSpeed = 1;
  baseStop(deccel);
  baseRotateStop();
  baseStop(deccel);
  delay(1000);
#endif
}
int debugDir;
void loop() {
  readGamepad();
  checkButtonGamepad();
  checkButtonGamepadToggle();
#ifdef KINEMATIC_EASY
  robotControl();
#else
  Serial.print(baseMove(0));
//  Serial.print(compassData);
#endif
Serial.println();
}

#ifndef KINEMATIC_EASY
ISR (TIMER1_OVF_vect)
{
  TCNT1 = 65286;
  baseKinematicSolve();
}
#endif
