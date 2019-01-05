#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Servo *mServo1 = mMotorDriver.getServo(1);
Emakefun_Servo *mServo2 = mMotorDriver.getServo(2);
Emakefun_Servo *mServo3 = mMotorDriver.getServo(3);
Emakefun_Servo *mServo4 = mMotorDriver.getServo(4);
void setup()
{
  mMotorDriver.begin(50);
}

void loop()
{
  mServo1->writeServo(0);
  mServo2->writeServo(0);
  mServo3->writeServo(0);
  mServo4->writeServo(0);
  delay(1000);
  mServo1->writeServo(90);
  mServo2->writeServo(90);
  mServo3->writeServo(90);
  mServo4->writeServo(90);
  delay(1000);
  mServo1->writeServo(180);
  mServo2->writeServo(180);
  mServo3->writeServo(180);
  mServo4->writeServo(180);
  delay(1000);
}
