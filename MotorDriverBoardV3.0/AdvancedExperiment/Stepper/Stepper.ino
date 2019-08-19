#include "Emakefun_MotorDriver.h"



Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_StepperMotor *StepperMotor_1 = mMotorDriver.getStepper(200,1);




 
void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin();

}

void loop()
{
  StepperMotor_1->setSpeed(50);
 StepperMotor_1->step(200,1, 1);
 delay(1000);
 StepperMotor_1->setSpeed(300);
  StepperMotor_1->step(200,1, 1);
 delay(1000);



}
