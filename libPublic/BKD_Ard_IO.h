/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/
#ifndef INC_BKD_ARD_IO_H_
#define INC_BKD_ARD_IO_H_
#include "Arduino.h"

#define upIntake    34
#define downIntake  36
#define dragFlag    38
#define chainDriver 32
#define motorLoad   40
#define npn1        A0
#define npn2        A7
#define buttonAuto  A15

void setupGpio()  
{ 
  pinMode(upIntake, OUTPUT);
  pinMode(downIntake, OUTPUT);
  pinMode(dragFlag, OUTPUT);
  pinMode(chainDriver, OUTPUT);
  pinMode(motorLoad, OUTPUT);
  pinMode(npn1, INPUT_PULLUP);
  pinMode(npn2, INPUT_PULLUP);
  pinMode(buttonAuto, INPUT_PULLUP);
}

#endif /* INC_BKD_ARD_IO_ */
