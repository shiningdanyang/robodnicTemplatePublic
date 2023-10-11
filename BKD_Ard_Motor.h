#ifndef INC_BKD_ARD_MOTOR_H_
#define INC_BKD_ARD_MOTOR_H_

#define R_PWM1  44
#define L_PWM1  2
#define R_PWM2  10
#define L_PWM2  9
#define R_PWM3  8
#define L_PWM3  7
#define R_PWM4  6
#define L_PWM4  5

int speedMode    = 3;
int realRunSpeed = 0;
int runSpeed     = 0;
int runSpeed1    = 200;/////////////////////////////////////////////
int runSpeed2    = 150;////////////////////////////////////////////
int runSpeed3    = 100;////////////////////////////////////////////
int rotateSpeed  = 0;
int counterAcc   = 0;

void motor1(int speed) {
#ifdef MECANUM
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0) {
    analogWrite(R_PWM1, abs(speed));
    digitalWrite(L_PWM1, 0);
  }
  else
  {
    digitalWrite(R_PWM1, 0);
    analogWrite(L_PWM1, abs(speed));
  }
#endif
  //  Serial.print(speed);
  //  Serial.print(" ");
}

void motor2(int speed) {
#ifdef MECANUM
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0)
  {
    analogWrite(R_PWM2, abs(speed));
    digitalWrite(L_PWM2, 0);
  }
  else
  {
    digitalWrite(R_PWM2, 0);
    analogWrite(L_PWM2, abs(speed));
  }
#endif
  //  Serial.print(speed);
  //  Serial.print(" ");
}

void motor3(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed < 0)
  {
    analogWrite(R_PWM3, abs(speed));
    digitalWrite(L_PWM3, 0);
  }
  else
  {
    digitalWrite(R_PWM3, 0);
    analogWrite(L_PWM3, abs(speed));
  }
  //  Serial.print(speed);
  //  Serial.print(" ");
}

void motor4(int speed) {
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 0)
  {
    analogWrite(R_PWM4, abs(speed));
    digitalWrite(L_PWM4, 0);
  }
  else
  {
    digitalWrite(R_PWM4, 0);
    analogWrite(L_PWM4, abs(speed));
  }
  //  Serial.print(speed);
  //  Serial.print(" ");
}

void testMotor()
{
  while(1)
  {
    motor1(100);
    motor2(0);
    motor3(0);
    motor4(0);
    delay(1000);
    motor1(0);
    motor2(100);
    motor3(0);
    motor4(0);
    delay(1000);
    motor1(0);
    motor2(0);
    motor3(100);
    motor4(0);
    delay(1000);
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(100);
    delay(1000);
    motor1(0);
    motor2(0);
    motor3(0);
    motor4(0);
    delay(1000);
  }
}

#endif /* INC_BKD_MOTOR_H_ */
