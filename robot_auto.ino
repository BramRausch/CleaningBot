#include <Wire.h>
#include <ArduinoWiFi.h>

unsigned long previousMillis = 0;
const int pingDelay = 100;

const int trigPin1 = 2;
const int echoPin1 = 3; 

const int trigPin2 = 4;
const int echoPin2 = 5; 

const int trigPin3 = 6;
const int echoPin3 = 7; 

void setup() {
  pinMode(8, OUTPUT);  //  -|
  pinMode(9, OUTPUT);  //   |
  pinMode(10, OUTPUT); //   |-- Motor control pins
  pinMode(11, OUTPUT); //  -|
  
  pinMode(12, INPUT_PULLUP); // Bumper input
  
  Wifi.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Distance sensor
  if (currentMillis - previousMillis >= pingDelay) {  // Non-blocking delay
    previousMillis = currentMillis;
    
    // Initialize the distance sensor variables
    long duration1, cm1, duration2, cm2, duration3, cm3;
  
    // Ping distance sensor #1
    pinMode(trigPin1, OUTPUT);
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
  
    pinMode(echoPin1, INPUT);
    duration1 = pulseIn(echoPin1, HIGH);
  
    // Ping distance sensor #2
    pinMode(trigPin2, OUTPUT);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
  
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);
    
    // Ping distance sensor #3
    pinMode(trigPin3, OUTPUT);
    digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
  
    pinMode(echoPin3, INPUT);
    duration3 = pulseIn(echoPin3, HIGH);
  
    // converts the time into a distance from all sensors
    cm1 = microsecondsToCentimeters(duration1);
    cm2 = microsecondsToCentimeters(duration2);
    cm3 = microsecondsToCentimeters(duration3);
    
    Wifi.print("d");  // Debug output to wifi console
    Wifi.print(cm1); 
    Wifi.print("/");
    Wifi.print(cm2);
    Wifi.print("/");
    Wifi.println(cm3);
    
    if(cm3 > cm1 && cm1 < 20){ 
      digitalWrite(8, LOW);    //  -|
      digitalWrite(9, HIGH);   //   |
      digitalWrite(10, LOW);   //   |-- Go backwards
      digitalWrite(11, HIGH);  //  -|
      delay(1000);
      digitalWrite(8, LOW);    //  -|
      digitalWrite(9, HIGH);   //   |
      digitalWrite(10, HIGH);  //   |-- Turn right
      digitalWrite(11, LOW);   //  -|
      delay(700);
    } else if(cm1 > cm3 && cm3 < 20 || cm1 == cm2 && cm2 == cm3 && cm1 < 20 || cm2 < 20 || digitalRead(12) == 0){
      digitalWrite(8, LOW);    //  -|
      digitalWrite(9, HIGH);   //   |
      digitalWrite(10, LOW);   //   |-- Go backwards
      digitalWrite(11, HIGH);  //  -|
      delay(1000);
      digitalWrite(8, HIGH);   //  -|
      digitalWrite(9, LOW);    //   |
      digitalWrite(10, LOW);   //   |-- Turn right
      digitalWrite(11, HIGH);  //  -|
      delay(700);
    }else{
      digitalWrite(8, HIGH);   //  -|
      digitalWrite(9, LOW);    //   |
      digitalWrite(10, HIGH);  //   |-- Go forward
      digitalWrite(11, LOW);   //  -|
    }
  }
}

long microsecondsToCentimeters(long microseconds) { //Function to calculate the distance
  // Sound travels at a speed of 340 m/s that's 29 microseconds per cm.
  // To calculate the distance we divide the microseconds it took the sound to come back by the microseconds per cm
  // but because sound the sound wave traveled back it took twice as long so we take half of this. 
  return microseconds / 29 / 2;
}
