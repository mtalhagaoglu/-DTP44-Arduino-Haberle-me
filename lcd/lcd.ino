#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "10110";

LiquidCrystal lcd_left_1(7, 6, A2, A3, A4, A5);
LiquidCrystal lcd_right_1(7, 5, A2, A3, A4, A5);
LiquidCrystal lcd_left_2(7, 4, A2, A3, A4, A5);
LiquidCrystal lcd_right_2(7, 3, A2, A3, A4, A5);

char status_normal[] = "Iyi Yolculuklar";
char status_crash[] = "Ileride Kaza Var"; // Kazaya Uzak Ekran
char status_crash2[] = "Dikkatli Geciniz"; // Kazaya Yakın Ekran

int command_received = 0; // Bilgisayardan gelen komut

int alarm_section = 0; // Bilgisayardan gelen komut eğer doğru formatta ise buraya atanacak. Onaylanmış ve doğru komut.

void set_lcd(LiquidCrystal lcd) {
  lcd.clear();
  lcd.leftToRight();
  lcd.setCursor(16, 1);
  lcd.autoscroll();
  delay(50);
}

void setup() {
  //Bilgisayar ile iletişime geçmek için gereken ayarlar
  Serial.begin(9600);
  Serial.setTimeout(1);

  //NRF Ayarları
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
  printf_begin();
  radio.printDetails();

  //Ekran Ayarları
  lcd_left_1.begin(116, 2); //16 colums and 2 rows
  lcd_left_1.cursor();
  lcd_right_1.begin(16, 2); //16 colums and 2 rows
  lcd_right_1.cursor();
  lcd_left_2.begin(16, 2); //16 colums and 2 rows
  lcd_left_2.cursor();
  lcd_right_2.begin(16, 2); //16 colums and 2 rows
  lcd_right_2.cursor();


}


// Alarm kodları için https://github.com/mtalhagaoglu/-DTP44-Arduino-Haberle-me


void loop() {

  if (Serial.available()) {
    command_received = Serial.readString().toInt();
    if (command_received < 100) {
      alarm_section = command_received;
      Serial.println("Komut: " + command_received);
      bool is_received = radio.write(&command_received, sizeof(command_received));
      if (is_received) {
        Serial.println("Komut Gönderildi");
      } else {
        Serial.println("Komut Gönderilemedi");
      }
    }
  }
  Serial.println("-----");

  set_lcd(lcd_left_1);
  set_lcd(lcd_right_1);
  set_lcd(lcd_left_2);
  set_lcd(lcd_right_2);
  for (int i = 0; i < strlen(status_crash); i++) {
    if (alarm_section == 0) {
      if (i < strlen(status_normal)) {
        lcd_left_1.print(status_normal[i]);
        lcd_left_2.print(status_normal[i]);
        lcd_right_1.print(status_normal[i]);
        lcd_right_2.print(status_normal[i]);
      }
    } else {
      if (alarm_section <= 50) { // emergency in right lane
        if (i < strlen(status_normal)) {
          lcd_left_1.print(status_normal[i]);
          lcd_left_2.print(status_normal[i]);
          if (alarm_section < (50 / 3)) {
            lcd_right_2.print(status_crash2[i]);
          }
        }

        if (alarm_section < (50 / 3)) { //İlk Kısım
          lcd_right_1.print(status_crash2[i]);

        } else if (alarm_section < 2 * (50 / 3)) { //Orta Kısım
          lcd_right_1.print(status_crash[i]);
          lcd_right_2.print(status_crash2[i]);
        } else { // Son Kısım
          lcd_right_1.print(status_crash[i]);
          lcd_right_2.print(status_crash[i]);
        }

      } else { // emergency in left lane
        if (i < strlen(status_normal)) {
          lcd_right_1.print(status_normal[i]);
          lcd_right_2.print(status_normal[i]);
          if (alarm_section < (100 / 3)) {
            lcd_left_2.print(status_crash2[i]);
          }
        }
        if (alarm_section < (100 / 3)) { //İlk Kısım
          lcd_left_1.print(status_crash2[i]);

        } else if (alarm_section < 2 * (100 / 3)) { //Orta Kısım
          lcd_left_1.print(status_crash[i]);
          lcd_left_2.print(status_crash2[i]);
        } else { //Son Kısım
          lcd_left_1.print(status_crash[i]);
          lcd_left_2.print(status_crash[i]);
        }
      }
    }
    delay(200);
  };
}
