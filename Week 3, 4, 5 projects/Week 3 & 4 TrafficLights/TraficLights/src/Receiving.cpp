#include <TrafficLightsCommunication.h>

void receivingData()
{
    if (traficLightBus.available() > 0)
    {
        if (isMaster)
        {
            ReceiveMaster();
        }
        else
        {
            ReceiveSlave();
        }
    }
}
