// Master EPS-32 send IR Sensor readings via (ESP-NOW)

#include <esp_now.h>
#include <WiFi.h> 

int IRpin = 13; //IR Sensor pin
//Slave or Reciver MAC address
uint8_t SlaveAddress[] = {0xCC, 0xDB, 0xA7, 0x98, 0x61, 0x28};

typedef struct struct_message
{
  int IROutput;
} struct_message;

//Store IR output
struct_message IRData;

//Store peer/slave info
esp_now_peer_info_t peerInfo;

//Verify if message is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status ==  ESP_NOW_SEND_SUCCESS ? "Delivery Sucess" : "Delivery Fail");
}

void setup() {
  //Serial monitor foe Debug
  Serial.begin(115200);

  pinMode(IRpin, INPUT); //INitliazen pin for sensor

  WiFi.mode(WIFI_STA); // Set as wifi station

  if (esp_now_init() != ESP_OK) // Initlize ESP_now
  {
    Serial.println("Error initlaizing ESP NOw");
    return;
  }

  esp_now_register_send_cb(OnDataSent); // registering callback function

  //Register slave esp-32
  memcpy(peerInfo.peer_addr, SlaveAddress,6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //Add peer
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

}

void loop() {
  //Set val to send
  IRData.IROutput = digitalRead(IRpin);
  Serial.println(IRData.IROutput);

  //Send message 
  esp_err_t result = esp_now_send(SlaveAddress, (uint8_t*) &IRData, sizeof(IRData));
  
  if(result == ESP_OK)
  {
    Serial.println("Data Sent succesfully");
  }
  else
  {
    Serial.println("Error sending data");
  }
  delay(2000);
}
