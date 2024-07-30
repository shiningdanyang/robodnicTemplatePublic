/*
     Created on: Oct 19, 2022
     Author: ShiningDanyang
     Please respect the author and do not take it as your own
*/

#ifndef INC_BKD_ARD_KINEMATICEASY_H_
#define INC_BKD_ARD_KINEMATICEASY_H_

void robotRun(int angle, int runSpeed, int rotateSpeed_)
{
#ifdef MECANUM
  switch (angle)
  {
    case 0:
      motor1(runSpeed + rotateSpeed_);
      motor2(-runSpeed + rotateSpeed_);
      motor3(-runSpeed + rotateSpeed_);
      motor4(runSpeed + rotateSpeed_);
      break;
    case 1800:
      motor1(-runSpeed + rotateSpeed_);
      motor2(runSpeed + rotateSpeed_);
      motor3(runSpeed + rotateSpeed_);
      motor4(-runSpeed + rotateSpeed_);
      break;
    case 900:
      motor1(-runSpeed + rotateSpeed_);
      motor2(-runSpeed + rotateSpeed_);
      motor3(runSpeed + rotateSpeed_);
      motor4(runSpeed + rotateSpeed_);
      break;
    case -900:
      motor1(runSpeed + rotateSpeed_);
      motor2(runSpeed + rotateSpeed_);
      motor3(-runSpeed + rotateSpeed_);
      motor4(-runSpeed + rotateSpeed_);
      break;
    case 450:
      motor1(0 + rotateSpeed_);
      motor2(-runSpeed + rotateSpeed_);
      motor3(0 + rotateSpeed_);
      motor4(runSpeed + rotateSpeed_);
      break;
    case -450:
      motor1(runSpeed + rotateSpeed_);
      motor2(0 + rotateSpeed_);
      motor3(-runSpeed + rotateSpeed_);
      motor4(0 + rotateSpeed_);
      break;
    case 1350:
      motor1(-runSpeed + rotateSpeed_);
      motor2(0 + rotateSpeed_);
      motor3(runSpeed + rotateSpeed_);
      motor4(0 + rotateSpeed_);
      break;
    case -1350:
      motor1(0 + rotateSpeed_);
      motor2(runSpeed + rotateSpeed_);
      motor3(0 + rotateSpeed_);
      motor4(-runSpeed + rotateSpeed_);
      break;
  }
#endif
#ifdef DIFFERENTIAL

#endif
}

void robotControl()
{
#ifndef KINEMATIC_EASY
  if (speedMode == 1)
  {
    runSpeed = runSpeed1;
    rotateSpeed = runSpeed1 - 40; //////////////////////////////////////////////////
  }
  else if (speedMode == 2)
  {
    runSpeed = runSpeed2;
    rotateSpeed = runSpeed2 - 60; ///////////////////////////////////////////////////
  }
  else if (speedMode == 3)
  {
    runSpeed = runSpeed3;
    rotateSpeed = runSpeed3 - 80; ///////////////////////////////////////////////////
  }
#endif
#ifdef MECANUM
  Serial.println(runSpeed);
  if      (!UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun(    0,        0,            0);
  else if (!UP && !DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun(    0,        0, -rotateSpeed);
  else if (!UP && !DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun(    0,        0,  rotateSpeed);
  else if ( UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun(    0, runSpeed,            0);
  else if ( UP && !DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun(    0, runSpeed, -rotateSpeed);
  else if ( UP && !DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun(    0, runSpeed,  rotateSpeed);
  else if (!UP &&  DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun( 1800, runSpeed,            0);
  else if (!UP &&  DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun( 1800, runSpeed, -rotateSpeed);
  else if (!UP &&  DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun( 1800, runSpeed,  rotateSpeed);
  else if (!UP && !DOWN &&  RIGHT && !LEFT && !L1 && !R1)   robotRun(  900, runSpeed,            0);
  else if (!UP && !DOWN &&  RIGHT && !LEFT && !L1 &&  R1)   robotRun(  900, runSpeed, -rotateSpeed);
  else if (!UP && !DOWN &&  RIGHT && !LEFT &&  L1 && !R1)   robotRun(  900, runSpeed,  rotateSpeed);
  else if (!UP && !DOWN && !RIGHT &&  LEFT && !L1 && !R1)   robotRun( -900, runSpeed,            0);
  else if (!UP && !DOWN && !RIGHT &&  LEFT && !L1 &&  R1)   robotRun( -900, runSpeed, -rotateSpeed);
  else if (!UP && !DOWN && !RIGHT &&  LEFT &&  L1 && !R1)   robotRun( -900, runSpeed,  rotateSpeed);
  else if ( UP && !DOWN &&  RIGHT && !LEFT && !L1 && !R1)   robotRun(  450, runSpeed,            0);
  else if ( UP && !DOWN &&  RIGHT && !LEFT && !L1 &&  R1)   robotRun(  450, runSpeed, -rotateSpeed);
  else if ( UP && !DOWN &&  RIGHT && !LEFT &&  L1 && !R1)   robotRun(  450, runSpeed,  rotateSpeed);
  else if ( UP && !DOWN && !RIGHT &&  LEFT && !L1 && !R1)   robotRun( -450, runSpeed,            0);
  else if ( UP && !DOWN && !RIGHT &&  LEFT && !L1 &&  R1)   robotRun( -450, runSpeed, -rotateSpeed);
  else if ( UP && !DOWN && !RIGHT &&  LEFT &&  L1 && !R1)   robotRun( -450, runSpeed,  rotateSpeed);
  else if (!UP &&  DOWN &&  RIGHT && !LEFT && !L1 && !R1)   robotRun( 1350, runSpeed,            0);
  else if (!UP &&  DOWN &&  RIGHT && !LEFT && !L1 &&  R1)   robotRun( 1350, runSpeed, -rotateSpeed);
  else if (!UP &&  DOWN &&  RIGHT && !LEFT &&  L1 && !R1)   robotRun( 1350, runSpeed,  rotateSpeed);
  else if (!UP &&  DOWN && !RIGHT &&  LEFT && !L1 && !R1)   robotRun(-1350, runSpeed,            0);
  else if (!UP &&  DOWN && !RIGHT &&  LEFT && !L1 &&  R1)   robotRun(-1350, runSpeed, -rotateSpeed);
  else if (!UP &&  DOWN && !RIGHT &&  LEFT &&  L1 && !R1)   robotRun(-1350, runSpeed,  rotateSpeed);
#endif
#ifdef DIFFERENTIAL
  if      (!UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun(0, 0, 0);
  else if (!UP && !DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun(0, 0, -rotateSpeed);
  else if (!UP && !DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun(0, 0, rotateSpeed);

  else if ( UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun(0, runSpeed, 0);
  else if ( UP && !DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun(0, runSpeed, -rotateSpeed);
  else if ( UP && !DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun(0, runSpeed, rotateSpeed);

  else if (!UP &&  DOWN && !RIGHT && !LEFT && !L1 && !R1)   robotRun(1800, runSpeed, 0);
  else if (!UP &&  DOWN && !RIGHT && !LEFT && !L1 &&  R1)   robotRun(1800, runSpeed, -rotateSpeed);
  else if (!UP &&  DOWN && !RIGHT && !LEFT &&  L1 && !R1)   robotRun(1800, runSpeed, rotateSpeed);
#endif
  //  Serial.println();
}
#endif /* INC_BKD_ARD_KINEMATICEASY_H_ */
