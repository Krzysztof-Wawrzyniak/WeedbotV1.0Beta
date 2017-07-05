int PINpompa = 5;
int PINZielonaPodlewanie = 6;
int PINCzerwonaPodlewanie = 7;

void Podlewanie(){
  if(WilgotnoscGleby<30){
    digitalWrite(PINpompa , LOW);
    digitalWrite(PINZielonaPodlewanie,HIGH);
  }else {
    digitalWrite(PINCzerwonaPodlewanie,HIGH);
  }
    
}

