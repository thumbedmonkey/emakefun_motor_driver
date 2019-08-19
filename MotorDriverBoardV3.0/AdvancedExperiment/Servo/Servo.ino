#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Servo *mServo5 = mMotorDriver.getServo(5);
Emakefun_Servo *mServo6 = mMotorDriver.getServo(6);
void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
}

void loop()
{
  mServo5->writeServo(0);
   mServo6->writeServo(0);
  delay(500);
  mServo5->writeServo(180);
   mServo6->writeServo(90);
  delay(500);
  mServo5->writeServo(0);
   mServo6->writeServo(180);
  delay(500);
  mServo5->writeServo(180);
   mServo6->writeServo(0);
  delay(500);
}
