#ifndef DEFINITIONS
#define DEFINITIONS

#define RED_LED 5
#define GREEN_LED 6

#define CAR_SENSOR 8

#include <Arduino.h>
#include <SoftwareSerial.h>

//--------------------TrafficLightBUS-Start-------------------//
#define RXpin 2
#define TXpin 3

SoftwareSerial traficLightBus = SoftwareSerial(RXpin, TXpin);

LightStates LightState = LIGHTS_RED;

CommunicationState COM_BUSS_State = COM_BUSS_TRANSMITTING;

Commands commandToBeSend = C_REPORT_BACK;
Commands lastCommandSend = C_REPORT_BACK;

const uint8_t msg[][1] = {{0xFF},  //  report back
                          {0xFD},  //  chage light to Green
                          {0xFC},  //  chage light to Red
                          {0x01},  //  Ack
                          {0x02}}; //  NACK

//
void TraficLightsCommunications();
void receivingData();
void ReceiveMaster();
void ReceiveSlave();
void transmitingData(Commands);

bool isMaster;
//--------------------TrafficLightBUS-End--------------------//

//--------------------CarDetector-Start----------------------//

void carDetector();
bool ThereIsACar;

//--------------------CarDetector-End------------------------//

//--------------------TrafficLightControl-Start-------------------//

void LightsState();
void Timer(uint32_t elapseTime);
bool hasElapsed = false;
uint32_t timeCheck = 0;

//--------------------TrafficLightControl-End---------------------//

//
#endif
