


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}


void loop() {
  int * incomingMsg;
  
  if(Serial.available() >0){
    incomingMsg = incomingMessage(); 
  }

  if(!(incomingMsg)){
    handleMessage(incomingMsg);
  }
  //outgoingMessage();
  blinkLed();
}


void blinkLed(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}


int * incomingMessage(){
  int incomingByte = Serial.read();
  int message[incomingByte] = {};
  
    if(incomingByte != -1){
      char buf[200] = {};
      Serial.readBytes(buf, incomingByte);
      for(int i = 0; i <= incomingByte; i++){
          message[i] = (int)buf[i];
      }
    }

    return message;
}

void handleMessage(int message[]){
     outgoingMessage(message);
}

void outgoingMessage(int * message){
  byte outgoingByte = 3;//(byte) (sizeof(message) / sizeof(message[0]));
  Serial.write(outgoingByte);
  
  for(int i=1; i<sizeof(message) / sizeof(message[0]); i++){
    Serial.write(message[i]);
  }

}
