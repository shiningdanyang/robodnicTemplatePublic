/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author, do not claim as your own or tell the community that you are the author ;)
     Dungf http://www.translate.google.com neeus khoong hieeur tieengs Anh ;)
*/










































































#define BKD_GAMEPAD
#define MECANUM
#define IMU
#define KINEMATIC_EASY
//#define ULTIMATE
// #define DEBUG
// #define TEST

#ifndef MECANUM
#define DIFFERENTIAL
#endif

#include "libPrivate/BKD_Ard_Motor.h"
#include "libPublic/BKD_Ard_Auto.h"
#include "libPublic/BKD_Ard_Lcd.h"
#include "libPrivate/BKD_Ard_Uart.h"

#ifdef ULTIMATE
#include "libPrivate/BKD_Ard_Kinematic_Ultimate.h"
#include "libPrivate/BKD_Ard_Uart_Ultimate.h"
#else
#endif

#ifdef KINEMATIC_EASY
#include "libPrivate/BKD_Ard_Kinematic_Basic.h"
#else
#include "BKD_Ard_Kinematic.h"
#endif


void setup() {
  failsafeActive();
  Serial.begin(57600);
  Serial.println("Welcome to ShiningDanyang ecosystem");
  
#ifdef TEST
  testMotor();
#endif

  setupLcd();
  setupGamepad();
  setupImu();
  setupGpio();
  Serial.println("Setup completed");


  while(isConnected == 0)
  {
    onLoopUart();
    failsafeActive();
  }
}

void loop() {
  onLoopUart();
  onLoopKinematic();
  onLoopLcd();
  Serial2.write(shootSpeed);
  Serial.println(compassData);

//USER CODE BEGIN HERE

if(SQUARE)
{
    digitalWrite(12, LOW);
}
else
{
    digitalWrite(12, HIGH);
}

if(SELECT)
{
    runSpeed = 200;
}
else
{
    runSpeed = 30;
}

//USER CODE END HERE
}
