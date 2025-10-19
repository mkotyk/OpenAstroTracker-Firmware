#ifndef _SOFTENDSTOP_HPP
#define _SOFTENDSTOP_HPP

#include "Types.hpp"
#include "Mount.hpp"

class Mount;

/////////////////////////////////
//
// class SoftEndStop
//
// Uses stall homing to determine the physical minimum of movement and then uses
// predefined distance and padding to set a software end stop to prevent hitting the physical limits
// in normal operation.
//
/////////////////////////////////
class SoftEndStop
{
public:
    enum State
    {
        SOFT_END_STOP_NOT_CONFIGURED,
        SOFT_END_STOP_ACTIVE,
        SOFT_END_STOP_TRIGGERED,
    };

    SoftEndStop(Mount& mount, const StepperAxis axis, const long rangeSteps)
        : SoftEndStop(mount, axis, rangeSteps, mount.getStepsPerDegree(axis) * 0.5f) {}

    SoftEndStop(Mount& mount, const StepperAxis axis, const long rangeSteps, const long paddingSteps)
        : _pMount(mount)
        , _axis(axis)
        , _rangeSteps(rangeSteps)
        , _paddingSteps(paddingSteps)
    {
        _state = SOFT_END_STOP_NOT_CONFIGURED;
    }

    void setMinPosition(const long minPositionSteps)
    {
        // Set stepper min/max absolute positions with some padding so we don't risk physical contact
        _minPositionSteps = minPositionSteps + _paddingSteps;
        _maxPositionSteps = (_minPositionSteps + _rangeSteps) - _paddingSteps;
        _state = SOFT_END_STOP_ACTIVE;
    }

    void clearTrigger()
    {
        _state = SOFT_END_STOP_ACTIVE;
    }

    bool checkLimits()
    {
        if (_state == SOFT_END_STOP_ACTIVE)
        {
            auto minTriggered = _pMount.getCurrentStepperPosition(_axis) <= _minPositionSteps;
            auto maxTriggered = _pMount.getCurrentStepperPosition(_axis) >= _maxPositionSteps;

            if (minTriggered || maxTriggered)
            {
                _state = SOFT_END_STOP_TRIGGERED;
                _pMount.stopSlewing(_axis);
                _pMount.stopGuiding(_axis);
                _pMount.waitUntilStopped(_axis);
            }
            return minTriggered || maxTriggered;
        }

        return false;
    }

    State getState() const
    {
        return _state;
    }
private:
    Mount & _pMount;
    const StepperAxis _axis;
    State _state;

    long _paddingSteps;
    long _rangeSteps;
    long _minPositionSteps;
    long _maxPositionSteps;
};

#endif
