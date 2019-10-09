
//char buf[200] = {};

void setup() {
  Serial.begin(9600);
  Serial.write("Connected\n");
}


void loop() {
  incomingMessage();
  //outgoingMessage();
}

void incomingMessage(){
  //int readForN = Serial.read();
  int incomingByte;
  incomingByte = Serial.read();

    if(incomingByte != -1){
      char buf[200] = {};
      Serial.readBytes(buf, incomingByte);

      String message = "";
      
      for(int i = 0; i <= incomingByte; i++){
          message += buf[i];
      }
      
      //Serial.print(message);
      handleMessage(message);
    }
}

void handleMessage(String message){
     outgoingMessage("Arduino got: " + message);
}

void outgoingMessage(String message){
  Serial.print(message);
}
