/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_KINEMATICBASIC_H_
#define INC_BKD_ARD_KINEMATICBASIC_H_
#include "../libPublic/BKD_Ard_Uart_User.h"
#ifdef ULTIMATE
#include "../libPrivate/BKD_Ard_Uart_Ultimate.h"
#include "../libPrivate/BKD_Ard_Kinematic_Ultimate.h"
#else
#include "../libPrivate/BKD_Ard_Uart.h"
#endif


int16_t setPoint;
bool enableSetPoint = false;
bool strategyPinned = true;

void robotRun(int angle, int runSpeed, int rotateSpeed_) {
  switch (angle) {
    case 0:
      motor1(+runSpeed + rotateSpeed_);
      motor2(-runSpeed + rotateSpeed_);
      motor3(-runSpeed + rotateSpeed_);
      motor4(+runSpeed + rotateSpeed_);
      break;
    case 1800:
      motor1(-runSpeed + rotateSpeed_);
      motor2(+runSpeed + rotateSpeed_);
      motor3(+runSpeed + rotateSpeed_);
      motor4(-runSpeed + rotateSpeed_);
      break;
    case 900:
      motor1(-runSpeed + rotateSpeed_);
      motor2(-runSpeed + rotateSpeed_);
      motor3(+runSpeed + rotateSpeed_);
      motor4(+runSpeed + rotateSpeed_);
      break;
    case -900:
      motor1(+runSpeed + rotateSpeed_);
      motor2(+runSpeed + rotateSpeed_);
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
}

int calculateCompensate() {
#ifdef ULTIMATE
  return calculateSlewRatePid();
#else
  return 0;
#endif
}

void onLoopKinematic() {
  if (speedMode == 1) {
    runSpeed = runSpeed1;
    rotateSpeed = rotSpeed1;  //////////////////////////////////////////////////
  } else if (speedMode == 2) {
    runSpeed = runSpeed2;
    rotateSpeed = rotSpeed2;  ///////////////////////////////////////////////////
  } else if (speedMode == 3) {
    runSpeed = runSpeed3;
    rotateSpeed = rotSpeed3;  ///////////////////////////////////////////////////
  }
  if (!UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1) {
    enableSetPoint = false;
    // robotRun(0, 0, calculateCompensate());
    robotRun(0, 0, 0);
  } else if (!UP && !DOWN && !RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(0, 0, -rotateSpeed);
  } else if (!UP && !DOWN && !RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(0, 0, rotateSpeed);
  } else if (UP && !DOWN && !RIGHT && !LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(0, runSpeed, 0);  //pinned
    else
      robotRun(0, runSpeed, calculateCompensate());  //pinned
  } else if (UP && !DOWN && !RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(0, runSpeed, -rotateSpeed);
  } else if (UP && !DOWN && !RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(0, runSpeed, rotateSpeed);
  } else if (!UP && DOWN && !RIGHT && !LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(1800, runSpeed, 0);  //pinned
    else
      robotRun(1800, runSpeed, calculateCompensate());  //pinned
  } else if (!UP && DOWN && !RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(1800, runSpeed, -rotateSpeed);
  } else if (!UP && DOWN && !RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(1800, runSpeed, rotateSpeed);
  } else if (!UP && !DOWN && RIGHT && !LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(900, runSpeed, 0);  //pinned
    else
      robotRun(900, runSpeed, calculateCompensate());  //pinned
  } else if (!UP && !DOWN && RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(900, runSpeed, -rotateSpeed);
  } else if (!UP && !DOWN && RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(900, runSpeed, rotateSpeed);
  } else if (!UP && !DOWN && !RIGHT && LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(-900, runSpeed, 0);  //pinned
    else
      robotRun(-900, runSpeed, calculateCompensate());  //pinned
  } else if (!UP && !DOWN && !RIGHT && LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(-900, runSpeed, -rotateSpeed);
  } else if (!UP && !DOWN && !RIGHT && LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(-900, runSpeed, rotateSpeed);
  } else if (UP && !DOWN && RIGHT && !LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(450, runSpeed, 0);  //pinned
    else
      robotRun(450, runSpeed, calculateCompensate());  //pinned
  } else if (UP && !DOWN && RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(450, runSpeed, -rotateSpeed);
  } else if (UP && !DOWN && RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(450, runSpeed, rotateSpeed);
  } else if (UP && !DOWN && !RIGHT && LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(-450, runSpeed, 0);  //pinned
    else
      robotRun(-450, runSpeed, calculateCompensate());  //pinned
  } else if (UP && !DOWN && !RIGHT && LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(-450, runSpeed, -rotateSpeed);
  } else if (UP && !DOWN && !RIGHT && LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(-450, runSpeed, rotateSpeed);
  } else if (!UP && DOWN && RIGHT && !LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(1350, runSpeed, 0);  //pinned
    else
      robotRun(1350, runSpeed, calculateCompensate());  //pinned
  } else if (!UP && DOWN && RIGHT && !LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(1350, runSpeed, -rotateSpeed);
  } else if (!UP && DOWN && RIGHT && !LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(1350, runSpeed, rotateSpeed);
  } else if (!UP && DOWN && !RIGHT && LEFT && !L1 && !R1) {
    if (!enableSetPoint) {
      enableSetPoint = true;
      setPoint = compassData;
    }
    if (!strategyPinned)
      robotRun(-1350, runSpeed, 0);  //pinned
    else
      robotRun(-1350, runSpeed, calculateCompensate());  //pinned
  } else if (!UP && DOWN && !RIGHT && LEFT && !L1 && R1) {
    enableSetPoint = false;
    robotRun(-1350, runSpeed, -rotateSpeed);
  } else if (!UP && DOWN && !RIGHT && LEFT && L1 && !R1) {
    enableSetPoint = false;
    robotRun(-1350, runSpeed, rotateSpeed);
  }
}
#endif /* INC_BKD_ARD_Kinematic_Basic_H_ */
