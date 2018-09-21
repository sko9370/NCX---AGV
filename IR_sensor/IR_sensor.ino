    // white is detected
    // black is not detected
    // good distance is 5-6 inches
    // make sure IR LED isn't directly facing
    // may need to readjust positioning or recalibrating sensitivity

    #define IRled       9
    #define IRpinR      10
    #define IRpinL      11
    #define MAXPULSE    65000
    #define RESOLUTION  20

    void setup(void) {
      IRsetup();
    }

    void IRsetup(void) {
      Serial.begin(9600);
      Serial.println("Ready to decode IR!");
      // tone(irLedPin, frequency (Hz), duration (ms))
      tone(IRled, 3000, 1000);
      delay(1000);
    }

    void loop(void) {
      int irL = irDetect(IRled, IRpinL);
      int irR = irDetect(IRled, IRpinR);
      printpulses(irL, irR)
    }

    void printpulses(int irL, int irR) {
      if(irL == 0) {
        Serial.print(" left detected\n");
      } else {
        Serial.print(" left not detected\n");
      }
      if(irR == 0) {
        Serial.print("right detected\n");
      } else {
        Serial.print("right not detected\n");
      }
    }

    int irDetect(int irLedPin, int irReceiverPin) {
      tone(irLedPin, 38000, 50);
      delay(1);
      int ir = digitalRead(irReceiverPin);
      delay(1);
      return ir;
    }
