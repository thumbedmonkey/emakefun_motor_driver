
#include "Servo.h"


int E1 = 4; //Bin1
int M1 = 2; //Bin2
int E2 = 6; //PWMB
int M2 = 7; //STBY
int servo_pin = 5;
Servo ForwardServo;
 
   
void setup()
{
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  ForwardServo.attach(servo_pin);
  ForwardServo.write(90);
}

void loop()
{
  int left1,centre,right1,left2,right2;
  left1=analogRead(A0);
  left2=analogRead(A1);
  centre=analogRead(A2);
  right1=analogRead(A4);
  right2=analogRead(A5);


  if((right1 >= 900)&&(right2 >= 900)&&(centre <= 20)&&(left2 >= 900)&&(left1 >= 900))//*******forward*******//
  {
    ForwardServo.write(90);
    Serial.println("go forward");
    int val=200;
    digitalWrite(E1,HIGH);
    digitalWrite(M1, LOW); //the speed value of motorA is val
    analogWrite(E2,val);
    digitalWrite(M2,HIGH); //the speed value of motorA is val
  }

  else  if((right1 <= 20)&&(centre >= 900)&&(left1 >= 900)&&(left2 >= 900)&&(right2 >= 900))//***turn right1***//
  {
    Serial.println("right1");
    ForwardServo.write(125);
    int val=70;
    digitalWrite(E1,HIGH);
    digitalWrite(M1, LOW); //the speed value of motorA is val
    analogWrite(E2,val);
    digitalWrite(M2,HIGH); //the speed value of motorA is val
   //delay(200);
   
  }
   else  if((right1 >= 900)&&(right2 >= 900)&&(centre >= 900)&&(left1 <= 20)&&(left2 >= 900))//***Turn left1***//
   {
     ForwardServo.write(45);
     Serial.println("left1");
     int val=70;
     digitalWrite(E1,HIGH);
     digitalWrite(M1, LOW); //the speed value of motorA is val
     analogWrite(E2,val);
     digitalWrite(M2,HIGH); //the speed value of motorA is val
    //delay(200); 
    }
    else if((right2 >= 900)&&(centre >= 900)&&(left2 <= 20)&&(right1= 900)&&(left1 >= 900))//***Turn left2***//
  {
    Serial.println("left2");
    ForwardServo.write(50);
    int val=70;
    digitalWrite(E1,HIGH);
    digitalWrite(M1, LOW); //the speed value of motorA is val
    analogWrite(E2,val);
    digitalWrite(M2,HIGH); //the speed value of motorA is val
   
  }

   else  if((right2 <= 20)&&(centre >= 900)&&(left2 >= 900)&&(left1 >= 900)&&(right1 >= 900))//***turn right2***//
   {
     ForwardServo.write(120);
     Serial.println("right2");
     int val=70;
     digitalWrite(E1,HIGH);
     digitalWrite(M1, LOW); //the speed value of motorA is val
     analogWrite(E2,val);
     digitalWrite(M2,HIGH); //the speed value of motorA is val

  }

  else if((centre <= 20)&&(left2 <= 20)&&(right2 <= 20)&&(left1 <= 20)&&(right1 <= 20))//*******Stop*******//
  {
    ForwardServo.write(90);
    Serial.println("stop");
    int val=0;
    digitalWrite(E1,HIGH);
    digitalWrite(M1, LOW); //the speed value of motorA is val
    analogWrite(E2,val);
    digitalWrite(M2,LOW); //the speed value of motorA is val
  }
}
