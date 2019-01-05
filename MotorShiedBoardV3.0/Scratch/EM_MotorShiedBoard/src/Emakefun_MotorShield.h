#ifndef _EMAKEFUN_MOTORSHIELD_h_
#define _EMAKEFUN_MOTORSHIELD_h_

#include <inttypes.h>
#include <Wire.h>
#include "IRremote.h"
#include "PS2X_lib.h"  //for v1.6
#include "Buzzer.h"
#include "RGBLed.h"
#include "Servo.h"
#include "nRF24L01.h"
#include "Sounds.h"

#define MOTOR_AIN1 3
#define MOTOR_BIN1 4
#define MOTOR_PWMA 5
#define MOTOR_PWMB 6

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

#define ENCODER_1_A 7
#define ENCODER_2_A 2

#define SERVO_PIN 7
#define RGB_PIN A3
#define ECHO_PIN A0
#define TRIG_PIN A1
#define IR_PIN 12
#define BUZZER_PIN 9

#define SERVO_MAX 1

#define PS2_DAT   12
#define PS2_CMD   11
#define PS2_SEL   10
#define PS2_CLK   13

#define NRF24L01_CE 10
#define NRF24L01_CSN 8

#define NRF_NAME "emakefun"
#define NRF_DATA_LEN 12
typedef enum
{
    E_RGB_ALL = 0,
    E_RGB_RIGHT = 1,
    E_RGB_LEFT = 2
} E_RGB_INDEX;

typedef enum
{
    E_RGB = 0,
    E_IR = 1,
    E_BUZZER = 2,
    E_PS2X = 3,
    E_NRF24L01 = 4,
    E_ULTRASONIC = 5,
    E_EXTERN_PIN = 6,
    E_SENSOR_MAX,
} E_SENSOR_INDEX;

class Emakefun_MotorShield;

class Emakefun_Sensor
{
public:
  Emakefun_Sensor(void);
  friend class Emakefun_MotorShield;
  IRremote  *mIrRecv;
  PS2X *mPs2x;
  Buzzer *mBuzzer;
  RGBLed *mRgb;
  Nrf24l *mNRF24L01;
  void SetRgbColor(E_RGB_INDEX index = E_RGB_ALL, long Color = RGB_WHITE);
  void Sing(byte songName);
  uint16_t GetUltrasonicDistance(void);
private:
  uint8_t IrPin;      // Infrared remoter pin
  uint8_t BuzzerPin;  // Buzzer pin
  uint8_t RgbPin;     // Rgb pin
  uint8_t EchoPin,TrigPin;
  uint8_t Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin;    // for Ps2 remoter
  uint8_t P1, P2, P3, P4, P5;    // for Infrared tracing pin
  Emakefun_MotorShield *MC;
};


class Emakefun_DCMotor
{
 public:
  Emakefun_DCMotor(void);
  friend class Emakefun_MotorShield;
  void run(uint8_t);
  void setSpeed(uint8_t);
 private:
  uint8_t IN1pin, PWMpin;
  Emakefun_MotorShield *MC;
  uint8_t motornum;
};

class Emakefun_EncoderMotor {
 public:
  Emakefun_EncoderMotor(void);
  friend class Emakefun_MotorShield;
  void setSpeed(uint16_t);
  void release(void);

 private:
  uint8_t IN1pin, PWMpin , ENCODERpin;
  uint8_t pluse;
  Emakefun_MotorShield *MC;
  uint8_t encodernum;
};

class Emakefun_Servo
{
public:
  Emakefun_Servo(void);
  friend class Emakefun_MotorShield;
  void writeServo(uint8_t angle);
  uint8_t readDegrees();
private:
  uint8_t PWMpin;
  Servo mServo;
  Emakefun_MotorShield *MC;
  uint8_t servonum, currentAngle;
};

class Emakefun_MotorShield
{
  public:
    Emakefun_MotorShield(void);
    friend class Emakefun_DCMotor;
    void begin(uint16_t freq = 1600);
    void setPWM(uint8_t pin, uint16_t val);
    void setPin(uint8_t pin, uint8_t val);
    Emakefun_DCMotor *getDCMotor(uint8_t num, uint8_t in1, uint8_t pwm);
    Emakefun_EncoderMotor *getEncoder(uint8_t num, uint8_t in1, uint8_t pwm, uint8_t encoder);
    Emakefun_Servo *getServo(uint8_t n, uint8_t pin);
    Emakefun_Sensor *getSensor(E_SENSOR_INDEX n);
 private:
    Emakefun_DCMotor dcmotors[2];
    Emakefun_EncoderMotor encoder[2];
    Emakefun_Servo servos[SERVO_MAX];
    Emakefun_Sensor sensors[E_SENSOR_MAX];
};

#endif
