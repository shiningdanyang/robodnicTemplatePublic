/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang & BKD-Fire
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_UART_USER_H_
#define INC_BKD_ARD_UART_USER_H_
#ifdef ULTIMATE
#include "../libPrivate/BKD_Ard_Uart_Ultimate.h"
#else
#include "../libPrivate/BKD_Ard_Uart.h"
#endif

#ifndef BKD_GAMEPAD
#define PS2_GAMEPAD
#include <PS2X_lib.h>
#define CLOCK 45
#define COMMAND 46
#define ATTENTION 47
#define DATA 49
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
#else
#define BKD_Gamepad Serial2
#define GAMEPAD_TIMEOUT 20000U
#endif
int16_t rxValueButton = 0;
int16_t rxValueJoyLeftX = 0, rxValueJoyLeftY = 0;
int16_t rxValueJoyRightX = 0, rxValueJoyRightY = 0;
uint8_t DATA[6], rxTemp, rxCnt = 0;
int16_t rxDATAIndex = 0;

#ifdef IMU
#define IMU_SERIAL Serial3
#endif

#define INTEGRATE_DEBOUNCE 3
#define MAX_COUNTER_ACC 200

int16_t compassData;

void checkButtonGamepadUser()
{

}


void toggleLeft()
{
  
}

void toggleDown()
{
  
}

void toggleRight()
{
  
}

void toggleUp()
{
  
}

void toggleStart()
{
  
}

void toggleR3()
{
  
}

void toggleL3()
{
  
}

void toggleSelect()
{
  
}

void toggleSquare()
{
  
}

void toggleCross()
{
  
}

void toggleCircle()
{
  isShoot = !isShoot;
}

void toggleTriangle()
{
  
}

void toggleR1()
{
  
}

void toggleL1()
{
  
}

void toggleR2()
{
  isChainDriver = !isChainDriver;
}

void toggleL2()
{
  isChainDriver1 = !isChainDriver1;
}

void toggleJLL()
{
  if(shootSpeed < 250)
  {
    shootSpeed = shootSpeed + 5;
  }
}

void toggleJLD()
{
  
}

void toggleJLR()
{
  if(shootSpeed > 10)
  {
    shootSpeed = shootSpeed - 5;
  }
}

void toggleJLU()
{
  
}

void toggleJRL()
{
  
}

void toggleJRD()
{
  
}

void toggleJRR()
{
  
}

void toggleJRU()
{
  
}


#endif
