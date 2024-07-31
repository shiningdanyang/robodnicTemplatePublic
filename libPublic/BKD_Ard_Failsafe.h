#ifndef INC_BKD_ARD_FAILSAFE_USER_H_
#define INC_BKD_ARD_FAILSAFE_USER_H_

extern void motorShoot(int shootSpeed);
extern uint8_t isConnected;
extern uint8_t isLiveCompass;

void failsafeActive()
{
  digitalWrite(upIntake, LOW);
  digitalWrite(downIntake, LOW);
  motorShoot(0);
  isConnected = 0;
}
#endif
