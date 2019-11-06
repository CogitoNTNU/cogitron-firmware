#include "Arduino.h"

String serialResponse = "";
char sz[] = "";
int n_tokens = 0;
String token_buffer[16];

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
}

int drive_forward(int dist) {
  Serial.println("Driving forward!");  
}

int handle_command() {
  if(n_tokens > 0) {
    if(token_buffer[0].equals("motor")){
      if(n_tokens == 2) {
        drive_forward(token_buffer[1].toInt());  
      }
    }
  }
}

void loop()
{
  Serial.println("rangeSense;0;20");
  
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
