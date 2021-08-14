#ifdef PLATFORM_ASR6501
#include "ASR6501_hwTimer.h"

void hwTimer::nullCallback(void) {}
void (*hwTimer::callbackTick)() = &nullCallback;
void (*hwTimer::callbackTock)() = &nullCallback;

volatile uint32_t hwTimer::HWtimerInterval = TimerIntervalUSDefault;

volatile bool hwTimer::isTick = false;
bool hwTimer::running = false;
bool hwTimer::alreadyInit = false;

volatile int32_t hwTimer::PhaseShift = 0;
volatile int32_t hwTimer::FreqOffset = 0;

TimerEvent_t hwTimer::MyTim; 

void ICACHE_RAM_ATTR hwTimer::callback(void)
{
    if (hwTimer::isTick)
    {
        hwTimer::callbackTick();
    }
    else
    {
        hwTimer::callbackTock();
    }
    hwTimer::isTick = !hwTimer::isTick;
}

void ICACHE_RAM_ATTR hwTimer::init()
{
    if (!alreadyInit)
    {
        TimerInit(&MyTim, &callback);
        TimerSetValue(&MyTim, HWtimerInterval);
        TimerStart(&MyTim);
        alreadyInit = true;
    }
}

void ICACHE_RAM_ATTR hwTimer::resume()
{
    running = true;
    TimerSetValue(&MyTim, HWtimerInterval);
    TimerStart(&MyTim);
    Serial.println("hwTimer resume");
}

void ICACHE_RAM_ATTR hwTimer::stop()
{
    running = false;
    TimerStop(&MyTim);
    Serial.println("hwTimer stop");
}

void ICACHE_RAM_ATTR hwTimer::updateInterval(uint32_t time)
{
    HWtimerInterval = time;
    Serial.print("hwTimer interval: ");
    Serial.println(time);
    TimerSetValue(&MyTim, HWtimerInterval);
    TimerStart(&MyTim);
}

void hwTimer::resetFreqOffset()
{
}

void hwTimer::incFreqOffset()
{
}

void hwTimer::decFreqOffset()
{
}

void hwTimer::phaseShift(int32_t newPhaseShift)
{
}

#endif
