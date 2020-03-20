#include <TrafficLightsCommunication.h>
#include <Definitions.h>

void setup()
{
  //SETTING UP THE PINMODES
  DDRD = DDRD | B01100000;
  PORTD = PORTD | B00000000;

  pinMode(CAR_SENSOR, INPUT_PULLUP);

  //STARTING SERIAL COMMUNICATION
  Serial.begin(9600);
  traficLightBus.begin(9600);

  isMaster = false;
  ThereIsACar = false;
}

void loop()
{
  carDetector();
  TraficLightsCommunications();
  LightsState();
}

void carDetector()
{
  if (digitalRead(CAR_SENSOR) == LOW)
  {
    ThereIsACar = true;
  }
  else
  {
    ThereIsACar = false;
  }
}

void TraficLightsCommunications()
{
  switch (COM_BUSS_State)
  {
  case COM_BUSS_RECEIVING:
    receivingData();
    break;

  case COM_BUSS_TRANSMITTING:
    transmitingData(commandToBeSend);
    break;
  }
}

void LightsState()
{
  switch (LightState)
  {
  case LIGHTS_RED:
    // PORTD = PORTD & B10000000;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    break;

  case LIGHTS_GREEN:
    //PORTD = PORTD ^ B10000000;
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    break;

  case LIGHTS_ROAD_CLOSED:
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    break;
  }
}