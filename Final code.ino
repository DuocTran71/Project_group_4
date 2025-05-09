#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //I2C của LCD là 0x27, LCD 16x02

int Relay = 6;

DS3231 rtc(SDA, SCL);
Time t;

 int giomo = 13;
 int phutmo = 00;
 int giaymo[] = {00, 10, 20, 30, 40, 50};
 
 int giotat = 13;
 int phuttat = 10;
 int giaytat[] = {05, 15, 25, 35, 45, 55};


void setup() {
  Serial.begin(115200);
  Wire.begin();//Khởi tạo I2C
  
  lcd.backlight();  //Mở đèn LCD
  lcd.init();  //Khởi động LCD
  lcd.setCursor(0,0);
  lcd.print("Time:");
  lcd.setCursor(0,1);
  lcd.print("Light Mode: ");
  lcd.setCursor(12,1);
  lcd.print("OFF");
  
  

  rtc.begin();
  rtc.setDOW(TUESDAY);     // Cài đặt thứ trong tuần
  rtc.setTime(12, 59, 55);     // Cài đặt giờ, phút, giây (24)
  rtc.setDate(6, 5, 2025);   // Ngày, tháng, năm

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
}

void loop() 
{
  t = rtc.getTime();
  // Serial.print(rtc.getDOWStr());
  // Serial.print(" ");
  
  // Serial.print(rtc.getDateStr());
  // Serial.print(" -- ");
  // lcd.setCursor(6,1);
  // lcd.print(rtc.getDateStr()); 

  // Serial.println(rtc.getTimeStr());
  
  lcd.setCursor(6,0);
  lcd.print(rtc.getTimeStr()); 

  delay (200);
  
  if(t.hour == giomo && t.min == phutmo)
    {

      bool found_giaymo = false;
      int arraySize_giaymo = sizeof(giaymo) / sizeof(giaymo[0]);
      for (int i = 0; i < arraySize_giaymo; i++) {
        if (t.sec == giaymo[i]) {
          found_giaymo = true;
          break;
        }
      }

      bool found_giaytat = false;
      int arraySize_giaytat = sizeof(giaytat) / sizeof(giaytat[0]);
      for (int i = 0; i < arraySize_giaymo; i++) {
        if (t.sec == giaytat[i]) {
          found_giaytat = true;
          break;
        }
      }


      if (found_giaymo) {
        digitalWrite(Relay,HIGH);
        lcd.setCursor(0,1);
        lcd.print("Light Mode: ");
        lcd.setCursor(12,1);
        lcd.print("ON");
        lcd.setCursor(14,1);
        lcd.print(" ");
      } else if (found_giaytat) {
        digitalWrite(Relay,LOW);
        lcd.setCursor(0,1);
        lcd.print("Light Mode: ");
        lcd.setCursor(12,1);
        lcd.print("OFF");
      }
    }
}


