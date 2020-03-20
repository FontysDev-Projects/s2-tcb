#include <TrafficLightsCommunication.h>

void transmitingData(Commands command)
{
    traficLightBus.write(msg[(int)command][0]);
    lastCommandSend = command;
    COM_BUSS_State = COM_BUSS_RECEIVING;
}