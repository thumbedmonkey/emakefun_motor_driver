#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Emakefun_MotorShield.h"

Emakefun_MotorShield::Emakefun_MotorShield(void) {
}

void Emakefun_MotorShield::begin(uint16_t freq) {
  // init PWM w/_freq
}

void Emakefun_MotorShield::setPWM(uint8_t pin, uint16_t value) {
    analogWrite(pin, value);
}
void Emakefun_MotorShield::setPin(uint8_t pin, uint8_t value) {
    digitalWrite(pin, value);
}

Emakefun_DCMotor *Emakefun_MotorShield::getDCMotor(uint8_t num, uint8_t in1, uint8_t pwm) {
  if (num > 2) return NULL;
  num--;
  if (dcmotors[num].motornum == 0) {
    // not init'd yet!
    dcmotors[num].motornum = num;
    dcmotors[num].MC = this;
    dcmotors[num].PWMpin = pwm;
    dcmotors[num].IN1pin = in1;
    pinMode(dcmotors[num].PWMpin, OUTPUT);
    pinMode(dcmotors[num].IN1pin, OUTPUT);
  }
  return &dcmotors[num];
}


Emakefun_EncoderMotor *Emakefun_MotorShield::getEncoder(uint8_t num, uint8_t in1, uint8_t pwm, uint8_t encoderpin) {
  if (num > 2) return NULL;
  num--;
  if (encoder[num].encodernum == 0) {
    // not init'd yet!
    encoder[num].encodernum = num;
    encoder[num].MC = this;
    encoder[num].IN1pin = in1;
    encoder[num].PWMpin = pwm;
    encoder[num].ENCODERpin = encoderpin;
    pinMode(encoder[num].PWMpin, OUTPUT);
    pinMode(encoder[num].IN1pin, OUTPUT);
    pinMode(encoder[num].ENCODERpin, INPUT);
  }
  return &encoder[num];
}

Emakefun_Servo *Emakefun_MotorShield::getServo(uint8_t num, uint8_t pin) {
  if (num > SERVO_MAX) return NULL;
  num--;
  if (servos[num].servonum == 0) {
    // not init'd yet!
    servos[num].servonum = num;
    servos[num].MC = this;
    servos[num].PWMpin = pin;
    pinMode(pin, OUTPUT);
    if (!servos[num].mServo.attached()) {
        servos[num].mServo.attach(pin);
    }
  }
  return &servos[num];
}

/******************************************
               SERVOS
******************************************/

Emakefun_Servo::Emakefun_Servo(void) {
  MC = NULL;
  servonum = 0;
  PWMpin = 0;
  currentAngle = 0;
}

void Emakefun_Servo::writeServo(uint8_t angle){
    mServo.write(angle);
}

uint8_t Emakefun_Servo::readDegrees(){
	return mServo.read();
}

/******************************************
               MOTORS
******************************************/

Emakefun_DCMotor::Emakefun_DCMotor(void) {
  MC = NULL;
  motornum = 0;
  PWMpin = IN1pin  = 0;
}

void Emakefun_DCMotor::run(uint8_t cmd) {
  switch (cmd) {
  case FORWARD:
    MC->setPin(IN1pin, HIGH);
    break;
  case BACKWARD:
    MC->setPin(IN1pin, LOW);  // take low first to avoid 'break'
    break;
  case RELEASE:
    MC->setPin(IN1pin, LOW);
    MC->setPWM(PWMpin, 0);
    break;
  }
}

void Emakefun_DCMotor::setSpeed(uint8_t speed) {
  MC->setPWM(PWMpin, 255);
}

/******************************************
               STEPPERS
******************************************/

Emakefun_EncoderMotor::Emakefun_EncoderMotor(void) {
   MC = NULL;
   encodernum = 0;
   PWMpin = IN1pin = ENCODERpin = 0;
}

void Emakefun_EncoderMotor::setSpeed(uint16_t speed) {
  MC->setPWM(PWMpin, (speed / 10) * 25.5);
}

void Emakefun_EncoderMotor::release(void) {
  MC->setPin(IN1pin, LOW);
  MC->setPWM(PWMpin, 0);
}

Emakefun_Sensor::Emakefun_Sensor(void) {
    MC = NULL;
    mIrRecv = NULL;
    mPs2x = NULL;
    mBuzzer = NULL;
    mRgb = NULL;
    IrPin = BuzzerPin = RgbPin = EchoPin = TrigPin = 0;
    Ps2xClkPin = Ps2xCmdPin = Ps2xAttPin = Ps2xDatPin = 0;
    P1 = P2 = P3 = P4 = P5 = 0;
}

void Emakefun_Sensor::SetRgbColor(E_RGB_INDEX index = E_RGB_ALL, long Color = RGB_WHITE)
{
    if (index == E_RGB_ALL) {
      mRgb->setColor(0, Color);
    } else {
      mRgb->setColor(index, Color);
    }
    mRgb->show();
}

