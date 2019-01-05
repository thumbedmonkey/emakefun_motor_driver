#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Servo *mServo1 = mMotorDriver.getServo(1);
void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);
}

void loop()
{
   mServo1->writeServo(0);
   delay(2000);
   mServo1->writeServo(180);
   delay(2000);
}
