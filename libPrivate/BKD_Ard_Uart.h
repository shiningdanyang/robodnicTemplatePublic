/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_UART_H_
#define INC_BKD_ARD_UART_H_
#include "Arduino.h"
#include "HardwareSerial.h"
#include "../libPublic/BKD_Ard_Uart_User.h"
#include "../libPrivate/BKD_Ard_Motor.h"
#include "../libPublic/BKD_Ard_IO.h"
#include "../libPublic/BKD_Ard_Failsafe.h"
#ifdef ULTIMATE
#include "../libPrivate/BKD_Ard_Uart_Ultimate.h"
#endif

long long timeStartCheckFailsafe;
uint8_t isLiveCompass = 0;
uint8_t isConnected = 0;

#define I_LEFT 15
#define I_DOWN 14
#define I_RIGHT 13
#define I_UP 12
#define I_START 11
#define I_R3 10
#define I_L3 9
#define I_SELECT 8
#define I_SQUARE 7
#define I_CROSS 6
#define I_CIRCLE 5
#define I_TRIANGLE 4
#define I_R1 3
#define I_L1 2
#define I_R2 1
#define I_L2 0

#ifndef BKD_GAMEPAD
#define LEFT ps2x.Button(PSB_PAD_LEFT)
#define DOWN ps2x.Button(PSB_PAD_DOWN)
#define RIGHT ps2x.Button(PSB_PAD_RIGHT)
#define UP ps2x.Button(PSB_PAD_UP)
#define START ps2x.Button(PSB_START)
#define R3 ps2x.Button(PSB_R3)
#define L3 ps2x.Button(PSB_L3)
#define SELECT ps2x.Button(PSB_SELECT)
#define SQUARE ps2x.Button(PSB_SQUARE)
#define CROSS ps2x.Button(PSB_CROSS)
#define CIRCLE ps2x.Button(PSB_CIRCLE)
#define TRIANGLE ps2x.Button(PSB_TRIANGLE)
#define R1 ps2x.Button(PSB_R1)
#define L1 ps2x.Button(PSB_L1)
#define R2 ps2x.Button(PSB_R2)
#define L2 ps2x.Button(PSB_L2)
#define JLL ps2x.Analog(PSS_LX) < 40 ? 1 : 0
#define JLD ps2x.Analog(PSS_LY) > 200 ? 1 : 0
#define JLR ps2x.Analog(PSS_LX) > 200 ? 1 : 0
#define JLU ps2x.Analog(PSS_LY) < 40 ? 1 : 0
#define JRL ps2x.Analog(PSS_RX) < 40 ? 1 : 0
#define JRD ps2x.Analog(PSS_RY) > 200 ? 1 : 0
#define JRR ps2x.Analog(PSS_RX) > 200 ? 1 : 0
#define JRU ps2x.Analog(PSS_RY) < 40 ? 1 : 0
#define RY ps2x.Analog(PSS_RY)
#define LY ps2x.Analog(PSS_LY)
#define RX ps2x.Analog(PSS_RX)
#define LX ps2x.Analog(PSS_LX)
#else
#define LEFT ((rxValueButton >> 15) & 1U) ? 0 : 1
#define DOWN ((rxValueButton >> 14) & 1U) ? 0 : 1
#define RIGHT ((rxValueButton >> 13) & 1U) ? 0 : 1
#define UP ((rxValueButton >> 12) & 1U) ? 0 : 1
#define START ((rxValueButton >> 11) & 1U) ? 0 : 1
#define R3 ((rxValueButton >> 10) & 1U) ? 0 : 1
#define L3 ((rxValueButton >> 9) & 1U) ? 0 : 1
#define SELECT ((rxValueButton >> 8) & 1U) ? 0 : 1
#define SQUARE ((rxValueButton >> 7) & 1U) ? 0 : 1
#define CROSS ((rxValueButton >> 6) & 1U) ? 0 : 1
#define CIRCLE ((rxValueButton >> 5) & 1U) ? 0 : 1
#define TRIANGLE ((rxValueButton >> 4) & 1U) ? 0 : 1
#define R1 ((rxValueButton >> 3) & 1U) ? 0 : 1
#define L1 ((rxValueButton >> 2) & 1U) ? 0 : 1
#define R2 ((rxValueButton >> 1) & 1U) ? 0 : 1
#define L2 ((rxValueButton >> 0) & 1U) ? 0 : 1
#define JLL rxValueJoyLeftX < 50 ? 1 : 0
#define JLD rxValueJoyLeftY > 215 ? 1 : 0
#define JLR rxValueJoyLeftX > 215 ? 1 : 0
#define JLU rxValueJoyLeftY < 50 ? 1 : 0
#define JRL rxValueJoyRightX < 50 ? 1 : 0
#define JRD rxValueJoyRightY > 215 ? 1 : 0
#define JRR rxValueJoyRightX > 215 ? 1 : 0
#define JRU rxValueJoyRightY < 50 ? 1 : 0
#define RY rxValueJoyRightY
#define LY rxValueJoyLeftY
#define RX rxValueJoyRightX
#define LX rxValueJoyLeftX
#endif

