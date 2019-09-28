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

  Serial.print(message);
  if (message != "") {
    messageHandler(message);
    message = ""; 
  }
}

void messageHandler(String message){
    while(true){
         Serial.write("test");
    }

}
