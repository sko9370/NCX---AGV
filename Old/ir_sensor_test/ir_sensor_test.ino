    /* Raw IR decoder sketch!
     
     This sketch/program uses the Arduno and a PNA4602 to 
     decode IR received. This can be used to make a IR receiver
     (by looking for a particular code)
     or transmitter (by pulsing an IR LED at ~38KHz for the
     durations detected 
     
     Code is public domain, check out www.ladyada.net and adafruit.com
     for more tutorials! 
     */




    // white is detected
    // black is not detected
    // good distance is 5-6 inches
    // make sure IR LED isn't directly facing
    // may need to readjust positioning or recalibrating sensitivity





    
    // We need to use the 'raw' pin reading methods
    // because timing is very important here and the digitalRead()
    // procedure is slower!
    //uint8_t IRpin = 2;
    // Digital pin #2 is the same as Pin D2 see
    // http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
    #define IRpin_PIN      PIND
    
    #define IRled          9
    #define IRpinR         10
    #define IRpinL         11
     
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
      Serial.println("Ready to decode IR!");
      tone(IRled, 3000, 1000);                       // Play tone for 1 second
      delay(1000);  
      
    }
     
    void loop(void) {
      uint16_t highpulse, lowpulse;  // temporary storage timing
      highpulse = lowpulse = 0; // start out with no pulse length
      
      /*
    //  while (digitalRead(IRpin)) { // this is too slow!
        while (IRpin_PIN & (1 << IRpin)) {
         // pin is still HIGH
     
         // count off another few microseconds
         highpulse++;
         delayMicroseconds(RESOLUTION);
     
         // If the pulse is too long, we 'timed out' - either nothing
         // was received or the code is finished, so print what
         // we've grabbed so far, and then reset
         if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
           printpulses();
           currentpulse=0;
           return;
         }
      }
      // we didn't time out so lets stash the reading
      pulses[currentpulse][0] = highpulse;
      
      // same as above
      while (! (IRpin_PIN & _BV(IRpin))) {
         // pin is still LOW
         lowpulse++;
         delayMicroseconds(RESOLUTION);
         if ((lowpulse >= MAXPULSE)  && (currentpulse != 0)) {
           printpulses();
           currentpulse=0;
           return;
         }
      }
      pulses[currentpulse][1] = lowpulse;
     
      // we read one high-low pulse successfully, continue!
      currentpulse++;
      */

      int irL = irDetect(IRled, IRpinL, 38000);       // Check for object on left
      int irR = irDetect(IRled, IRpinR, 38000);
      if(irL == 0)                       // If only left side detects
      {
        Serial.print(" left detected\n");               // Right for 20 ms
      }
      else                                       // Otherwise, no IR detects
      {
        Serial.print(" left not detected\n");               // Forward 20 ms
      }
      if(irR == 0)                       // If only left side detects
      {
        Serial.print("right detected\n");               // Right for 20 ms
      }
      else                                       // Otherwise, no IR detects
      {
        Serial.print("right not detected\n");               // Forward 20 ms
      }
    }
     
    void printpulses(void) {
      Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
      for (uint8_t i = 0; i < currentpulse; i++) {
        Serial.print(pulses[i][0] * RESOLUTION, DEC);
        Serial.print(" usec, ");
        Serial.print(pulses[i][1] * RESOLUTION, DEC);
        Serial.println(" usec");
      }
      
      // print it in a 'array' format
      Serial.println("int IRsignal[] = {");
      Serial.println("// ON, OFF ");
      for (uint8_t i = 0; i < currentpulse-1; i++) {
        //Serial.print("\t"); // tab
        Serial.print("pulseIR(");
        Serial.print(pulses[i][1] * RESOLUTION , DEC);
        Serial.print(");");
        Serial.println("");
        //Serial.print("\t");
        Serial.print("delayMicroseconds(");
        Serial.print(pulses[i+1][0] * RESOLUTION , DEC);
        Serial.println(");");
     
      }
      //Serial.print("\t"); // tab
      Serial.print("pulseIR(");
      Serial.print(pulses[currentpulse-1][1] * RESOLUTION, DEC);
      Serial.print(");");
    }

    int irDetect(int irLedPin, int irReceiverPin, long frequency)
    {
      tone(irLedPin, frequency, 50);              // IRLED 38 kHz for at least 1 ms
      delay(1);                                  // Wait 1 ms
      int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
      delay(1);                                  // Down time before recheck
      return ir;                                 // Return 1 no detect, 0 detect
    }
