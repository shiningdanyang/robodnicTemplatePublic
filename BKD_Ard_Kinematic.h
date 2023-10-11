#ifndef INC_BKD_ARD_KINEMATIC_H_
#define INC_BKD_ARD_KINEMATIC_H_

/*
   BKD_Kinematic.h

    Created on: Oct 19, 2022
        Author: ShiningDanyang
*/

/*
  //================================================
  4 wheels Omni/Mecanum base Controller

  //================================================

  //----------------------
  void baseKinematicSolve(void) // put in separated task

  //----------------------
  void baseSteering(int angle, int maxSpeed)
  void baseSteering(int angle, int maxSpeed, float curve)

  example: baseSteering(450, 70)
    //Direction: 450
    //Max speed: 70

  //----------------------
  void baseRunAngle(float angle, int maxSpeed, float baseAngle)

  example:
    while(.....){
      baseRunAngle(900, 70, 450)
    }
    //Direction: 900
    //Max speed: 70
    //Head angle: 450.

  //----------------------
  void baseRotateFree(float rotate, int rotatePoint)
  void baseRotate(int rotateAngle, float rotate, int rotatePoint)
  int baseFixAngle()

  example: baseRotateFree(0.5, 0)
      Rotate free:   ROTATE_FREE
      Direction and rotate speed:  0.5
      Center :        0     {0 : center, 1: LF...,2,3, 4: RR}

  example:
    baseRotate(300, 0.5, 0);
    while(baseFixAngle()){
    }

  //----------------------
  void baseSetAcc(float X, float Y)
  void baseStop(int acc)     // Stop all
  void baseRotateStop()      // Stop rotate
  void baseResetImu()

  //----------------------
  int baseIsRun()
  int baseIsStop()
  int baseAngle()
  int baseSpeed()
*/
#include <avr/interrupt.h>

//=================================================
//----- Constant -----
//=================================================
#define PROTOCOL_UART
#define PROTOCOL_PWM
#define NUMBER_OF_DRIVER 7

#define STOP_ROTATE_TIME 50U
#define ROTATE_FREE 30000
#define vu8 uint8_t
#define vs16 int16_t
#define vs32 int32_t
const float deccel = 2;
uint8_t isRotate = 0;
uint8_t itegrateStopRotate;
float runningRotating = 1;

#define isUP        UP
#define isDOWN      DOWN
#define isLEFT      LEFT
#define isRIGHT     RIGHT
#define isR1        R1
#define isL1        L1
#define isR3        R3
#define isL3        L3

int16_t driverSpeed[8];

uint8_t M1 = 0;
uint8_t M2 = 1;
uint8_t M3 = 2;
uint8_t M4 = 3;
uint8_t M5 = 4;
uint8_t M6 = 5;
uint8_t M7 = 6;
uint8_t M8 = 7;

vs16 imu;
const int baseLimitSpeed = 254;  // Max speed is: fixDirError + maxSpeed
const float f05 = 0.5, f1 = 1.0, f2 = 2.0, f4 = 4.0, f5 = 5.0, f6 = 6.0, f10 = 10.0, f20 = 20.0, f30 = 30.0, f45 = 45.0, f60 = 60.0, f120 = 120.0;
const int i100 = 100;
const int thresholdHeadAngle = 200;
const int motorLock = 0;
const int motorLockRepeat = 100;
const float radian = 3.141592653589793238462643 / 180;

//----- 1st order linear privateAccelerate -----
float _baseY = 20;
float _baseX = 200;

