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
  lcd.print(" Danyang's Ecosystem");
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.setCursor(12, 1);
  lcd.print("live ");
  lcd.setCursor(6, 1);
  lcd.print("     ");
  lcd.setCursor(0, 2);
  lcd.print("Run:");
  lcd.setCursor(10, 2);
  lcd.print("Shoot:");
  lcd.setCursor(0, 3);
  lcd.print("Enc:");
}

void onLoopLcd()
{
  lcd.setCursor(7, 1);
  lcd.print(compassData);
  lcd.setCursor(5, 2);
  lcd.print(runSpeed);
  lcd.setCursor(17, 2);
  lcd.print(shootSpeed);
  lcd.setCursor(4, 3);
  lcd.print("          ");
  lcd.setCursor(4, 3);
  lcd.print(enc_motor);
  lcd.setCursor(19, 1);
  lcd.print(isLiveCompass);
}

#endif /* INC_BKD_ARD_GAMEPAD_H_ */
