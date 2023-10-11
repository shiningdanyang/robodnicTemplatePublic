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

#ifdef IMU
  IMU_SERIAL.write('z');
#endif

  while ((micros() - timeStartReadGamepad) < GAMEPAD_TIMEOUT)
  {
    while (!BKD_Gamepad.available())
    {
#ifdef DEBUG
      Serial.print(".");
#endif
    }
    rxTemp = BKD_Gamepad.read();
    if (rxTemp == 0xAA) rxCnt++;
    else
    {
      if (rxCnt == 4)
      {
        DATA[rxDATAIndex] = rxTemp;
        rxDATAIndex++;
        if (rxDATAIndex == 6)
        {
          rxValueButton = DATA[0] << 8 | DATA[1];
          rxValueJoyRightX = DATA[2] << 8;
          rxValueJoyRightY = DATA[3];
          rxValueJoyLeftX = DATA[4] << 8;
          rxValueJoyLeftY = DATA[5];
#ifdef DEBUG
          Serial.print("B:");
          Serial.print(rxValueButton, HEX);
#endif
          rxDATAIndex = 0;
          rxCnt = 0;
//          break;
        }
      }
      else rxCnt = 0;
    }
  }
#ifdef IMU
  uint8_t highByte = IMU_SERIAL.read();
  uint8_t lowByte = IMU_SERIAL.read();
  compassData = (highByte<<8) | lowByte;
  IMU_SERIAL.read();
  IMU_SERIAL.read();
#endif
#endif
}

void checkButtonGamepad()
{
  if (LEFT)
  {}
  else
  {}

  if (DOWN)
  {}
  else
  {}

  if (RIGHT)
  {}
  else
  {}

  if (UP)
  {}
  else
  {}

  if (START)
  {
    desiredRunSpeed = 100;
  }
  else
  {
    
  }

  if (R3)
  {}
  else
  {}

  if (L3)
  {}
  else
  {}

  if (SELECT)
  {
    desiredRunSpeed = 150;
  }
  else
  {
    
  }

  if (SQUARE)
  {}
  else
  {}

  if (CROSS)
  {}
  else
  {}

  if (CIRCLE)
  {
    desiredRunSpeed = 50;
  }
  else
  {
    
  }

  if (TRIANGLE)
  {}
  else
  {}

  if (R1)
  {}
  else
  {}

  if (L1)
  {}
  else
  {}

  if (R2)
  {}
  else
  {}

  if (L2)
  {}
  else
  {}

  if (JRU)
  {}
  else
  {}

  if (JRD)
  {}
  else
  {}

  if (JRL)
  {}
  else
  {}

  if (JRR)
  {}
  else
  {}

  if (JLU)
  {}
  else
  {}

  if (JLD)
  {}
  else
  {}

  if (JLL)
  {}
  else
  {}

  if (JLR)
  {}
  else
  {}
}

