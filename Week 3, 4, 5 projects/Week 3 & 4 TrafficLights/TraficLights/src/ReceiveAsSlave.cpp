#include <TrafficLightsCommunication.h>

void ReceiveSlave()
{
    //Serial.println(traficLightBus.read());
    switch (traficLightBus.read())
    {
    case 0xFF: //Report back
        //checks if there is a car
        if (ThereIsACar)
        { //if there is a car
            commandToBeSend = C_ACK;
        }
        else
        { // if no carr detected
            commandToBeSend = C_NACK;
        }
        COM_BUSS_State = COM_BUSS_TRANSMITTING;
        break;

    case 0xFD: //C_CHANGE_LIGHT_GREEN
        LightState = LIGHTS_GREEN;
        commandToBeSend = C_ACK;
        COM_BUSS_State = COM_BUSS_TRANSMITTING;
        break;
    case 0xFC: //C_CHANGE_LIGHT_RED
        LightState = LIGHTS_RED;
        commandToBeSend = C_ACK;
        COM_BUSS_State = COM_BUSS_TRANSMITTING;
        break;

    default:
        // both leds are light-up
        LightState = LIGHTS_ROAD_CLOSED;
        COM_BUSS_State = COM_BUSS_TRANSMITTING;
        break;
    }
}