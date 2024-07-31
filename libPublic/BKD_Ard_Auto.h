/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/
#ifndef BKD_ARD_AUTO_H
#define BKD_ARD_AUTO_H
#include "Arduino.h"
#include "../libPrivate/BKD_Ard_Motor.h"
#include "../libPublic/BKD_Ard_IO.h"
#include <Encoder.h>

Encoder myEnc(20, 18);
int enc_motor = 0;
int enc_target = 70;
bool sate_auto = false;

void runAutomatically()
{
  long newPosition = myEnc.read();
  enc_motor = newPosition;
  Serial.print(enc_motor);
  Serial.print("  ");
  Serial.println();
}


#endif /* BKD_ARD_AUTO_H */
