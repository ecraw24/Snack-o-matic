

/*
  Button Sweep

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 52.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  created 2021
  by Kirk & Emma
*/
// create servo object to control a servo

  #include <Servo.h>
  Servo myservo;  
  // twelve servo objects can be created on most boards

// create sevseg object for digit display
 
  #include "SevSeg.h"
  SevSeg sevseg; 

// Set the pin numbers, interval, and number of LEDs
    
    const int servoPin = 9;           // the number of the pushbutton pin
    const int ledPin0 =  13;          // the number of the LED pin
    int buttonPin[] = {2, 4, 3};      // {red, blue, yellow}
    int ledPin[] = {13, 11, 12};      // {red, blue, yellow}
    const long interval = 2000;       // interval at which to blink (milliseconds)
    const int LEDS = 3;               // number of leds
  
// variables will change (states, servo position, etc.)
    
    int buttonState[] = {LOW, LOW, LOW};         
    int ledState[] = {LOW, LOW, LOW};
    int pos = 0;                           
    int level = 1;
    int startCount = 0;  
    int correct = 0; 
    int i = 0;
    int marker = -1;  

  // will store last time LED was updated
    
    unsigned long previousMillis = 0;       

void setup() {
  
  pinMode(ledPin0, OUTPUT);       // initialize the LED pin as an output:
  pinMode(ledPin[0], OUTPUT);     // initialize the LED pin as an output:
  pinMode(ledPin[1], OUTPUT);     // initialize the LED pin as an output:
  pinMode(ledPin[2], OUTPUT);     // initialize the LED pin as an output:
  myservo.attach(servoPin);       // attaches the servo on servoPin to the servo object
  pinMode(buttonPin[0], INPUT);   // initialize the pushbutton pin as an input:
  pinMode(buttonPin[1], INPUT);   // initialize the pushbutton pin as an input:
  pinMode(buttonPin[2], INPUT);   // initialize the pushbutton pin as an input:

  // Set up digit display
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {7, 8, 10, 53, 52, 6, 5, 0};           // Set segment pins
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

}

void loop() {

    // Turn red light on for the first time at the first level
    //if (startCount < 1) { 
      digitalWrite(ledPin[1], HIGH);
      moveServoStart(); 
      displayDigit(level); 
      //startCount++;  
    //} 

    // Change LED if interval is complete
    ledChange(); 
     
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH. Check if number of correct is at level
    if (digitalRead(buttonPin[i]) == HIGH && digitalRead(ledPin[i]) == HIGH) {
        
        if (marker != i) {
          correct++; 
          marker = i; 
        }  
        
        if (correct == level) {
          moveServo();
          correct = 0; 
          startCount = 0; 
          
          if (level < 10) {
            level++;  
            
          } else {
            level = 1;  
          }
          
        }
      }   
    }

  void ledChange() {
    
    //if statement for making pin blink
    if ((millis() - previousMillis) >= interval) {
    
      // save the last time you blinked the LED
      previousMillis = millis(); 

      // Turn off previous light and turn on next light
      ledState[i] = LOW; 
      
      // set the current LED with the ledState of the variable:
      digitalWrite(ledPin[i], ledState[i]);

      // cycle through LEDs in order
      if (i < (LEDS - 1)) {
        ledState[++i] = HIGH;
      } else if (i == (LEDS - 1)){
        i = 0; 
        ledState[i] = HIGH; 
      } 
      
      // set the new LED with the ledState of the variable:
      digitalWrite(ledPin[i], ledState[i]); 
      
    } 
  }

  void moveServo() {

      // Open
      for (pos = 0; pos <= 90; pos += 1) {    // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        myservo.write(pos);                   // tell servo to go to position in variable 'pos'
        delay(5);                             // waits 15ms for the servo to reach the position
      }

      // Close
      for (pos = 90; pos >= 0; pos -= 1) {    // goes from 90 degrees to 0 degrees
        myservo.write(pos);                   // tell servo to go to position in variable 'pos'
        delay(5);                             // waits 15ms for the servo to reach the position
      }

      displayDigit(level); 
 
  }

  void moveServoStart() {

      // Open
      for (pos = 0; pos <= 5; pos += 1) {    // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        myservo.write(pos);                   // tell servo to go to position in variable 'pos'
        delay(5);                             // waits 15ms for the servo to reach the position
      }

      // Close
      for (pos = 5; pos >= 0; pos -= 1) {    // goes from 90 degrees to 0 degrees
        myservo.write(pos);                   // tell servo to go to position in variable 'pos'
        delay(5);                             // waits 15ms for the servo to reach the position
      }
  }

  void displayDigit(int num){
        sevseg.setNumber(num);
        sevseg.refreshDisplay();        
  }
