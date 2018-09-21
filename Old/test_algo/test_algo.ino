#define IRpin_PIN      PIND
#define IRled          9
#define IRpinR         10
#define IRpinL         11

#include <Servo.h>

const int pingPinL = 7;
const int pingPinR = 4;

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

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000
 
// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing
 
void setup(void) {
  Serial.begin(9600);
  //Serial.println("Ready to decode IR!");
  tone(IRled, 3000, 1000);                       // Play tone for 1 second
  
  right.attach(11);   // attaches the servo on pin 10 to the servo object
  //This is one of the servo ports on the Parallax shield. Others are 11, 12, and 13
  left.attach(12);
  
  //delay(1000);

  int cmL=100, cmR=100, durationL, durationR;

  while (cmL > 15 && cmR > 15) {
    pinMode(pingPinL, OUTPUT);
    digitalWrite(pingPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPinL, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPinL, LOW);
  
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(pingPinL, INPUT);
    durationL = pulseIn(pingPinL, HIGH);
  
    pinMode(pingPinR, OUTPUT);
    digitalWrite(pingPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPinR, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPinR, LOW);
  
    pinMode(pingPinR, INPUT);
    durationR = pulseIn(pingPinR, HIGH);

    cmL = microsecondsToCentimeters(durationL);
    cmR = microsecondsToCentimeters(durationR);
    
    for (i = 0; i < 100; i++)
      {
        right.writeMicroseconds(FORE_FULL);     // full speed in one direction
        left.writeMicroseconds(FORE_FULL);
        //delay(15);
      }
  }

  right.writeMicroseconds(STOP+250);
  left.writeMicroseconds(STOP+50);
  delay(15);
}

void loop() {

  ////////////////////////////////////////////////////////////////////////////////////  
  
  uint16_t highpulse, lowpulse;  // temporary storage timing
  highpulse = lowpulse = 0; // start out with no pulse length

  int irL = irDetect(IRled, IRpinL, 38000);       // Check for object on left
  int irR = irDetect(IRled, IRpinR, 38000);
  /*
  if(irL == 0)                       // If only left side detects
  {
    Serial.print(" left detected\n");               // Right for 20 ms
  }
  else                                       // Otherwise, no IR detects
  {
    Serial.print(" left not detected\n");               // Forward 20 ms
  }
  
  if(irR == 0)                       // If only right side detects
  {
    Serial.print("right detected\n");               // Right for 20 ms
  }
  else                                       // Otherwise, no IR detects
  {
    Serial.print("right not detected\n");               // Forward 20 ms
  }
  */
  ////////////////////////////////////////////////////////////////////////////////////  
  long durationL, durationR, cmL, cmR;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPinL, OUTPUT);
  digitalWrite(pingPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinL, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPinL, INPUT);
  durationL = pulseIn(pingPinL, HIGH);

  pinMode(pingPinR, OUTPUT);
  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);

  pinMode(pingPinR, INPUT);
  durationR = pulseIn(pingPinR, HIGH);

  // convert the time into a distance
  cmL = microsecondsToCentimeters(durationL);
  cmR = microsecondsToCentimeters(durationR);

  Serial.print(cmL);
  Serial.print("cmL");
  Serial.println();

  Serial.print(cmR);
  Serial.print("cmR");
  Serial.println();

  //delay(100);

////////////////////////////////////////////////////////////////////////////////////
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

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
    {
      tone(irLedPin, frequency, 50);              // IRLED 38 kHz for at least 1 ms
      delay(1);                                  // Wait 1 ms
      int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
      delay(1);                                  // Down time before recheck
      return ir;                                 // Return 1 no detect, 0 detect
    }
