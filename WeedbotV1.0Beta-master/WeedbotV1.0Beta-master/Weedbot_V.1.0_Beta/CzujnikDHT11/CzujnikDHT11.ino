
//CZUJNIK TEMPERATURY I WILGOTNOŚCI_________________________________________________________________________________________________________
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT11     // DHT 11 (AM2302)

DHT dht(DHTPIN, DHTTYPE);
int TemperaturaPowietrza = 99;
int WilgotnoscPowietrza = 99;

void CzujnikDHT11() {
  //Odczyt temperatury i wilgotności z czujnika DHT11

  TemperaturaPowietrza = dht.readTemperature();
  WilgotnoscPowietrza = dht.readHumidity();
  Chlodzenie();
}
//CZUJNIK TEMPERATURY I WILGOTNOŚCI_________________________________________________________________________________________________________

