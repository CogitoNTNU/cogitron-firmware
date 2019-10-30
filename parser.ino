#include "Arduino.h"

String serialResponse = "";
char sz[] = "";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
}

void loop()
{
  if ( Serial.available()) {
    serialResponse = Serial.readStringUntil('\r\n');
    
    char buf[sizeof(sz)];
    serialResponse.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str;
    while ((str = strtok_r(p, ";", &p)) != NULL)
      Serial.println(str);
  }
}
