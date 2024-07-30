#ifndef INC_BKD_ARD_GAMEPAD_H_
#define INC_BKD_ARD_GAMEPAD_H_
#include "BKD_Ard_Motor.h"
#ifndef BKD_GAMEPAD
#define PS2_GAMEPAD
#include <PS2X_lib.h>
#define CLOCK     45
#define COMMAND   46
#define ATTENTION 47
#define DATA      49
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
#else
#define BKD_Gamepad Serial3
#define GAMEPAD_TIMEOUT 20000U
long long timeStartReadGamepad;
uint8_t DATA[6], rxTemp, rxCnt = 0;
int16_t rxValueButton = 0;
int16_t rxValueJoyLeftX = 0, rxValueJoyLeftY = 0;
int16_t rxValueJoyRightX = 0, rxValueJoyRightY = 0;
int16_t rxDATAIndex = 0;
#endif
int16_t compassData;
uint8_t desiredRunSpeed = 50;

#ifdef IMU
#define IMU_SERIAL Serial2
#endif

#define INTEGRATE_DEBOUNCE 20
#define MAX_COUNTER_ACC 200


uint8_t previousLEFT;
uint8_t previousDOWN;
uint8_t previousRIGHT;
uint8_t previousUP;
uint8_t previousSTART;
uint8_t previousR3;
uint8_t previousL3;
uint8_t previousSELECT;
uint8_t previousSQUARE;
uint8_t previousCROSS;
uint8_t previousCIRCLE;
uint8_t previousTRIANGLE;
uint8_t previousR1;
uint8_t previousL1;
uint8_t previousR2;
uint8_t previousL2;
uint8_t previousJLL;
uint8_t previousJLR;
uint8_t previousJLU;
uint8_t previousJLD;
uint8_t previousJRL;
uint8_t previousJRR;
uint8_t previousJRU;
uint8_t previousJRD;

uint8_t integrateLEFT;
uint8_t integrateDOWN;
uint8_t integrateRIGHT;
uint8_t integrateUP;
uint8_t integrateSTART;
uint8_t integrateR3;
uint8_t integrateL3;
uint8_t integrateSELECT;
uint8_t integrateSQUARE;
uint8_t integrateCROSS;
uint8_t integrateCIRCLE;
uint8_t integrateTRIANGLE;
uint8_t integrateR1;
uint8_t integrateL1;
uint8_t integrateR2;
uint8_t integrateL2;
uint8_t integrateJLL;
uint8_t integrateJLR;
uint8_t integrateJLU;
uint8_t integrateJLD;
uint8_t integrateJRL;
uint8_t integrateJRR;
uint8_t integrateJRU;
uint8_t integrateJRD;

#define I_LEFT      15
#define I_DOWN      14
#define I_RIGHT     13
#define I_UP        12
#define I_START     11
#define I_R3        10
#define I_L3        9
#define I_SELECT    8
#define I_SQUARE    7
#define I_CROSS     6
#define I_CIRCLE    5
#define I_TRIANGLE  4
#define I_R1        3
#define I_L1        2
#define I_R2        1
#define I_L2        0

