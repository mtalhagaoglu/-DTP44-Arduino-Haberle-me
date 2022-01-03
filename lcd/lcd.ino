#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "10110";

LiquidCrystal lcd_left_1(7, 6, A2, A3, A4, A5);
LiquidCrystal lcd_right_1(7, 5, A2, A3, A4, A5);
LiquidCrystal lcd_left_2(7, 4, A2, A3, A4, A5);
LiquidCrystal lcd_right_2(7, 3, A2, A3, A4, A5);

char status_normal[] = "Iyi Yolculuklar";
char status_crash[] = "Dikkat Ileride Kaza Var";

int alarm_section = 0;

void set_lcd(LiquidCrystal lcd) {
  lcd.clear();
  lcd.leftToRight();
  lcd.setCursor(16, 1);
  lcd.autoscroll();
  delay(50);
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver

  // list the lcd dimension you are using

  lcd_left_1.begin(8, 2); //16 colums and 2 rows
  lcd_left_1.cursor();
  lcd_right_1.begin(8, 2); //16 colums and 2 rows
  lcd_right_1.cursor();
  lcd_left_2.begin(8, 2); //16 colums and 2 rows
  lcd_left_2.cursor();
  lcd_right_2.begin(8, 2); //16 colums and 2 rows
  lcd_right_2.cursor();


}

int command_received = 0;

void loop() {
  while (!radio.available());
  if (radio.available()) {
    radio.read(&command_received, sizeof(command_received));
    if(command_received > 999 && command_received < 2000){
      alarm_section = command_received - 1000;  
    }
  }
  Serial.println(radio.available());
  Serial.println(alarm_section);
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
      if (alarm_section <= 3) { // emergency in right lane
        if (i < strlen(status_normal)) {
          lcd_left_1.print(status_normal[i]);
          lcd_left_2.print(status_normal[i]);
        }

        lcd_right_1.print(status_crash[i]);
        lcd_right_2.print(status_crash[i]);
      } else { // emergency in left lane
        lcd_left_1.print(status_crash[i]);
        lcd_left_2.print(status_crash[i]);
        if (i < strlen(status_normal)) {
          lcd_right_1.print(status_normal[i]);
          lcd_right_2.print(status_normal[i]);
        }
      }
    }
    delay(100);
  };
}
