//BrainWave sensor purpose is to catch readLowBeta();
//Returns the Attention becasue most stable 
//Amplitude of focusing is what is needed

#include <Brain.h>

// Use Serial1 (UART1) instead of default Serial
HardwareSerial mySerial(1);
Brain brain(mySerial);

void setup() {
  Serial.begin(115200);  // For debugging
  mySerial.begin(9600, SERIAL_8N1, 17, 16); // TX=16, RX=17 (change as needed)
}

void loop() {
  if (brain.update()) {
    Serial.println(brain.readAttention()); // using this to gather data on when Im focusing. Values vary per person
    //Serial.println(brain.readCSV());
  }
}
