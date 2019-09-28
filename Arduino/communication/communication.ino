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



String message = "";
MotorControl driver;

void setup() {
  driver = MotorControl();
  Serial.begin(9600);
  Serial.write("Connected");
}


void loop() {

  while (Serial.available() > 0) {
    byte received = Serial.read();
    message += char(received);
  }

  if (message != "") {
    outgoingMessage(message);
    message = ""; 
  }
}

void outgoingMessage(String message){
  for(int i=0; i<message.length(); i++){
    Serial.write((byte)message[i]);
  }
         
}
