//Slave communication
#include <esp_now.h>
#include <WiFi.h> 
#include <Brain.h>

const int ForwardPin = 13;       // H-bridge forward control pin
const int BackwardPin = 12;      // H-bridge backward control pin
const int pwmFreq = 5000;        // Frequency for PWM (5kHz)
const int pwmResolution = 8;    // Resolution for PWM (0-255)


typedef struct struct_message //recive data should be same as sender
{
  byte Command;
}struct_message;

struct_message ReciveData;
bool newDataReceived = false; 

//Function called when recive data
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  //copy info incomingData to Recivedata
  memcpy(&ReciveData, incomingData, sizeof(ReciveData));
  newDataReceived = true; // Flag to indicate new data has been received
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //set as wifi station

  //Intiliaze ESP-NOW:
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initliazing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  ledcAttach(ForwardPin, pwmFreq, pwmResolution);
  ledcAttach(BackwardPin, pwmFreq, pwmResolution);

}

void loop() {
   if (newDataReceived) {
    newDataReceived = false; // Reset flag
    if(ReciveData.Command > 64) //nothing dtected
    {
      ForwardDirection();
      Serial.println("Going Foward");
    } 
    else if(ReciveData.Command < 64)
    {
      StopMotor();// something deteced
      Serial.println("Stopping");
    }
   }
  delay(2000);
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

