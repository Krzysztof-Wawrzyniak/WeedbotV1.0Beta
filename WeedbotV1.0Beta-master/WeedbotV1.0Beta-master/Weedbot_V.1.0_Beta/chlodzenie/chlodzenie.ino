//________________________CHLODZENIE_______________________________
int PINWiatrakaZewnetrznego = 8;
int PINZielonaChlodzenie = 9;
int PINCzerwonaChlodzenie = 10;

void Chlodzenie() 
{
  if (TemperaturaPowietrza > 30) {
    digitalWrite(PINWiatrakaZewnetrznego,LOW);
    digitalWrite(PINZielonaChlodzenie,HIGH);
  } else {
    digitalWrite(PINCzerwonaChlodzenie,HIGH);
  }
  
}
//________________________CHLODZENIE_______________________________
