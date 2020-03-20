//
#ifndef TRAFFIC_BUSS_COM
#define TRAFFIC_BUSS_COM

#include <Arduino.h>
#include <SoftwareSerial.h>

extern SoftwareSerial traficLightBus;

typedef enum LightStates
{
    LIGHTS_RED,
    LIGHTS_GREEN,
    LIGHTS_ROAD_CLOSED
} LightStates;

extern LightStates LightState;

//
typedef enum CommunicationState
{
    COM_BUSS_RECEIVING,
    COM_BUSS_TRANSMITTING
} CommunicationState;

extern CommunicationState COM_BUSS_State;

typedef enum Commands
{
    C_REPORT_BACK,
    C_CHANGE_LIGHT_GREEN,
    C_CHANGE_LIGHT_RED,
    C_ACK,
    C_NACK
} Commands;

extern Commands commandToBeSend;
extern Commands lastCommandSend;

extern const uint8_t msg[][1];
//
extern void TraficLightsCommunications();

extern void receivingData();
extern void ReceiveMaster();
extern void ReceiveSlave();

extern void transmitingData(Commands);
extern void Timer(uint32_t elapseTime);

extern bool isMaster;

extern bool ThereIsACar;

extern uint32_t timeCheck;
extern bool hasElapsed;
//
#endif