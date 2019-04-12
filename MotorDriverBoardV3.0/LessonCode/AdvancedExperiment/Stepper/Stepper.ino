#include "Emakefun_MotorDriver.h"



Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_StepperMotor *StepperMotor_1 = mMotorDriver.getStepper(200,1);
Emakefun_StepperMotor *StepperMotor_2 = mMotorDriver.getStepper(200,2);



 
void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);

}

void loop()
{
 StepperMotor_1->step(50,FORWARD, SINGLE);
 StepperMotor_2->step(50,FORWARD, SINGLE);

}