//=================================================
//----- Global var -----
//=================================================
int _baseChange = 0;
int _baseRotatePoint = 0;
int _baseCurrentSpeed = 0;
int _baseRunSpeed = 0;
int _baseMaxSpeed = 0;
int _baseAccStop = 0;
int _baseCounter = 0;
int _baseHeadAngle = ROTATE_FREE;
int _baseDirectionAngle = ROTATE_FREE;
int _baseRotateAngle = 0;
int _baseHeadAngleCounterFix = 0;
int _baseImu = 0;
int _baseImuInit = 0;
int _baseImuLast = 0;
float _baseRunM2 = 0;
float _baseRunM1 = 0;
float _baseRunM3 = 0;
float _baseRunM4 = 0;
float _baseRotateSpeed = 0;
float _baseCurve = 0;
float _baseHeadAngleToFix = ROTATE_FREE;
uint8_t _baseDelayDecelerate = 15;
uint8_t _baseIsAlreadyStop = 0;
int16_t motor1Speed = 0;
int16_t motor2Speed = 0;
int16_t motor3Speed = 0;
int16_t motor4Speed = 0;
int16_t motor1SpeedPre = 0;
int16_t motor2SpeedPre = 0;
int16_t motor3SpeedPre = 0;
int16_t motor4SpeedPre = 0;
uint8_t moveCommand;

void setupKinematic()
{
  cli();
  /* Reset Timer/Counter1 */
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;

  /* Setup Timer/Counter1 */
  TCCR1B |= (1 << CS11) | (1 << CS10);    // prescale = 64
  TCNT1 = 65286;
  TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable
  sei();                                  // Global interrupt enable
}



vu8 privateMotorMinFix(vu8 S)
{
  return (S < 4 ? 0 : S);
}

int privateRoundF(float num)
{
  if (num < 0) return num - f05;
  else return num + f05;
}

float privateAbsF(float num)
{
  if (num >= 0) return num;
  else return -num;
}

int privateAbsI(int num)
{
  if (num >= 0) return num;
  else return -num;
}

float privateMaxF4(float N1, float N2, float N3, float N4)
{
  float _maxNum = 0.001;
  if (N1 < 0) N1 = -N1;
  if (N2 < 0) N2 = -N2;
  if (N3 < 0) N3 = -N3;
  if (N4 < 0) N4 = -N4;

  if (N1 > _maxNum) _maxNum = N1;
  if (N2 > _maxNum) _maxNum = N2;
  if (N3 > _maxNum) _maxNum = N3;
  if (N4 > _maxNum) _maxNum = N4;

  return _maxNum;
}

int privateAccelerate(int x)
{
  // ------ acceleration -----------
  float y = (-_baseY / _baseX) * x + _baseY;
  return (int)y;
}

float privateFixMotorValue(int T)
{
  if (T == 0)
  {
    return 0;
  }
  else if (T < 0)
  {
    return (T * 0.2 - 0.5) / _baseCurrentSpeed; // Depending on the base, the minimum possible coefficient is 0.5, 1, 2...
  }
  else
  {
    return (T * 0.2 + 0.5) / _baseCurrentSpeed;
  }
}

void baseSetAllMotor(int speed)
{
  motor1(speed);
  motor2(speed);
  motor3(speed);
  motor4(speed);
}

void privateStopAcc(void)
{
}

void privateSpeedAcc(int acc, int n)
{
}

void privateCalculateMotor(float speedRotateOffset)
{
}
void baseStop(unsigned int acc)
{
}

void privateDirectionAnalytics()
{
}

void privateAngleAnalytics(void)
{
}

int baseAngle(void)
{
//    return -compassData;
  return 0;
}

int baseSpeed()
{
  return _baseCurrentSpeed;
}

uint8_t baseIsStop()
{
  return (driverSpeed[M2] < 3 && driverSpeed[M1] < 3 && driverSpeed[M3] < 3 && driverSpeed[M4] < 3);
}

uint8_t baseIsRun()
{
  return (_baseHeadAngle == ROTATE_FREE) ? 0 : 1;
}

void baseSetAcc(float fX, float fY)
{
  _baseY = fY;
  _baseX = fX;
}

void baseResetImu(void)
{
  //  compass_Reset();
}

void baseRotateStop()
{
}

void baseRotate(int rotateAngle, float rotateSpeed, int rotatePoint)
{
}

