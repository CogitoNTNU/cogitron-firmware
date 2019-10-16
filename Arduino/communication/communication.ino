


void setup() {
  Serial.begin(9600);
  Serial.write("Connected");
  pinMode(13, OUTPUT);
}


void loop() {
  String incomingMsg = "";
  
  if(Serial.available() >0){
    incomingMsg = incomingMessage(); 
  }

  if(incomingMsg != ""){
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


String incomingMessage(){
  int incomingByte = Serial.read();
  String message = "";
  
    if(incomingByte != -1){
      char buf[200] = {};
      Serial.readBytes(buf, incomingByte);
      for(int i = 0; i <= incomingByte; i++){
          message += buf[i];
      }
    }
    return message;
}

void handleMessage(String message){
     outgoingMessage(message);
}

void outgoingMessage(String message){
  for(int i=0; i<message.length(); i++){
    Serial.write(message[i]);
  }

}
