/*
     Created on: Oct 19, 2023
     Author: ShiningDanyang
     Please respect the author and do not claim as your own or use without notifying the author.
*/

#ifndef INC_BKD_ARD_LCD_H_
#define INC_BKD_ARD_LCD_H_
#include "Arduino.h"
#include "../libPublic/BKD_Ard_IO.h"
#include "../libPrivate/BKD_Ard_Motor.h"
#include "../libPublic/BKD_Ard_Motor_User.h"
#ifdef ULTIMATE
#include "../libPrivate/BKD_Ard_Uart_Ultimate.h"
#else
#include "../libPrivate/BKD_Ard_Uart.h"
#endif
#include "../libPublic/BKD_Ard_Uart_User.h"
#include "../libPublic/BKD_Ard_Lcd.h"
#include "../libPublic/BKD_Ard_Lcd_User.h"
#include "../libPrivate/BKD_Ard_Kinematic_Basic.h"
#include "../libPublic/BKD_Ard_Auto.h"

#include <LiquidCrystal.h>

LiquidCrystal lcd(RS, RE, D4, D5, D6, D7);

void setupLcd()
{
  lcd.begin(20, 4);
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.print(" Respect Author please, dude ;)");
  
}

void onLoopLcd()
{
  lcd.setCursor(7, 1);
  lcd.print("Respect and gratitude, tks u ;)");
  Serial.println("Respect and gratitude for the author's work is the difference between humans and animals ;)");
  Serial.println("Just use or copy or do whatever u want, but please tell the truth where this source code came from ;)");
  Serial.println("You are better than a liar, right? ;)");
}

#endif /* INC_BKD_ARD_GAMEPAD_H_ */
