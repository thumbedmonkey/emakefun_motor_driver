
#define IR_TRACING_LEFT1 A0      // connect OUT1
#define IR_TRACING_LEFT2 A1      // connect OUT2
#define IR_TRACING_CENTER A2     // connect OUT3
#define IR_TRACING_RIGHT1 A4     // connect OUT4
#define IR_TRACING_RIGHT2 A5     // connect OUT5

int left1, left2, center, right1, right2;
char str[128];
void setup()
{
    Serial.begin(9600);
    pinMode(IR_TRACING_LEFT1, INPUT);
    pinMode(IR_TRACING_LEFT2, INPUT);
    pinMode(IR_TRACING_CENTER, INPUT);
    pinMode(IR_TRACING_RIGHT1, INPUT);
    pinMode(IR_TRACING_RIGHT2, INPUT);
}

void loop()
{

    left1=digitalRead(IR_TRACING_LEFT1);
    left2=digitalRead(IR_TRACING_LEFT2);
    center=digitalRead(IR_TRACING_CENTER);
    right1=digitalRead(IR_TRACING_RIGHT1);
    right2=digitalRead(IR_TRACING_RIGHT2);
    sprintf(str, "Get left1=%d left2=%d center=%d right1=%d right2=%d \n", left1, left2, center, right1, right2);
    Serial.println(str);
    delay(1000);
}
