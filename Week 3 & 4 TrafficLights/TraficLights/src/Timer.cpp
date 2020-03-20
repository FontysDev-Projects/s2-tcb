#include <TrafficLightsCommunication.h>

void Timer(uint32_t elapseTime)
{
    while (1)
    {
        if (millis() - timeCheck > elapseTime)
        {
            hasElapsed = !hasElapsed;
            timeCheck = millis();
            break;
        }
    }
}
