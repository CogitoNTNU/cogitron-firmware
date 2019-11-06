#include "Arduino.h"

String serialResponse = "";
char sz[] = "";
int n_tokens = 0;
String token_buffer[16];

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
}

int setMotor(int motor, int speed) {
  Serial.println("setMotorAck");  
}

int setMotors(int motor1, int motor2, int speed){
  Serial.println("setMotorsAck");
}

int moveServo(int servoId, int degree){
  Serial.println("moveServoAck");
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
