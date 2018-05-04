
#include "RGBLed.h"
RGBLed rgbled_A3(7,A3);
void setup()
{

}

void loop()
{
     rgbled_A3.setColor(1,10,10,10);
     rgbled_A3.show();
}

