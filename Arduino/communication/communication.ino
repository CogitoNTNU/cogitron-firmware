class MotorControl {
  public:
    void goForward() {
      Serial.print("Forward");
    }

    void reverse() {
      Serial.print("Reverse");
    }

    void turnLeft() {
      Serial.print("Turn left");
    }

    void turnRight() {
      Serial.print("Turn right");
    }

    void pivotLeft() {
      Serial.print("Pivot left");
    }

    void pivotRight() {
      Serial.print("Pivot right");
    }

    void stopMotor() {
      Serial.print("Stop motor");
    }
};



String messageOut = "";

MotorControl driver;

void setup() {
  driver = MotorControl();
  Serial.begin(9600);
  Serial.write("Connected\n");
}


void loop() {
  readMessage();
  if(messageOut != ""){
    //outgoingMessage(messageOut);
  }
}

void readMessage(){
  int check = Serial.peek();
  String incomingMessage;
  
  while(check > -1){
     byte in = Serial.read();
     incomingMessage += (char) in;
     check = Serial.peek();
  }
  outgoingMessage(incomingMessage);

  
}

void outgoingMessage(String message){
  for(int i=0; i<message.length(); i++){
    Serial.write(message[i]);
  }
}
