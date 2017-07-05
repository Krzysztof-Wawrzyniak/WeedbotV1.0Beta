#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
LiquidCrystal_I2C  lcd(0x27, 16, 2);

//____________________WILGOTNOŚĆ GLEBY________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WilgotnoscGleby = 99;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CzujnikWilgotnosciGleby() {
  // Odczytaj wartosc z czujnika wilgotnosci gleby:
  int  wartosc_odczytu = analogRead(A0);

  WilgotnoscGleby = map(wartosc_odczytu, 1023, 0, 0, 100);
  Podlewanie();
}
//____________________WILGOTNOŚĆ GLEBY________________________________________________________________________________________________________

//CZUJNIK TEMPERATURY I WILGOTNOŚCI___________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN A2
#define DHTTYPE DHT11     // DHT 11 (AM2302)
DHT dht(DHTPIN, DHTTYPE);
int TemperaturaPowietrza = 99;
int WilgotnoscPowietrza = 99;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CzujnikDHT11() {
  //Odczyt temperatury i wilgotności z czujnika DHT11

  TemperaturaPowietrza = dht.readTemperature();
  WilgotnoscPowietrza = dht.readHumidity();
 //   Serial.print("Temp: "); Serial.println(TemperaturaPowietrza); Serial.print("Wilg:"); Serial.print(WilgotnoscPowietrza); //Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);

  Chlodzenie();
}
//CZUJNIK TEMPERATURY I WILGOTNOŚCI___________________________________________________________________________________________________________

//________________________________________________CHLODZENIE__________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINZielonaChlodzenie = 2;
int PINWiatrakaZewnetrznego = 3;
int PINCzerwonaChlodzenie = 4;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Chlodzenie()
{
  if (TemperaturaPowietrza > 30) {
    digitalWrite(PINWiatrakaZewnetrznego, LOW);
    digitalWrite(PINZielonaChlodzenie, HIGH);
  } else {
    digitalWrite(PINCzerwonaChlodzenie, HIGH);
  }
}
//________________________________________________CHLODZENIE__________________________________________________________________________________

//_____________________________________PODLEWANIE_____________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINZielonaPodlewanie = 5;
int PINpompa = 6;
int PINCzerwonaPodlewanie = 7;

unsigned long AktualnyCzas = 0;
unsigned long CzasPodlewania = 10000;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Podlewanie() {
  if (WilgotnoscGleby < 30) { //Jesli wilgotnosc gleby spadnie ponizej 30% wlacz pompe podlewajaca na 10 sekund
    AktualnyCzas = millis();
    if (millis() < AktualnyCzas + CzasPodlewania) {
      digitalWrite(PINpompa , LOW);
      digitalWrite(PINZielonaPodlewanie, HIGH);
      digitalWrite(PINCzerwonaPodlewanie, LOW);
    } else // wylacz pompe
      digitalWrite(PINpompa , HIGH);
    digitalWrite(PINZielonaPodlewanie, LOW);
    digitalWrite(PINCzerwonaPodlewanie, HIGH);
  }
}
//_____________________________________PODLEWANIE_____________________________________________________________________________________________

//____________________ZEGAR___________________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Zmienne dotyczace czasu
int rok; int miesiac; int dzien;
int godzina; int minuta; int sekunda;
const char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Zegar()
{
  tmElements_t tm;
  if (RTC.read(tm)) {
    godzina = tm.Hour; minuta = tm.Minute; sekunda = tm.Second; rok = tm.Year; miesiac = tm.Month; dzien = tm.Day;
    wyswietlacz();
  } else {
    if (RTC.chipPresent()) {
      lcd.println("DS1307 stoi. Uruchom Zegar");
    }
    else {
      lcd.println("DS1307 blad oczczytu!"); lcd.println("sprawdz polaczenie");
    }
    delay(9000);
  }
  delay(1000);
}
//____________________ZEGAR___________________________________________________________________________________________________________________

//________________________________WIATRAK MIESZAJĄCY__________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINZielonaDiodaWiatrakaWewnetrznego = 8;
int PINWiatrakaWewnetrznego = 9;
int PINCzerwonaDiodaWiatrakaWewnetrznego = 10;

