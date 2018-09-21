int photoresPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  getBrightness();
}

void photoresSetup(void) {
  Serial.begin(9600);
}

int getBrightness(void) {
  return analogRead(photoresPin);
}

void printBrightness(void) {
  Serial.println(analogRead(photoresPin));
  delay(100);
}
