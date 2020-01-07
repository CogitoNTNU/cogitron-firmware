#include <NewPing.h>    //Library that allows reading from multiple ultrasonic sensors
#include <ADXL335.h>
#include <SK6812.h>


const int inputPin = 3;            // Input pin (for PIR sensor - pyroelectric infrared sensor)
int pirState = LOW;               // Starting by assuming no motion detected
int val = 0;                     // Variable for reading the pin status (reads from input pin)

const int xpin = A0; //x-axis on accelerometer
const int ypin = A1; //y-axis
const int zpin = A2; //z-axis
const int cal = 332; //calibration constant for the accelerometer values

int xAxis;
int yAxis;
int zAxis;

const int sonars = 2;                 // Number of ultrasonic sensors
const int max_distance = 200;        // Max distance sensor can read (in cm)
const int pingInterval = 33;        // Milliseconds between each ping
  
unsigned long pingTimer[sonars];  // When each pings
unsigned int cm[sonars];         // Store ping distances.
uint8_t currentSensor = 0;      // Which sensor is active.

SK6812 LED(8);

RGBW color1 = {255, 0, 129, 255}; // 255 blue, 50 white

String serialResponse = "";
char sz[] = "";
int n_tokens = 0;
String token_buffer[16];


 
NewPing sonar[sonars] = { // Sensor object array for the two sensors
  //NewPin(TrigPin, EchoPin, max_distance) this is the format
  NewPing(11, 10, max_distance), //Top sensor
  NewPing(7, 6, max_distance), //Bottom sensor (angled sensor)
};
//OK sonar initiation

 
void setup() {
  Serial.begin(115200); //Baud rate ONLY for the ultrasonic sensors
  pinMode(inputPin, INPUT);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < sonars; i++)
    pingTimer[i] = pingTimer[i - 1] + pingInterval;
  LED.set_output(4); // Digital Pin 4
}
//OK setup


 
void loop() {
  for (uint8_t i = 0; i < sonars; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += pingInterval * sonars;
      if (i == 0 && currentSensor == sonars - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
      accelerometer();
      pirSensor();
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
      
    }
  
  
  delay(100);
  }
  
//OK loop

  // The rest of your code would go here.

}
//OK END OF LOOP THAT RUNS (main)
 
void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
//OK echoCheck function
 
void oneSensorCycle() { // Do something with the results.
 
    Serial.println("sonar;frm;" + String(cm[0]));
    Serial.println("sonar;ned;" + String(cm[1]));

  Serial.println();
}
//OK oneSensorCycle

void accelerometer() { //Reads the analogue values from the accelerometer and stores them in variables
  xAxis = (analogRead(xpin)-cal);
  yAxis = (analogRead(ypin)-cal);
  zAxis = (analogRead(zpin)-cal);
  Serial.print("acceleroMeter;xAxis;" + String(xAxis)+"\n");
  Serial.print("acceleroMeter;yAxis;" + String(yAxis)+"\n");
  Serial.print("acceleroMeter;zAxis;" + String(zAxis)+"\n");
  
  //Serial.print("x-axis: ");Serial.println(xAxis);
  //Serial.print("y-axis: ");Serial.println(yAxis);
  //Serial.print("z-axis: ");Serial.println(zAxis);
  delay(200);

  }

void pirSensor() {
  val = digitalRead(inputPin);
  
  if (val == HIGH)
  {            
    //DO: Turn on robot
    //Or for example turn a LED ON
  
    if (pirState == LOW) 
  {
      Serial.println("pirSensor;Motion;true");
      pirState = HIGH;
    }
  } 
  else 
  {
    if (pirState == HIGH)
  {
      Serial.println("pirSensor;Motion;false");
      pirState = LOW;
    }
  }

  }

void ledStrip(int R, int G, int B) {
    LED.set_rgbw(0, {G, R, B, G});
    LED.set_rgbw(1, {R, B, G, R});
    LED.set_rgbw(2, {B, G, R, B});
    LED.set_rgbw(3, {G, R, B, G});
    LED.set_rgbw(4, {R, B, G, R});
    LED.set_rgbw(5, {B, G, R, B});
/*
  if(mode == 2){
    LED.set_rgbw(0, {0, 255, 0, 0}); // Set first LED to color1
    LED.set_rgbw(1, {255, 0, 0, 255}); // Set first LED to color1
    LED.set_rgbw(2, {0, 0, 255, 0}); // Set first LED to color1
    LED.set_rgbw(3, {0, 255, 0, 0}); // Set first LED to color1
    LED.set_rgbw(4, {255, 0, 0, 255}); // Set first LED to color1
    LED.set_rgbw(5, {0, 0, 255, 0}); // Set first LED to color1
  }else if(mode == 1){ 
    LED.set_rgbw(0, {0, 255, 129, 0}); // Set first LED to color1
    LED.set_rgbw(1, {255, 129, 0, 255}); // Set first LED to color1
    LED.set_rgbw(2, {129, 0, 255, 129}); // Set first LED to color1
    LED.set_rgbw(3, {0, 255, 129, 0}); // Set first LED to color1
    LED.set_rgbw(4, {255, 129, 0, 255}); // Set first LED to color1
    LED.set_rgbw(5, {129, 0, 255, 129}); // Set first LED to color1
  }else if(mode == 0){
    LED.set_rgbw(0, {0, 0, 0, 0}); // Set first LED to color1
    LED.set_rgbw(1, {0, 0, 0, 0}); // Set first LED to color1
    LED.set_rgbw(2, {0, 0, 0, 0}); // Set first LED to color1
    LED.set_rgbw(3, {0, 0, 0, 0}); // Set first LED to color1
    LED.set_rgbw(4, {0, 0, 0, 0}); // Set first LED to color1
    LED.set_rgbw(5, {0, 0, 0, 0}); // Set first LED to color1
  }
*/
  
  LED.sync();

}

int handle_command() {
  if(n_tokens > 0) {
    
    if(token_buffer[0].equals("setLed")){
      if(n_tokens == 4) {
        int R = token_buffer[1].toInt();
        int G = token_buffer[2].toInt();
        int B = token_buffer[3].toInt();
        ledStrip(R,G,B);
        }
      } 
    } 
  }
