#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "10110";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 2;
int received_data = 0;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

int command = 0;

void loop()
{
   if (Serial.available()) {
    received_data = Serial.readString().toInt();
    Serial.println(received_data);
    if(received_data != command && received_data != 0){
      command = received_data;
    }
    delay(100);
    bool is_received = radio.write(&command, sizeof(command));
    while(not is_received){
      is_received = radio.write(&command, sizeof(command));      
      }
    Serial.println("4444");
    
    delay(100);
  }
}
