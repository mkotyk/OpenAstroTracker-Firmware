#ifndef _STALLHOMING_HPP
#define _STALLHOMING_HPP

#include "Types.hpp"
#include "Mount.hpp"

/////////////////////////////////
//
// class StallHoming
//
/////////////////////////////////
class StallHoming
{
public:
    enum Result
    {
        STALL_HOMING_RESULT_SUCCEEDED = 1,
        STALL_HOMING_RESULT_HOMING_NEVER_RUN = 0,
        STALL_HOMING_RESULT_HOMING_IN_PROGRESS = -1
    };

    enum State
    {
        STALL_HOMING_START_FIND_LIMIT = 0,
        STALL_HOMING_FINDING_LIMIT,
        STALL_HOMING_LIMIT_FOUND,
        STALL_HOMING_TRAVEL_TO_OFFSET,
        STALL_HOMING_FAILED,
        STALL_HOMING_SUCCESSFUL,
        STALL_HOMING_NOT_ACTIVE,

        STALL_HOMING_TERMINATOR
    };

    StallHoming(Mount& mount, StepperAxis axis, uint32_t diagPin)
        : _pMount(mount)
        , _axis((axis))
        , _diagPin(diagPin)
    {
        _state = STALL_HOMING_NOT_ACTIVE;
        _lastResult = STALL_HOMING_RESULT_HOMING_NEVER_RUN;
        _wasTracking = _pMount.isSlewingTRK();
        pinMode(_diagPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(_diagPin), [this] { this->ISRDiagTriggered(); }, RISING);

    }

    bool findHome();
    void processHomingProgress();
    static String getHomingState(State state);
    State getHomingState() const;
    bool isIdleOrComplete() const
    {
        return _state == STALL_HOMING_NOT_ACTIVE;
    }
    String getLastResult() const;
private:
    void ISRDiagTriggered();

    Mount &_pMount;
    StepperAxis _axis;
    uint32_t _diagPin;
    int _savedRate;
    State _state;
    Result _lastResult;
    bool _wasTracking;
};

#endif
