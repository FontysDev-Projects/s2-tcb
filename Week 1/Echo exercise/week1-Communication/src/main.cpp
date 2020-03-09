#include <Arduino.h>

char c;

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{ // put your main code here, to run repeatedly:

  if (Serial.available() > 0)
  {
    Serial.readBytes(&c, 1);       
  }
  
  if (c != 0)
  {
    switch (c)
    {
    case (char)0x08:
      Serial.print(c);
      Serial.print((char)0x20);
      Serial.print(c);
      break;
    
    default:
    Serial.print(c);
      break;
    }
  }
  c = 0;
}
