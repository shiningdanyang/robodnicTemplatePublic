/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
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

  if (isShoot)
  {
    motorShoot(shootSpeed);
  } else {
    motorShoot(0);
  }

  if (isChainDriver || isChainDriver1)
  {
    digitalWrite(chainDriver, LOW);
  } else
  {
    digitalWrite(chainDriver, HIGH);
  }
}
