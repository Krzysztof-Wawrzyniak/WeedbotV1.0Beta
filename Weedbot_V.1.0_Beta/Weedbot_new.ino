#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

LiquidCrystal_I2C  lcd(0x27, 16, 2);
//Zmienne dotyczace czasu
int rok; int miesiac; int dzien;
int godzina; int minuta; int sekunda;
const char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); lcd.backlight(); lcd.setBacklight(HIGH);
  //ustawZegar();
}
void loop() {
  Zegar();
  CzujnikWilgotnosciGleby();
  CzujnikDHT11();
  Swiatlo();
  MieszaniePowietrza();
}