void Emakefun_Sensor::Sing(byte songName)
{
  switch (songName) {
    case S_connection:
      mBuzzer->_tone(note_E5, 50, 30);
      mBuzzer->_tone(note_E6, 55, 25);
      mBuzzer->_tone(note_A6, 60, 10);
      //  _tone(9, 394);
      break;

    case S_disconnection:
      mBuzzer->_tone(note_E5, 50, 30);
      mBuzzer->_tone(note_A6, 55, 25);
      mBuzzer->_tone(note_E6, 50, 10);
      break;

    case S_buttonPushed:
      mBuzzer->bendTones (note_E6, note_G6, 1.03, 20, 2);
      delay(30);
      mBuzzer->bendTones (note_E6, note_D7, 1.04, 10, 2);
      break;

    case S_mode1:
      mBuzzer->bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
      break;

    case S_mode2:
      mBuzzer->bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
      break;

    case S_mode3:
      mBuzzer->_tone(note_E6, 50, 100); //D6
      mBuzzer->_tone(note_G6, 50, 80); //E6
      mBuzzer->_tone(note_D7, 300, 0); //G6
      break;

    case S_surprise:
      mBuzzer->bendTones(800, 2150, 1.02, 10, 1);
      mBuzzer->bendTones(2149, 800, 1.03, 7, 1);
      break;

    case S_OhOoh:
      mBuzzer->bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
      delay(200);

      for (int i = 880; i < 2000; i = i * 1.04) {
        mBuzzer->_tone(note_B5, 5, 10);
      }
      break;

    case S_OhOoh2:
      mBuzzer->bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);

      for (int i = 1880; i < 3000; i = i * 1.03) {
        mBuzzer->_tone(note_C6, 10, 10);
      }
      break;

    case S_cuddly:
      mBuzzer->bendTones(700, 900, 1.03, 16, 4);
      mBuzzer->bendTones(899, 650, 1.01, 18, 7);
      break;

    case S_sleeping:
      mBuzzer->bendTones(100, 500, 1.04, 10, 10);
      delay(500);
      mBuzzer->bendTones(400, 100, 1.04, 10, 1);
      break;

    case S_happy:
      mBuzzer->bendTones(1500, 2500, 1.05, 20, 8);
      mBuzzer->bendTones(2499, 1500, 1.05, 25, 8);
      break;

    case S_superHappy:
      mBuzzer->bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      mBuzzer->bendTones(5999, 2000, 1.05, 13, 2);
      break;

    case S_happy_short:
      mBuzzer->bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      mBuzzer->bendTones(1900, 2500, 1.05, 10, 8);
      break;

    case S_sad:
      mBuzzer->bendTones(880, 669, 1.02, 20, 200);
      break;

    case S_confused:
      mBuzzer->bendTones(1000, 1700, 1.03, 8, 2);
      mBuzzer->bendTones(1699, 500, 1.04, 8, 3);
      mBuzzer->bendTones(1000, 1700, 1.05, 9, 10);
      break;

    case S_fart1:
      mBuzzer->bendTones(1600, 3000, 1.02, 2, 15);
      break;

    case S_fart2:
      mBuzzer->bendTones(2000, 6000, 1.02, 2, 20);
      break;

    case S_fart3:
      mBuzzer->bendTones(1600, 4000, 1.02, 2, 20);
      mBuzzer->bendTones(4000, 3000, 1.02, 2, 20);
      break;
  }
}

uint16_t Emakefun_Sensor::GetUltrasonicDistance(void)
{
    uint16_t FrontDistance;
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    FrontDistance = pulseIn(EchoPin, HIGH) / 58.00;
    return FrontDistance;
}

Emakefun_Sensor *Emakefun_MotorShield::getSensor(E_SENSOR_INDEX n)
{
    switch (n) {
        case E_RGB:
            if (sensors[n].mRgb == NULL) {
                sensors[n].RgbPin = RGB_PIN;
                pinMode(RGB_PIN, OUTPUT);
                sensors[n].mRgb = new RGBLed(RGB_PIN, 2);
            }
            break;
        case E_IR:
            if (sensors[n].mIrRecv == NULL) {
                sensors[n].IrPin = IR_PIN;
                pinMode(IR_PIN, INPUT);
                sensors[n].mIrRecv = new IRremote (IR_PIN);
                sensors[n].mIrRecv->begin();  // Initialize the infrared receiver
            }
            break;
        case E_BUZZER:
            if (sensors[n].mBuzzer == NULL) {
                sensors[n].BuzzerPin = BUZZER_PIN;
                sensors[n].mBuzzer = new Buzzer(BUZZER_PIN);
            }
            break;
        case E_PS2X:
            if (sensors[n].mPs2x == NULL) {
                sensors[n].mPs2x = new PS2X();
                sensors[n].Ps2xClkPin = PS2_CLK;
                sensors[n].Ps2xCmdPin = PS2_CMD;
                sensors[n].Ps2xAttPin = PS2_SEL;
                sensors[n].Ps2xDatPin = PS2_DAT;
                sensors[n].mPs2x->config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
            }
            break;
        case E_NRF24L01:
            if (sensors[n].mNRF24L01 == NULL) {
                sensors[n].mNRF24L01 = new Nrf24l(NRF24L01_CE, NRF24L01_CSN);
                sensors[n].mNRF24L01->spi = &MirfHardwareSpi;
                sensors[n].mNRF24L01->init();
                sensors[n].mNRF24L01->setRADDR(NRF_NAME); //Set your own address (receiver address) 
                sensors[n].mNRF24L01->payload = NRF_DATA_LEN;
                sensors[n].mNRF24L01->channel = 90;             //Set the used channel
                sensors[n].mNRF24L01->config();
            }
            break;
        case E_ULTRASONIC:
            sensors[n].EchoPin = ECHO_PIN;
            sensors[n].TrigPin = TRIG_PIN;
            pinMode(ECHO_PIN, INPUT);
            pinMode(TRIG_PIN, OUTPUT);
            break;
  }
   sensors[n].MC = this;
  return &sensors[n];
}

