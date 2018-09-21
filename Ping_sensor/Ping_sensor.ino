const int pingPinL = 7;
const int pingPinR = 4;
long durationL, durationR;
int cmL, cmR;

void setup() {
  Serial.begin(9600);
}

void loop() {
  durationL = pingDuration(pingPinL);
  durationR = pingDuration(pingPinR);

  cmL = microsecondsToCentimeters(durationL);
  cmR = microsecondsToCentimeters(durationR);

  printDistances(cmL, cmR);
  delay(100);
}

void pingSetup(void) {
  
}

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
