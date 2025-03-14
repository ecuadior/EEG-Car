// This will be a test to see if when I'm focusing, it would cause the motor to spin
// Purpose use the attention value which represnt focus beacsue most stable
//This will be done with 1 micrcontroller and is a test case to see if its possible to do it with 2 micrcontroller

#include <Brain.h>
HardwareSerial mySerial(1);
Brain brain(mySerial);

//H-Bridge
const int ForwardPin = 13;       // H-bridge forward control pin
const int BackwardPin = 12;      // H-bridge backward control pin
const int pwmFreq = 5000;        // Frequency for PWM (5kHz)
const int pwmResolution = 8;    // Resolution for PWM (0-255)

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 17, 16); // TX=16, RX=17 (change as needed)
  

   // Set up PWM channels and attach them to pins
  ledcAttach(ForwardPin, pwmFreq, pwmResolution);
  ledcAttach(BackwardPin, pwmFreq, pwmResolution);
  

}

void loop() {
 if (brain.update()) {
    Serial.println(brain.readAttention());
    byte focus = brain.readAttention();
    if(focus>=60) // Means I'm fcousing on something. Dont know full range but knows its larger than 60 
    {
      ForwardDirection();
    }
    else
    {
      StopMotor();
    }
  }

}

void ForwardDirection() {
  ledcWrite(ForwardPin, 200); // Set forward pin PWM duty cycle
  ledcWrite(BackwardPin, 0);  // Ensure backward pin is off
  //Serial.println("Motor Moving Forward");
}
void BackwardDirection()
{
  ledcWrite(BackwardPin, 120); // set backward pwm duty cycle
  ledcWrite(ForwardPin, 0); // Ensure forward pin is off
}
void StopMotor() {
  ledcWrite(ForwardPin, 0);   // Stop forward pin
  ledcWrite(BackwardPin, 0);  // Stop backward pin
  //Serial.println("Motor Stopped");
}