int MieszanieGodzinaON = 4;
int MieszanieGodzinaOFF = 22;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MieszaniePowietrza() {
  //wlacz Wiatrak wewnetrzny o godzinie MieszanieGodzinaON i wylacz o godzinie MieszanieGodzinaOFF
  if ( godzina > MieszanieGodzinaON && godzina < MieszanieGodzinaOFF) {
    digitalWrite(PINWiatrakaWewnetrznego, LOW);
    digitalWrite(PINZielonaDiodaWiatrakaWewnetrznego, HIGH);
    digitalWrite(PINCzerwonaDiodaWiatrakaWewnetrznego, LOW);
    Serial.println("Wiatrak Mieszajacy wlaczony"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);

  } else
    //wylacz o godzinie MieszanieGodzinaOFF i wypisz na Serial Monitorze ze wiatraj jest wylaczony
  {
    digitalWrite(PINWiatrakaWewnetrznego, HIGH);
    digitalWrite(PINCzerwonaDiodaWiatrakaWewnetrznego, HIGH);
    digitalWrite(PINZielonaDiodaWiatrakaWewnetrznego, LOW);
    Serial.println("Wiatrak Mieszajacy wylaczony"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);
  }
}
//________________________________WIATRAK MIESZAJĄCY__________________________________________________________________________________________


//____________________OSWIETLENIE_____________________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINZielonaDiodaSwiatlo = 11;
int PINswiatlo = 12;
int PINCzerwonaDiodaSwiatlo = 13;

int SwiatloGodzinaON = 9;
int SwiatloGodzinaOFF = 23;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Swiatlo() {
  //wlacz swiatlo o godzinie SwiatloGodzinaON
  if ( godzina > SwiatloGodzinaON && godzina < SwiatloGodzinaOFF) {
    digitalWrite(PINswiatlo, LOW);
    digitalWrite(PINZielonaDiodaSwiatlo, HIGH);
    digitalWrite(PINCzerwonaDiodaSwiatlo, LOW);
    Serial.println("Swiatlo wlaczone"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);

  } else
    //Wylacz Oswietlenie o godzinie SwiatloGodzinaOFF 23
  {
    digitalWrite(PINswiatlo, HIGH);
    digitalWrite(PINCzerwonaDiodaSwiatlo, HIGH);
    digitalWrite(PINZielonaDiodaSwiatlo, LOW);
    Serial.println("Swiatlo wylaczone"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);
  }
}
//____________________OSWIETLENIE_____________________________________________________________________________________________________________


//____________________WYSWIETLACZ LCD_________________________________________________________________________________________________________
void wyswietlacz() {
  lcd.scrollDisplayLeft();
  lcd.setCursor (0, 0); LCDprint2digits(godzina); lcd.print(':'); LCDprint2digits(minuta); lcd.print(':'); LCDprint2digits(sekunda);
  lcd.setCursor (0, 1); LCDprint2digits(dzien); lcd.print('/'); lcd.print(monthName[miesiac - 1]); lcd.print('/'); lcd.print(tmYearToCalendar(rok));
  lcd.setCursor (9, 0); lcd.print("Temp Pow: "); LCDprint2digits(TemperaturaPowietrza); lcd.print("*C");
  lcd.setCursor (12, 1); lcd.print("Wilg Pow:"); LCDprint2digits(WilgotnoscPowietrza); lcd.print("%");
  lcd.setCursor (24, 0); lcd.print("Wilg Gleby: "); LCDprint2digits(WilgotnoscGleby); lcd.print("%");
}
void LCDprint2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}
//____________________WYSWIETLACZ LCD___________________________________________________________________________________________________________

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); lcd.backlight(); lcd.setBacklight(HIGH);
  //ustawZegar();
  // hurtowa inicjalizacja pinow 2-14 na wyjscia
  for (int i = 2; i < 14; i++){
    pinMode(i, OUTPUT);
  }
  //inicjalizacja Pinow wejscia
  pinMode(A0,INPUT);
}
void loop() {
  Zegar();
  CzujnikWilgotnosciGleby();
  CzujnikDHT11();
  Swiatlo();
  MieszaniePowietrza();
}
