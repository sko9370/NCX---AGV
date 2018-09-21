int sensorPinR = A1;   // select the analog input pin for the photoresistor

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("right");
  Serial.println(analogRead(sensorPinR));
  delay(100);
}

//http://playground.arduino.cc/Learning/PhotoResistor
