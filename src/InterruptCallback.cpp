#include "Configuration.hpp"
#include "Utility.hpp"
#include "InterruptCallback.hpp"

//////////////////////////////////////
// This is an hardware-independent abstraction layer over
// whatever timer is used for the hardware being run
//////////////////////////////////////


    #if defined ESP32
    // We don't support ESP32 boards in interrupt mode
    #elif defined __AVR_ATmega2560__  // Arduino Mega
        #define USE_TIMER_1 true
        #define USE_TIMER_2 true
        #define USE_TIMER_3 false
        #define USE_TIMER_4 false
        #define USE_TIMER_5 false
PUSH_NO_WARNINGS
        #include "libs/TimerInterrupt/TimerInterrupt.h"
POP_NO_WARNINGS
    #elif defined(ARDUINO_ARCH_STM32)
        #include "HardwareTimer.h"
    #else
        #error Unrecognized board selected. Either implement interrupt code or define the board here.
    #endif

    #if defined(ESP32)

    #elif defined __AVR_ATmega2560__

bool InterruptCallback::setInterval(uint32_t intervalMs, interrupt_callback_p callback, void *payload)
{
    // We have requested to use Timer2 (see above)
    ITimer2.init();

    // This timer supports the callback with payload
    return ITimer2.attachInterruptInterval<void *>(intervalMs / 1000.0f, callback, payload, 0UL);
}

void InterruptCallback::stop()
{
    ITimer2.stopTimer();
}

void InterruptCallback::start()
{
    ITimer2.restartTimer();
}
    #elif defined(ARDUINO_ARCH_STM32)
HardwareTimer timer(TIM3);
bool InterruptCallback::setInterval(uint32_t intervalMicroSeconds, interrupt_callback_p callback, void *payload)
{
    timer.setMode(1, TIMER_OUTPUT_COMPARE);
    timer.setPrescaleFactor(1);
    timer.setCount(intervalMicroSeconds, MICROSEC_FORMAT);
    timer.attachInterrupt(1, std::bind(callback, payload));
    timer.resume();
    return true;
}

void InterruptCallback::stop()
{
    timer.pause();
}

void InterruptCallback::start()
{
    timer.resume();
}


    #endif