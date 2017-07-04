//____________________WYSWIETLACZ LCD_________________________________________________________________________________________________________
void wyswietlacz() {

  lcd.setCursor (0, 0); LCDprint2digits(godzina); lcd.print(':'); LCDprint2digits(minuta);// lcd.print(':'); LCDprint2digits(sekunda);
  lcd.setCursor (0, 1); LCDprint2digits(dzien); lcd.print('/'); lcd.print(monthName[miesiac - 1]); // lcd.print('/'); lcd.print(tmYearToCalendar(rok));
  lcd.setCursor (5, 0); lcd.print("T:"); LCDprint2digits(TemperaturaPowietrza); lcd.print("C");
  lcd.setCursor (7, 1); lcd.print("W:"); LCDprint2digits(WilgotnoscPowietrza); lcd.print("%");
  lcd.setCursor (11, 0); lcd.print("G:"); LCDprint2digits(WilgotnoscGleby); lcd.print("%");

}
void LCDprint2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}

//____________________WYSWIETLACZ LCD_____________________________________________________________________________________________________

