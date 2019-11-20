#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#include <NewPing.h>



Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



String serialResponse = "";
char sz[] = "";
int n_tokens = 0;
String token_buffer[16];

Adafruit_DCMotor *motorLeft = AFMS.getMotor(1);
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);

Adafruit_DCMotor* motors[] = {
  motorLeft,
  motorRight
};

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 60 // Analog servos run at ~60 Hz updates

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  AFMS.begin();
  pwm.begin();

  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz updates

  
  delay(10);

}

int setMotor(int motor, int speed) {
  if(motor < 2) {
    motors[motor]->setSpeed(speed);
    
    if(speed > 0)
      motors[motor]->run(FORWARD);
    else
      motors[motor]->run(RELEASE);
      
    Serial.println("setMotorAck");  
  }
}

int setMotors(int motor1, int motor2, int speed){
  motors[0]->setSpeed(motor1);
  motors[1]->setSpeed(motor2);
   
  if(motor1 > 0)
      motors[0]->run(FORWARD);
    else
      motors[0]->run(RELEASE);
  
  if(motor2 > 0)
      motors[1]->run(FORWARD);
    else
      motors[1]->run(RELEASE);
    
  Serial.println("setMotorsAck");
}

int moveServo(int servoId, int degree){
  int pulseLength = map(degree, 0, 180, SERVOMIN, SERVOMAX);

  Serial.println("moveServoAck");
  pwm.setPWM(servoId, 0, pulseLength);
}

int getMotor(int motorId, int speed){
  Serial.println("getMotor");
}

int handle_command() {
  if(n_tokens > 0) {
    
    if(token_buffer[0].equals("setMotor")){
      if(n_tokens == 3) {
        setMotor(token_buffer[1].toInt(), token_buffer[2].toInt());  
      } 
    } else if(token_buffer[0].equals("setMotors")){
      if(n_tokens == 4){
        setMotors(token_buffer[1].toInt(), token_buffer[2].toInt(), token_buffer[3].toInt());
      }
    } else if(token_buffer[0].equals("moveServo")){
      if(n_tokens == 3){
        moveServo(token_buffer[1].toInt(),token_buffer[2].toInt());
      }
    } else if(token_buffer[0].equals("getMotor")){
      if(n_tokens == 3){
        getMotor(token_buffer[1].toInt(), token_buffer[2].toInt());
      }
    }
  }
}

void loop()
{
  //Serial.println("rangeSense;0;20");
  
  if ( Serial.available()) {
    serialResponse = Serial.readStringUntil('\r\n');
    
    char buf[sizeof(sz) * 256];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str;
    n_tokens = 0;
    
    while ((str = strtok_r(p, ";", &p)) != NULL) {
      token_buffer[n_tokens] = str;
      n_tokens++;
    }
    handle_command();
  }
  
  delay(100);
}
