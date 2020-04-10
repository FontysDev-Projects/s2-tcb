#include <TrafficLightsCommunication.h>

void ReceiveMaster()
{
    if (lastCommandSend == C_REPORT_BACK)
    {
        switch (traficLightBus.read())
        {
        case 0x01: //C_ACK - car detected
                   //led red
            if (ThereIsACar && hasElapsed)
            {
                LightState = LIGHTS_GREEN;
                commandToBeSend = C_CHANGE_LIGHT_RED;
            }
            else
            {
                LightState = LIGHTS_RED;
                commandToBeSend = C_CHANGE_LIGHT_GREEN;
            }
            COM_BUSS_State = COM_BUSS_TRANSMITTING;
            break;

        case 0x02: //C_NACK - no car detected
            // led green
            if (ThereIsACar)
            {
                LightState = LIGHTS_GREEN;
                commandToBeSend = C_CHANGE_LIGHT_RED;
            }
            else
            {
                LightState = LIGHTS_RED;
                commandToBeSend = C_CHANGE_LIGHT_RED;
            }

            COM_BUSS_State = COM_BUSS_TRANSMITTING;
            break;

        default:
            // both leds are light-up
            LightState = LIGHTS_ROAD_CLOSED;
            COM_BUSS_State = COM_BUSS_TRANSMITTING;
            break;
        }
    }
    else
    {
        switch (traficLightBus.read())
        {
        case 0x01: //C_ACK
            commandToBeSend = C_REPORT_BACK;
            COM_BUSS_State = COM_BUSS_TRANSMITTING;
            Timer(5000);
            break;

        case 0x02: //C_NACK
            transmitingData(lastCommandSend);
            break;

        default:
            // both leds are light-up
            LightState = LIGHTS_ROAD_CLOSED;
            COM_BUSS_State = COM_BUSS_TRANSMITTING;
            break;
        }
    }
}