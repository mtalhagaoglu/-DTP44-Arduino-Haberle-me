#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

 
const int in1 = 4;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
const int in2 = 5;
const int in3 =  6;
const int in4 =  7;
const int buzzer = A0;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "10110";

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(1);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(buzzer,OUTPUT);
  printf_begin();
  radio.printDetails();
}
int command = 0;
int command_received = 0;

int line = 1; // İkinci şerit ise 1 yap

void loop()
{



  if (radio.available()) { // NRF ile gelen komut var mı onu kontrol ediyoruz.
    radio.read(&command_received, sizeof(command_received));
    if (command_received > 0 + (line * 50) && command_received <= 50 + (line * 50)) { // İlk 50 Sağ şeritte giden araba için
      command = (command_received % 50) / 7;
    } else {
      command = 0;
    }+
    Serial.println(command_received);
  } else {
    command = 0;
  }

  if (Serial.available()) {// Arabadan bilgisayara direkt olarak saniye bilgisi vermek için.
    command = Serial.readString().toInt();
  }
  Serial.println(command);
  Serial.println(radio.available());
  Serial.println("----");
  if (command) {
    digitalWrite(buzzer,HIGH);
    digitalWrite(in1, LOW); // İleri
    digitalWrite(in2,  HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH);
    delay(command * 1000);
    digitalWrite(in1, LOW); // Dur
    digitalWrite(in2,  LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4,  LOW);
    delay(2000); // Kazaya müdehale için 2 Saniye Bekleme Gerek yok ise üstteki delay()'e kadar kaldır.
    digitalWrite(in1, HIGH); // Geri
    digitalWrite(in2,  LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4,  LOW);
    delay(command * 1000);
    digitalWrite(in1, LOW); // Dur
    digitalWrite(in2,  LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4,  LOW);
    delay(command * 1000);
    digitalWrite(buzzer,LOW);
  } else { //Komut 0 ise arabaya durmalı
    digitalWrite(in1, LOW);
    digitalWrite(in2,  LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4,  LOW);
  }
  delay(200);
}