void baseRotateFree(float rotate, int rotatePoint)
{
  baseRotate(ROTATE_FREE, rotate, rotatePoint);
}

void baseSteering(int directionAngle, int maxSpeed, float curve)
{
}

void baseTranslate(int directionAngle, int maxSpeed)
{
}

void baseHolonomic(float directionAngle, int maxSpeed, float headAngle, float rotateSpeed)
{
}

void baseSetMotor(int speed_M1, int speed_M2, int speed_M3, int speed_M4)
{
}


void baseKinematicSolve(void)//--------  ---------
{
}

uint8_t baseMove(int headCustom)
{
  uint8_t debugDirection;
  if (headCustom == 1)
  {
    moveCommand = (isR1 << 5) | (isL1 << 4) | (isRIGHT << 3) | (isLEFT << 2) | (isUP << 1) | (isDOWN << 0);
  }
  else if (headCustom == 0)
  {
    moveCommand = (isUP << 1) | (isDOWN << 2) | (isLEFT << 3) | (isRIGHT << 4) | (isL1 << 5) | (isR1 << 6);
  }
  switch (moveCommand)
  {
    case 0:  //nothing pressed
      {
        debugDirection = 0;
        baseStop(deccel);
        if (isRotate == 1)
        {
          if(_baseCurrentSpeed == 0)
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 2:  //UP
      {
        debugDirection = 1;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(0, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 66: //UP R1
      {
        debugDirection = 2;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(0, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 34: //UP L1
      {
        debugDirection = 3;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(0, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 18:  //UP RIGHT
      {
        debugDirection = 4;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(450, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 82: //UP RIGHT R1
      {
        debugDirection = 5;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(450, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 50: //UP RIGHT L1
      {
        debugDirection = 6;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(450, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 16:  //RIGHT
      {
        debugDirection = 7;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(900, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 80: //RIGHT R1
      {
        debugDirection = 8;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(900, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 48: //RIGHT L1
      {
        debugDirection = 9;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(900, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 20:  //DOWN RIGHT
      {
        debugDirection = 10;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1350, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 84: //DOWN RIGHT R1
      {
        debugDirection = 11;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1350, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 52: //DOWN RIGHT L1
      {
        debugDirection = 12;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1350, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 4:  //DOWN
      {
        debugDirection = 13;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1800, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 68: //DOWN R1
      {
        debugDirection = 14;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1800, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 36: //DOWN L1
      {
        debugDirection = 15;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(1800, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 12:  //DOWN LEFT
      {
        debugDirection = 16;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-1350, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 76: //DOWN LEFT R1
      {
        debugDirection = 17;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-1350, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 44: //DOWN LEFT L1
      {
        debugDirection = 18;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-1350, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 8:  //LEFT
      {
        debugDirection = 19;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-900, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 72: //LEFT R1
      {
        debugDirection = 20;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-900, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 40: //LEFT L1
      {
        debugDirection = 21;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-900, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 10:  //UP LEFT
      {
        debugDirection = 22;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-450, runSpeed, 0);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 74: //UP LEFT R1
      {
        debugDirection = 23;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-450, runSpeed, runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 42: //UP LEFT L1
      {
        debugDirection = 24;
        if (isRotate == 0)
        {
          runSpeed = desiredRunSpeed;
          rotateSpeed = 1;
          baseSteering(-450, runSpeed, -runningRotating);
        }
        else
        {
          if(_baseCurrentSpeed != 0)
          {
            baseStop(deccel);
          }
          else
          {
            isRotate = 0;
          }
        }
        break;
      }
    case 64:  //R1
      {
        debugDirection = 25;
        isRotate = 1;
        baseRotateFree(1, 0);
        break;
      }
    case 32:  //L1
      {
        debugDirection = 26;
        isRotate = 1;
        baseRotateFree(-1, 0);
        break;
      }
  }
  return debugDirection;
}


#endif
