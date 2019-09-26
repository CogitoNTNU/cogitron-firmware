
void setup() {
  Serial.begin(9600);
  Serial.write("Connected");
}

void loop() {
  
    if(Serial.available() > 0) {
        byte received = Serial.read();
        
        //leser en og en byte om gangen og avsluttes med byte= 10 
        //må samle disse bytesene for å lage en samlet beskjed.
       
        Serial.write(received);
    }

}
