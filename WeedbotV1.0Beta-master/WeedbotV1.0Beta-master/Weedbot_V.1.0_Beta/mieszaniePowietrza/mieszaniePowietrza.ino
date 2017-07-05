//________________________________WIATRAK MIESZAJĄCY__________________________________________________________________________________________

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PINWiatrakaWewnetrznego = 11;
int PINZielonaDiodaWiatrakaWewnetrznego = 12;
int PINCzerwonaDiodaWiatrakaWewnetrznego = 13;
int MieszanieGodzinaON = 4;
int MieszanieGodzinaOFF = 22;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MieszaniePowietrza() {
  //wlacz swiatlo o godzinie SwiatloGodzinaON i minucie SwiatloMinutaON
  if ( godzina > MieszanieGodzinaON && godzina < MieszanieGodzinaOFF) {
    digitalWrite(PINWiatrakaWewnetrznego, LOW);
    digitalWrite(PINZielonaDiodaWiatrakaWewnetrznego, HIGH);
    Serial.println("Wiatrak Mieszajacy wlaczony"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);

  } else
    //wylacz swiatlo o godzinie SwiatloGodzinaOFF i minucie SwiatloMinutaOFF
    //  if (godzina < SwiatloGodzinaOFF && minuta < SwiatloMinutaOFF)
  {
    digitalWrite(PINWiatrakaWewnetrznego, HIGH);
    digitalWrite(PINCzerwonaDiodaWiatrakaWewnetrznego, HIGH);
    Serial.println("Wiatrak Mieszajacy wylaczony"); Serial.print(godzina); Serial.print(":"); Serial.print(minuta); Serial.print(":"); Serial.println(sekunda);
  }
}
//________________________________WIATRAK MIESZAJĄCY__________________________________________________________________________________________
