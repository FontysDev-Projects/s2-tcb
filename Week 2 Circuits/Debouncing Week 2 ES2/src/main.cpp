#include <Arduino.h>
#include <Bounce2.h>

#define DAY_LED 5
#define NIGHT_LED 6
#define SWITCH 9

typedef enum State
{
  DAY_MODE,
  NIGHT_MODE
} state;

state State = DAY_MODE;

Bounce deboucer = Bounce();

void SwitchLights(state);

void setup()
{
  pinMode(DAY_LED, OUTPUT);
  pinMode(NIGHT_LED, OUTPUT);

  pinMode(SWITCH, INPUT_PULLUP);

  deboucer.attach(SWITCH);
  deboucer.interval(20);

  //Serial.begin(9600);
}

void loop()
{
  deboucer.update();

  if (deboucer.fell())
  {
    if (State == DAY_MODE)
    {
      State = NIGHT_MODE;
    }
    else
    {
      State = DAY_MODE;
    }
    SwitchLight(State);
  }
}

void SwitchLight(state State)
{
  switch (State)
  {
  case DAY_MODE:
    digitalWrite(DAY_LED, HIGH);
    digitalWrite(NIGHT_LED, LOW);
    break;
  case NIGHT_MODE:
    digitalWrite(DAY_LED, LOW);
    digitalWrite(NIGHT_LED, HIGH);
    break;
  }
}