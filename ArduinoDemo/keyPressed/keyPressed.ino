#include "IRremote.h"

IRremote ir;

unsigned char r;
  
void setup()
{
  Serial.begin(9600);
  ir.begin(); 
 
} 
void loop()
{
  
 ir.keyPressed(r);
    
}



