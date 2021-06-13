#define ENG_ad 9
#define ENG_ae 6
#define ENG_bd 5
#define ENG_be 3

void setup()
{
  
}

void loop()
{
  analogWrite(ENG_ad, 255);
  analogWrite(ENG_be, 255);
  analogWrite(ENG_ae, 0);
  analogWrite(ENG_bd, 0);

  delay(1000);

  analogWrite(ENG_ad, 0);
  analogWrite(ENG_be, 0);
  analogWrite(ENG_ae, 255);
  analogWrite(ENG_bd, 255);

  delay(1000);

  analogWrite(ENG_ad, 0);
  analogWrite(ENG_be, 0);
  analogWrite(ENG_ae, 0);
  analogWrite(ENG_bd, 0);

  delay(1000);
}
