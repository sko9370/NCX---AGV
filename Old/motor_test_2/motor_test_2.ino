/*
     Code to operate the MMP-5 with a Sabertooth Motor Controller set to R/C mode
     The Sabertooth expects to receive a "center" or "stop" position first (as if the R/C
     joystick was in the neutral position.
     Then it expect to receive the end limits.
     If this code is not executed when the controller is powered up, the MMP-5 may move
     eratically or not at all
     COL Lisa A. Shay
*/

#include <Servo.h>

Servo right;  // create servo object to control a servo
Servo left;   // twelve servo objects can be created on most boards

const int RIGHT = 11;
const int LEFT = 12;

int STOP = 1250;
int FORE_HALF = 1050;
int FORE_FULL = 1000;
int BACK_HALF = 1700;
int BACK_FULL = 2000;

int i = 0;      // loop counter
const int dur = 2;  // counter duration 2 is the minimun setting to
// produce reliable results.  Increase to 25 if
// the motor controller behaves eratically.

void setup()
{
  right.attach(11);   // attaches the servo on pin 10 to the servo object
  //This is one of the servo ports on the Parallax shield. Others are 11, 12, and 13
  left.attach(12);
/*
  for (i = 0; i < dur; i++ )
  {
    right.writeMicroseconds(STOP);    // motor stop
    left.writeMicroseconds(STOP);
    delay(15);
  }

  for (i = 0; i < dur; i++)
  {
    right.writeMicroseconds(FORE_FULL);     // full speed in one direction
    left.writeMicroseconds(FORE_FULL);
    delay(15);
  }
  for (i = 0; i < dur; i++)
  {
    right.writeMicroseconds(BACK_FULL);   // full speed in the other direction
    left.writeMicroseconds(BACK_FULL);
    delay(15);
  }

  for (i = 0; i < dur; i++ )
  {
    right.writeMicroseconds(STOP);    // motor stop
    left.writeMicroseconds(STOP);
    delay(15);
  }
  // end setup code
*/
/*
  for (i = 0; i < 100; i++)
  {
    right.writeMicroseconds(FORE_FULL);     // full speed in one direction
    left.writeMicroseconds(FORE_FULL);
    delay(15);
  }
  right.writeMicroseconds(STOP);
  left.writeMicroseconds(STOP);
  for (i = 0; i < 100; i++)
  {
    right.writeMicroseconds(BACK_FULL);     // full speed in one direction
    left.writeMicroseconds(BACK_FULL);
    delay(15);
  }
  right.writeMicroseconds(STOP);
  left.writeMicroseconds(STOP);
  for (i = 0; i < 100; i++)
  {
    right.writeMicroseconds(FORE_HALF);     // full speed in one direction
    left.writeMicroseconds(FORE_HALF);
    delay(15);
  }
  right.writeMicroseconds(STOP);
  left.writeMicroseconds(STOP);
  for (i = 0; i < 100; i++)
  {
    right.writeMicroseconds(BACK_HALF);     // full speed in one direction
    left.writeMicroseconds(BACK_HALF);
    delay(15);
  }
  right.writeMicroseconds(STOP+250);
  left.writeMicroseconds(STOP+50);
*/
  
}

void driveFeet(int numFeet)
{
  int delayTime = numFeet*12;
  for (i = 0; i < 100; i++)
  {
    right.writeMicroseconds(BACK_FULL);
    left.writeMicroseconds(BACK_FULL);
    delay(delayTime);
  }
  right.writeMicroseconds(STOP+250);
  left.writeMicroseconds(STOP+50);
  delay(1000);
}

void loop()
{

}
