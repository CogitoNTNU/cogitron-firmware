
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
#include <NewPing.h>

Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);
//NewPing Servo[
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void FullSpeed(int s){
  if(s < 0){
    myMotorL->setSpeed(-s);
    myMotorR->setSpeed(-s);
    myMotorL->run(BACKWARD);
    myMotorR->run(BACKWARD);
}
  else if(s > 255){s = 255;}

  else{
    myMotorL->setSpeed(s);
    myMotorR->setSpeed(s);
    myMotorL->run(FORWARD);
    myMotorR->run(FORWARD);
    
  }
}
/*
int moveServo(int n,int deg){
  servo[n].write(deg);
}
*/
void loop() {

  FullSpeed(100);
  /*
  if(text == forward[1){
    forward()
  }
  */
}
  // put your main code here, to run repeatedly:
  //les inn function fra port
  