void checkButtonGamepadToggle()
{
  if (LEFT)
  {
    if (++integrateLEFT > INTEGRATE_DEBOUNCE)
    {
      integrateLEFT = INTEGRATE_DEBOUNCE;
      if (previousLEFT == 0)
      {
        /* Toggle LEFT here */
      }
      previousLEFT = 1;
    }
  }
  else
  {
    integrateLEFT = 0;
    previousLEFT = 0;
  }

  if (DOWN)
  {
    if (++integrateDOWN > INTEGRATE_DEBOUNCE)
    {
      integrateDOWN = INTEGRATE_DEBOUNCE;
      if (previousDOWN == 0)
      {
        /* Toggle DOWN here */
      }
      previousDOWN = 1;
    }
  }
  else
  {
    integrateDOWN = 0;
    previousDOWN = 0;
  }

  if (RIGHT)
  {
    if (++integrateRIGHT > INTEGRATE_DEBOUNCE)
    {
      integrateRIGHT = INTEGRATE_DEBOUNCE;
      if (previousRIGHT == 0)
      {
        /* Toggle RIGHT here */
      }
      previousRIGHT = 1;
    }
  }
  else
  {
    integrateRIGHT = 0;
    previousRIGHT = 0;
  }

  if (UP)
  {
    if (++integrateUP > INTEGRATE_DEBOUNCE)
    {
      integrateUP = INTEGRATE_DEBOUNCE;
      if (previousUP == 0)
      {
        /* Toggle UP here */
      }
      previousUP = 1;
    }
  }
  else
  {
    integrateUP = 0;
    previousUP = 0;
  }

  if (START)
  {
    if (++integrateSTART > INTEGRATE_DEBOUNCE)
    {
      integrateSTART = INTEGRATE_DEBOUNCE;
      if (previousSTART == 0)
      {
        /* Toggle START here */
      }
      previousSTART = 1;
    }
  }
  else
  {
    integrateSTART = 0;
    previousSTART = 0;
  }

  if (R3)
  {
    if (++integrateR3 > INTEGRATE_DEBOUNCE)
    {
      integrateR3 = INTEGRATE_DEBOUNCE;
      if (previousR3 == 0)
      {
        /* Toggle R3 here */
      }
      previousR3 = 1;
    }
  }
  else
  {
    integrateR3 = 0;
    previousR3 = 0;
  }

  if (L3)
  {
    if (++integrateL3 > INTEGRATE_DEBOUNCE)
    {
      integrateL3 = INTEGRATE_DEBOUNCE;
      if (previousL3 == 0)
      {
        /* Toggle L3 here */
      }
      previousL3 = 1;
    }
  }
  else
  {
    integrateL3 = 0;
    previousL3 = 0;
  }

  if (SELECT)
  {
    if (++integrateSELECT > INTEGRATE_DEBOUNCE)
    {
      integrateSELECT = INTEGRATE_DEBOUNCE;
      if (previousSELECT == 0)
      {
        /* Toggle SLECT here */
      }
      previousSELECT = 1;
    }
  }
  else
  {
    integrateSELECT = 0;
    previousSELECT = 0;
  }

  if (SQUARE)
  {
    if (++integrateSQUARE > INTEGRATE_DEBOUNCE)
    {
      integrateSQUARE = INTEGRATE_DEBOUNCE;
      if (previousSQUARE == 0)
      {
        /* Toggle SQUARE here */
      }
      previousSQUARE = 1;
    }
  }
  else
  {
    integrateSQUARE = 0;
    previousSQUARE = 0;
  }

  if (CROSS)
  {
    if (++integrateCROSS > INTEGRATE_DEBOUNCE)
    {
      integrateCROSS = INTEGRATE_DEBOUNCE;
      if (previousCROSS == 0)
      {
        /* Toggle CROSS here */
      }
      previousCROSS = 1;
    }
  }
  else
  {
    integrateCROSS = 0;
    previousCROSS = 0;
  }

  if (CIRCLE)
  {
    if (++integrateCIRCLE > INTEGRATE_DEBOUNCE)
    {
      integrateCIRCLE = INTEGRATE_DEBOUNCE;
      if (previousCIRCLE == 0)
      {
        /* Toggle CIRCLE here */
      }
      previousCIRCLE = 1;
    }
  }
  else
  {
    integrateCIRCLE = 0;
    previousCIRCLE = 0;
  }

  if (TRIANGLE)
  {
    if (++integrateTRIANGLE > INTEGRATE_DEBOUNCE)
    {
      integrateTRIANGLE = INTEGRATE_DEBOUNCE;
      if (previousTRIANGLE == 0)
      {
        /* Toggle TRIANGLE here */
      }
      previousTRIANGLE = 1;
    }
  }
  else
  {
    integrateTRIANGLE = 0;
    previousTRIANGLE = 0;
  }

  if (R1)
  {
    if (++integrateR1 > INTEGRATE_DEBOUNCE)
    {
      integrateR1 = INTEGRATE_DEBOUNCE;
      if (previousR1 == 0)
      {
        /* Toggle R1 here */
      }
      previousR1 = 1;
    }
  }
  else
  {
    integrateR1 = 0;
    previousR1 = 0;
  }

  if (L1)
  {
    if (++integrateL1 > INTEGRATE_DEBOUNCE)
    {
      integrateL1 = INTEGRATE_DEBOUNCE;
      if (previousL1 == 0)
      {
        /* Toggle L1 here */
      }
      previousL1 = 1;
    }
  }
  else
  {
    integrateL1 = 0;
    previousL1 = 0;
  }

  if (R2)
  {
    if (++integrateR2 > INTEGRATE_DEBOUNCE)
    {
      integrateR2 = INTEGRATE_DEBOUNCE;
      if (previousR2 == 0)
      {
        /* Toggle R2 here */
      }
      previousR2 = 1;
    }
  }
  else
  {
    integrateR2 = 0;
    previousR2 = 0;
  }

  if (L2)
  {
    if (++integrateL2 > INTEGRATE_DEBOUNCE)
    {
      integrateL2 = INTEGRATE_DEBOUNCE;
      if (previousL2 == 0)
      {
        /* Toggle L2 here */
      }
      previousL2 = 1;
    }
  }
  else
  {
    integrateL2 = 0;
    previousL2 = 0;
  }

  if (JLL)
  {
    if (++integrateJLL > INTEGRATE_DEBOUNCE)
    {
      integrateJLL = INTEGRATE_DEBOUNCE;
      if (previousJLL == 0)
      {
        /* Toggle L2 here */
      }
      previousJLL = 1;
    }
  }
  else
  {
    integrateJLL = 0;
    previousJLL = 0;
  }

  if (JLR)
  {
    if (++integrateJLR > INTEGRATE_DEBOUNCE)
    {
      integrateJLR = INTEGRATE_DEBOUNCE;
      if (previousJLR == 0)
      {
        /* Toggle L2 here */
      }
      previousJLR = 1;
    }
  }
  else
  {
    integrateJLR = 0;
    previousJLR = 0;
  }

  if (JLU)
  {
    if (++integrateJLU > INTEGRATE_DEBOUNCE)
    {
      integrateJLU = INTEGRATE_DEBOUNCE;
      if (previousJLU == 0)
      {
        /* Toggle L2 here */
      }
      previousJLU = 1;
    }
  }
  else
  {
    integrateJLU = 0;
    previousJLU = 0;
  }

  if (JLD)
  {
    if (++integrateJLD > INTEGRATE_DEBOUNCE)
    {
      integrateJLD = INTEGRATE_DEBOUNCE;
      if (previousJLD == 0)
      {
        /* Toggle L2 here */
      }
      previousJLD = 1;
    }
  }
  else
  {
    integrateJLD = 0;
    previousJLD = 0;
  }

  if (JRL)
  {
    if (++integrateJRL > INTEGRATE_DEBOUNCE)
    {
      integrateJRL = INTEGRATE_DEBOUNCE;
      if (previousJRL == 0)
      {
        /* Toggle L2 here */
      }
      previousJRL = 1;
    }
  }
  else
  {
    integrateJRL = 0;
    previousJRL = 0;
  }

  if (JRR)
  {
    if (++integrateJRR > INTEGRATE_DEBOUNCE)
    {
      integrateJRR = INTEGRATE_DEBOUNCE;
      if (previousJRR == 0)
      {
        /* Toggle L2 here */
      }
      previousJRR = 1;
    }
  }
  else
  {
    integrateJRR = 0;
    previousJRR = 0;
  }

  if (JRU)
  {
    if (++integrateJRU > INTEGRATE_DEBOUNCE)
    {
      integrateJRU = INTEGRATE_DEBOUNCE;
      if (previousJRU == 0)
      {
        /* Toggle L2 here */
      }
      previousJRU = 1;
    }
  }
  else
  {
    integrateJRU = 0;
    previousJRU = 0;
  }

  if (JRD)
  {
    if (++integrateJRD > INTEGRATE_DEBOUNCE)
    {
      integrateJRD = INTEGRATE_DEBOUNCE;
      if (previousJRD == 0)
      {
        /* Toggle L2 here */
      }
      previousJRD = 1;
    }
  }
  else
  {
    integrateJRD = 0;
    previousJRD = 0;
  }
}

#endif /* INC_BKD_ARD_GAMEPAD_H_ */
