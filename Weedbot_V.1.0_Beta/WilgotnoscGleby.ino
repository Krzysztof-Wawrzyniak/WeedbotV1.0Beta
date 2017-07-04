//____________________WILGOTNOŚĆ GLEBY_________________________________________________________________________________________________________
int WilgotnoscGleby = 99;
void CzujnikWilgotnosciGleby() {
  // Odczytaj wartosc z czujnika wilgotnosci gleby:
  int  wartosc_odczytu = analogRead(A0);

  WilgotnoscGleby = map(wartosc_odczytu, 1023, 0, 0, 100);
  Podlewanie();
}
//____________________WILGOTNOŚĆ GLEBY_________________________________________________________________________________________________________

