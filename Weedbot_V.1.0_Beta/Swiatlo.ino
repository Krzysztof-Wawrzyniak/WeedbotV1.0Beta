//____________________OSWIETLENIE_________________________________________________________________________________________________________

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINswiatlo = 4;
int PINZielonaDiodaSwiatlo = 5;
int PINCzerwonaDiodaSwiatlo = 6;
int SwiatloGodzinaON = 4;
int SwiatloGodzinaOFF = 22;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Swiatlo() {
  //wlacz swiatlo o godzinie SwiatloGodzinaON i minucie SwiatloMinutaON
  if ( godzina > SwiatloGodzinaON && godzina < SwiatloGodzinaOFF) {
    digitalWrite(PINswiatlo, LOW);
    digitalWrite(PINZielonaDiodaSwiatlo, HIGH);
    Serial.println("Swiatlo wlaczone"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);

  } else
    //wylacz swiatlo o godzinie SwiatloGodzinaOFF i minucie SwiatloMinutaOFF
    //  if (godzina < SwiatloGodzinaOFF && minuta < SwiatloMinutaOFF)
  {
    digitalWrite(PINswiatlo, HIGH);
    digitalWrite(PINCzerwonaDiodaSwiatlo, HIGH);
    Serial.println("Swiatlo wylaczone"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);
  }
}
//____________________OSWIETLENIE_________________________________________________________________________________________________________
