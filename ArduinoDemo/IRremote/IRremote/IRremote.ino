#include "Buzzer.h"
#include "RGBLed.h"
#include "Servo.h"
#include "IRremote.h"
int motor_L2 = 4; //Bin1
int motor_L1 = 2; //Bin2
int PWMB = 6; //PWMB
int STBY = 7; //STBY
int servo_pin = 5;
Servo ForwardServo;

double Speed = 100;

int i = 40;

//long Bluetooth_mode = 0xFF629D;//*****************************************蓝牙模式
//long IR_mode = 0xFFA25D;//************************************************红外遥控
//long Tracking_mode = 0xFFE21D;//******************************************红外循迹
//long Ultrasound_mode = 0xFF22DD;//****************************************超声波壁障
//long PS2X_mode = 0xFFC23D;//**********************************************PS2手柄
//
//long forward = 0xFF02FD;
//long back = 0xFF9867;
//long stop = 0xFFA857;
//long left = 0xFFE01F;
//long right = 0xFF906F;
//
//long Speed_increase = 0xFFB04F;
//long Speed_1 = 0xFF30CF;
//long Speed_2 = 0xFF18E7;
//long Speed_3 = 0xFF7A85;
Buzzer buzzer;
IRremote ir;
RGBLed rgbled_A3(7,A3);
void setup()
{
  Serial.begin(9600);
  ir.begin(); 
 pinMode(STBY, OUTPUT);
 pinMode(motor_L1, OUTPUT);
 pinMode(motor_L2, OUTPUT);
  ForwardServo.attach(servo_pin);
  ForwardServo.write(90);

}

void move(int direction )
{
     
      if(direction == 1)
      {
          digitalWrite(motor_L2,HIGH);
          digitalWrite(motor_L1, LOW); //the speed value of motorA is val
          digitalWrite(STBY,HIGH); //the speed value of motorA is val
      }
      else if(direction == 2)
      {
          digitalWrite(motor_L2,LOW);
          digitalWrite(motor_L1,HIGH); //the speed value of motorA is value
          digitalWrite(STBY,HIGH); //the speed value of motorA is val  
      }
      else if(direction == 3)
      {
          digitalWrite(motor_L2,LOW);
          digitalWrite(motor_L1,HIGH); //the speed value of motorA is value
          digitalWrite(STBY,HIGH); //the speed value of motorA is val  
      }    
   }


   
void loop()
{

 if(ir.keyPressed(24))
    {
     ForwardServo.write(90);
     move(1);
     analogWrite(PWMB,Speed);
     rgbled_A3.setColor(0,0,Speed-35,0);
     rgbled_A3.show(); 
    }
    else{
        if(ir.keyPressed(82))
        {
          ForwardServo.write(90);
           move(2);
           analogWrite(PWMB,Speed);
           rgbled_A3.setColor(0,Speed-35,Speed-35,Speed-35);
           rgbled_A3.show(); 
        }
        else{
            if(ir.keyPressed(8))
            {
              ForwardServo.write(50);
               move(1);
               analogWrite(PWMB,Speed);
               rgbled_A3.setColor(2,25,15,0);
               rgbled_A3.setColor(1,0,0,0);
               rgbled_A3.show(); 
            }
            else{
                 if(ir.keyPressed(90))
                 {
                  ForwardServo.write(115);
                   move(1);
                   analogWrite(PWMB,Speed);
                   rgbled_A3.setColor(1,25,15,0);
                   rgbled_A3.setColor(2,0,0,0);
                   rgbled_A3.show(); 
                }
                else{
                    if(ir.keyPressed(22))
                    {
                       i=i+10;                    
                      if (i>=255)
                      {
                         i=255;
                          buzzer.tone(2000, i);
                       }  
                         Speed = i;
                         Serial.println(Speed);//The hexadecimal line feed output code
                         buzzer.tone(3000, i);
                         //return;
                        
                    }
                    
                    else{
                        if(ir.keyPressed(13))
                        {
                            i=i-10;                    
                      if (i<=40)
                      {
                      i=40;
                       buzzer.tone(2000, i);
                       }  
                         Speed = i;
                         Serial.println(Speed);//The hexadecimal line feed output code
                         buzzer.tone(3000, i);
                        }
                      
                            else{
                                ForwardServo.write(90);
                                move(3);
                                analogWrite(PWMB,0);
                                rgbled_A3.setColor(0,Speed-35,0,0);
                                rgbled_A3.show();   
                               }
                        }
                    }
                
            }
        }
    }
    
  
}