#ifndef BKD_GAMEPAD
#define LEFT      ps2x.Button(PSB_PAD_LEFT)
#define DOWN      ps2x.Button(PSB_PAD_DOWN)
#define RIGHT     ps2x.Button(PSB_PAD_RIGHT)
#define UP        ps2x.Button(PSB_PAD_UP)
#define START     ps2x.Button(PSB_START)
#define R3        ps2x.Button(PSB_R3)
#define L3        ps2x.Button(PSB_L3)
#define SELECT    ps2x.Button(PSB_SELECT)
#define SQUARE    ps2x.Button(PSB_SQUARE)
#define CROSS     ps2x.Button(PSB_CROSS)
#define CIRCLE    ps2x.Button(PSB_CIRCLE)
#define TRIANGLE  ps2x.Button(PSB_TRIANGLE)
#define R1        ps2x.Button(PSB_R1)
#define L1        ps2x.Button(PSB_L1)
#define R2        ps2x.Button(PSB_R2)
#define L2        ps2x.Button(PSB_L2)
#define JLL       ps2x.Analog(PSS_RX) <  20 ? 1 : 0
#define JLD       ps2x.Analog(PSS_RY) > 235 ? 1 : 0
#define JLR       ps2x.Analog(PSS_RX) > 235 ? 1 : 0
#define JLU       ps2x.Analog(PSS_RY) <  20 ? 1 : 0
#define JRL       ps2x.Analog(PSS_RX) <  20 ? 1 : 0
#define JRD       ps2x.Analog(PSS_RY) > 235 ? 1 : 0
#define JRR       ps2x.Analog(PSS_RX) > 235 ? 1 : 0
#define JRU       ps2x.Analog(PSS_RY) <  20 ? 1 : 0
#define RY        ps2x.Analog(PSS_RY)
#define LY        ps2x.Analog(PSS_LY)
#define RX        ps2x.Analog(PSS_RX)
#define LX        ps2x.Analog(PSS_LX)
#else
#define LEFT      ((rxValueButton>>15) & 1U) ? 0 : 1
#define DOWN      ((rxValueButton>>14) & 1U) ? 0 : 1
#define RIGHT     ((rxValueButton>>13) & 1U) ? 0 : 1
#define UP        ((rxValueButton>>12) & 1U) ? 0 : 1
#define START     ((rxValueButton>>11) & 1U) ? 0 : 1
#define R3        ((rxValueButton>>10) & 1U) ? 0 : 1
#define L3        ((rxValueButton>> 9) & 1U) ? 0 : 1
#define SELECT    ((rxValueButton>> 8) & 1U) ? 0 : 1
#define SQUARE    ((rxValueButton>> 7) & 1U) ? 0 : 1
#define CROSS     ((rxValueButton>> 6) & 1U) ? 0 : 1
#define CIRCLE    ((rxValueButton>> 5) & 1U) ? 0 : 1
#define TRIANGLE  ((rxValueButton>> 4) & 1U) ? 0 : 1
#define R1        ((rxValueButton>> 3) & 1U) ? 0 : 1
#define L1        ((rxValueButton>> 2) & 1U) ? 0 : 1
#define R2        ((rxValueButton>> 1) & 1U) ? 0 : 1
#define L2        ((rxValueButton>> 0) & 1U) ? 0 : 1
#define JLL       rxValueJoyLeftX  <  20 ? 1 : 0
#define JLD       rxValueJoyLeftY  > 235 ? 1 : 0
#define JLR       rxValueJoyLeftX  > 235 ? 1 : 0
#define JLU       rxValueJoyLeftY  <  20 ? 1 : 0
#define JRL       rxValueJoyRightX <  20 ? 1 : 0
#define JRD       rxValueJoyRightY > 235 ? 1 : 0
#define JRR       rxValueJoyRightX > 235 ? 1 : 0
#define JRU       rxValueJoyRightY <  20 ? 1 : 0
#define RY        rxValueJoyRightY
#define LY        rxValueJoyLeftY
#define RX        rxValueJoyRightX
#define LX        rxValueJoyLeftX
#endif

void setupGamepad()
{
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
  BKD_Gamepad.begin(19200);
#endif
#ifdef IMU
  IMU_SERIAL.begin(115200);
  delay(1000);
  IMU_SERIAL.write('a');
  delay(1000);
#endif
}

void readGamepad()
{
#ifndef BKD_GAMEPAD
  ps2x.read_gamepad(false, vibrate); // disable vibration of the controller
#else
  timeStartReadGamepad = micros();
#endif
}

void checkButtonGamepad()
{
}

void checkButtonGamepadToggle()
{
}

#endif /* INC_BKD_ARD_GAMEPAD_H_ */
