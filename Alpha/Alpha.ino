///////////////////////////////////////////////Servo
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
///////////////////////////////////////////////Ping
const int pingPinL = 7;
const int pingPinR = 4;

long durationL, durationR;
int cmL = 500;
int cmR = 500;

void setup() {
  Serial.begin(9600);
  servoSetup();

  fastForward(1);
}

void loop() {

}

//////////////////////////////////////////////Servo
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
    servoR.writeMicroseconds(F_HALF);
    servoL.writeMicroseconds(F_HALF);
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
    servoR.writeMicroseconds(R_HALF-25);
    servoL.writeMicroseconds(F_HALF+25);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
void turnLeft(int deg) {
  int duration = deg*(10/9);
  for (i = 0; i < duration; i++) {
    servoR.writeMicroseconds(F_HALF+25);
    servoL.writeMicroseconds(R_HALF-25);
    delay(15);
  }
  servoR.writeMicroseconds(STOP);
  servoL.writeMicroseconds(STOP);
  delay(15);
}
//////////////////////////////////////////////Ping

int pingDuration(int pingPin) {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  return pulseIn(pingPin, HIGH);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void printDistances(int cmL, int cmR) {
  Serial.print(cmL);
  Serial.print(" cmL");
  Serial.println();

  Serial.print(cmR);
  Serial.print(" cmR");
  Serial.println();
  Serial.println();
}
/////////////////////////////////////////////////
