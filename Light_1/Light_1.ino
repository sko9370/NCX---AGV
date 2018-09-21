#include <Servo.h>
#define servoRpin 11
#define servoLpin 12
const int F_FULL = 1000;
const int F_HALF = 1250;
const int STOP = 1500;
const int R_HALF = 1750;
const int R_FULL = 2000;
const int dur = 2;
int i = 0;
Servo servoR, servoL;
int photoresPin = A1;


void setup() {
  servoSetup();
}

void loop() {
  
  turnLeft(45);
  int brightnessL = getBrightness();
  turnRight(45);
  int brightnessR = getBrightness();

  if (brightnessL > brightnessR) {
    turnLeft(45);
    halfForward(1);
  }
  else {
    halfForward(1);
  }
  
}

void servoSetup(void) {
  servoR.attach(servoRpin);
  servoL.attach(servoLpin);

  for (i = 0; i < dur; i++) {
    servoR.writeMicroseconds(STOP);    // motor stop
    servoL.writeMicroseconds(STOP);
    delay(15);
  }
  for (i = 0; i < dur; i++) {
    servoR.writeMicroseconds(F_FULL);     // full speed in one direction
    servoL.writeMicroseconds(F_FULL);
    delay(15);
  }
  for (i = 0; i < dur; i++) {
    servoR.writeMicroseconds(R_FULL);   // full speed in the other direction
    servoL.writeMicroseconds(R_FULL);
    delay(15);
  }
  for (i = 0; i < dur; i++ ) {
    servoR.writeMicroseconds(STOP);    // motor stop
    servoL.writeMicroseconds(STOP);
    delay(15);
  }
}

// must use values 1 or greater as input
void fastForward(int numFeet) {
  int duration = numFeet*100;
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(F_FULL);
    servoL.writeMicroseconds(F_FULL);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void fastReverse(int numFeet) {
  int duration = numFeet*100;
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(R_FULL);
    servoL.writeMicroseconds(R_FULL);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void halfForward(int numFeet) {
  int duration = numFeet*100;
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(F_HALF+100);
    servoL.writeMicroseconds(F_HALF+100);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void halfReverse(int numFeet) {
  int duration = numFeet*100;
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(R_HALF);
    servoL.writeMicroseconds(R_HALF);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void turnRight(int deg) {
  int duration = deg*(10/9);
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(R_HALF-50);
    servoL.writeMicroseconds(F_HALF+50);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void turnLeft(int deg) {
  int duration = deg*(10/9);
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(F_HALF+50);
    servoL.writeMicroseconds(R_HALF-50);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
///////////////////////////////////////////////////
int getBrightness(void) {
  return analogRead(photoresPin);
}

void printBrightness(void) {
  Serial.println(analogRead(photoresPin));
  delay(100);
}