void checkButtonGamepadToggleUltimate();
void setupImuAdvance();
void readGamepadUart();
void readImuAdvance();

void setupGamepad() {
#ifndef BKD_GAMEPAD
  error = ps2x.config_gamepad(CLOCK, COMMAND, ATTENTION, DATA, false, false);
  if (error == 0) {
    Serial.println("Found Controller, configured successful");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring or reset the Arduino");

  else if (error == 2)
    Serial.println("Controller found but not accepting COMMANDs");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");

  // Check for the type of controller
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
#else
  BKD_Gamepad.begin(19200); //debug purpose, please simulate the data frame from host pc
#endif
}

void setupImu()
{
#ifdef ULTIMATE
  setupImuAdvance();
#endif
}

void checkButtonGamepad() {
  if (LEFT) {
    // sate = false;
  } else {
  }

  if (DOWN) {
    // sate = false;
  } else {
  }

  if (RIGHT) {
    // sate = false;
  } else {
  }

  if (UP) {
  } else {
  }

  if (START) {
    speedMode = 2;
  } else {
  }

  if (R3) {
    speedMode = 3;
  } else {
  }

  if (L3) {
    // sate = false;
  } else {
  }

  if (SELECT) {
    speedMode = 1;
  } else {
  }

  if (SQUARE) {
    digitalWrite(motorLoad, LOW);
  } else {
    digitalWrite(motorLoad, HIGH);
  }

  if (CROSS) {
    digitalWrite(downIntake, LOW);
  } else {
    digitalWrite(downIntake, HIGH);
  }

  if (CIRCLE) {
  } else {
  }

  if (TRIANGLE) {
    digitalWrite(upIntake, LOW);
  } else {
    digitalWrite(upIntake, HIGH);
  }

  if (R1) {
  } else {
  }

  if (L1) {
  } else {
  }

  if (R2) {
  } else {
  }

  if (L2) {
    digitalWrite(dragFlag, LOW);
    isChainDriver1 = true;
  } else {
    digitalWrite(dragFlag, HIGH);
    isChainDriver1 = false;
  }

  if (JRU) {
  } else {
  }

  if (JRD) {
  } else {
  }

  if (JRL) {
  } else {
  }

  if (JRR) {
  } else {
  }

  if (JLU) {
  } else {
  }

  if (JLD) {
  } else {
  }

  if (JLL) {
  } else {
  }

  if (JLR) {
  } else {
  }
}

void checkButtonGamepadToggle() {
#ifdef BKD_GAMEPAD
#ifdef ULTIMATE
  checkButtonGamepadToggleUltimate();
#endif
#endif
}

void readGamepad()
{
#ifndef BKD_GAMEPAD
  ps2x.read_gamepad(false, vibrate);  // disable vibration of the controller
#else
#ifdef ULTIMATE
  readGamepadUart();
#endif
#endif
}

void readImu()
{
#ifdef ULTIMATE
#ifdef IMU
  readImuAdvance();
#endif
#endif
}

void onLoopUart() {
  readGamepad();
  checkButtonGamepad();
  checkButtonGamepadToggle();
  readImu();
}

#endif /* INC_BKD_ARD_GAMEPAD_H_ */
