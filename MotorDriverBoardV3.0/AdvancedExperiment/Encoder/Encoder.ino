#include "Emakefun_MotorDriver.h"

static volatile int Encoder1Pulse = 0, Encoder2Pulse = 0;

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(1);
Emakefun_EncoderMotor *EncodeMotor_2 = mMotorDriver.getEncoderMotor(2);

void encoder1(void)
{
  Encoder1Pulse++;
  Serial.print("Encoder1Pulse");
  Serial.println(Encoder1Pulse);
}

void encoder2(void)
{
  Encoder2Pulse++;
  Serial.print("Encoder2Pulse");
  Serial.println(Encoder2Pulse);
}
 
void setup()
{
    Serial.begin(9600);
    EncodeMotor_1->init(encoder1);
    EncodeMotor_2->init(encoder2);
}

void loop()
{
  
}
