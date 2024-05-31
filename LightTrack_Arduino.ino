#include "SevSeg.h"
SevSeg sevseg;

// Counter
int rotationCount = 0;
bool turn = false;
// In feet
double radius = 6.28 / 30.48; 
double pi = 3.1415926535897932384626433832795;
double circumference = pi * radius * 2;
bool reset = false;
int resetVal = 50;

// Display
int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;



void setup() {
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  // put your setup code here, to run once:
  // Display
  pinMode(pinA, OUTPUT);  
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  // Counter
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  //Display 
  //uncomment to display number
  // Serial.println(distance);
  //sevseg.setNumber(123, 0); 
  //sevseg.refreshDisplay(); // Must run repeatedly

  // Counter
  int analogValue = analogRead(A0);
  int button = analogRead(A1);
  Serial.println(button);
  if (resetVal == 0) {
    rotationCount = 0;
    resetVal = 50;
  }
  while (resetVal != 0) {
    if (button >= 0 && button < 3) {
      resetVal -= 1;
    } else {
      resetVal = 50;
    }
    break;
  }


  //Serial.println(analogValue);
  if (analogValue <= 3){
    turn = true;
  } 

  // do same thing as button where many 0s must be detected before considering it as a turn
  if (turn && analogValue >= 7){
    rotationCount += 1;
    turn = false;
  }
  double distance = circumference * rotationCount;

  sevseg.setNumber((int)distance, 0); 
  sevseg.refreshDisplay(); // Must run repeatedly
}
