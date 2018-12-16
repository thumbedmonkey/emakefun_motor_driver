#include "Emakefun_MotorShield.h"

Emakefun_MotorShield mMotorShield = Emakefun_MotorShield();
Emakefun_DCMotor *motor_1 = mMotorShield.getDCMotor(1, MOTOR_AIN1, MOTOR_PWMA);
Emakefun_DCMotor *motor_2 = mMotorShield.getDCMotor(2, MOTOR_BIN1, MOTOR_PWMB);
Emakefun_Servo *servo = mMotorShield.getServo(1, SERVO_PIN);
Emakefun_Sensor *rgb = mMotorShield.getSensor(E_RGB);
Emakefun_Sensor *ir = mMotorShield.getSensor(E_IR);

void setup()
{
    Serial.begin(9600);
   motor_1->setSpeed(100);
    motor_2->setSpeed(100);
    rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
   // while(1);
}

void loop()
{
   servo->writeServo(0);
   motor_1->run(1);
  // motor_2->run(1);
   delay(2000);
   servo->writeServo(180);
  // motor_1->run(2);
  // motor_2->run(2);
   delay(2000);
}
