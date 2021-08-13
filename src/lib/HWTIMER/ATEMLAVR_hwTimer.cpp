#ifdef PLATFORM_ATMELAVR
#include "ATMELAVR_hwTimer.h"
#include <TimerOne.h>

void inline hwTimer::nullCallback(void) {}

void (*hwTimer::callbackTick)() = &nullCallback;
void (*hwTimer::callbackTock)() = &nullCallback;

volatile uint32_t hwTimer::HWtimerInterval = TimerIntervalUSDefault;
volatile bool hwTimer::isTick = true;
volatile int32_t hwTimer::PhaseShift = 0;
volatile int32_t hwTimer::FreqOffset = 0;
bool hwTimer::running = false;

#define HWTIMER_TICKS_PER_US 5

void hwTimer::init()
{
    if (!running)
    {
        Timer1.initialize(hwTimer::HWtimerInterval >> 1);
        Timer1.attachInterrupt(hwTimer::callback);
        isTick = true;
        running = true;
    }
}

void hwTimer::stop()
{
    if (running)
    {
        Timer1.stop();
        Timer1.detachInterrupt();
        running = false;
    }
}

void ICACHE_RAM_ATTR hwTimer::resume()
{
    if (!running)
    {
        init();
        running = true;
    }
}

void hwTimer::updateInterval(uint32_t newTimerInterval)
{
    hwTimer::HWtimerInterval = newTimerInterval * HWTIMER_TICKS_PER_US;
    if (running)
    {
        Timer1.setPeriod(hwTimer::HWtimerInterval >> 1);
    }
}

void ICACHE_RAM_ATTR hwTimer::resetFreqOffset()
{
    FreqOffset = 0;
}

void ICACHE_RAM_ATTR hwTimer::incFreqOffset()
{
    FreqOffset++;
}

void ICACHE_RAM_ATTR hwTimer::decFreqOffset()
{
    FreqOffset--;
}

void ICACHE_RAM_ATTR hwTimer::phaseShift(int32_t newPhaseShift)
{
    int32_t minVal = -(hwTimer::HWtimerInterval >> 2);
    int32_t maxVal = (hwTimer::HWtimerInterval >> 2);

    hwTimer::PhaseShift = constrain(newPhaseShift, minVal, maxVal) * HWTIMER_TICKS_PER_US;
}

void ICACHE_RAM_ATTR hwTimer::callback()
{
    if (!running)
    {
        return;
    }

    if (hwTimer::isTick)
    {
        Timer1.setPeriod((hwTimer::HWtimerInterval >> 1) + FreqOffset);
        hwTimer::callbackTick();
    }
    else
    {
        Timer1.setPeriod((hwTimer::HWtimerInterval >> 1) + hwTimer::PhaseShift + FreqOffset);
        hwTimer::PhaseShift = 0;
        hwTimer::callbackTock();
    }
    hwTimer::isTick = !hwTimer::isTick;
}
#endif
