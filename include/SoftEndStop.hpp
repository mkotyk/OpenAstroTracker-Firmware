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
    };

    SoftEndStop(const StepperAxis axis, const long rangeSteps, const long paddingSteps)
        : _axis(axis)
        , _state(SOFT_END_STOP_NOT_CONFIGURED)
        , _rangeSteps(rangeSteps)
        , _paddingSteps(paddingSteps)
        , _minPositionSteps(0L)
        , _maxPositionSteps(0L)
    {
        LOG(DEBUG_MOUNT, "[SOFTENDSTOP] %s axis: Range steps:%l Padding steps:%l",
            _axis == RA_STEPS ? F("RA") : F("DEC"),
            _rangeSteps,
            _paddingSteps
        );
    }

    void setMinPosition(const long minPositionSteps)
    {
        // Set stepper min/max absolute positions with some padding so we don't risk physical contact
        _minPositionSteps = minPositionSteps + _paddingSteps;
        _maxPositionSteps = minPositionSteps + _rangeSteps - _paddingSteps;
        _state = SOFT_END_STOP_ACTIVE;
        LOG(DEBUG_MOUNT, "[SOFTENDSTOP] %s axis: Range steps:%l Padding steps:%l Min steps:%l Max steps:%l",
            _axis == RA_STEPS ? F("RA") : F("DEC"),
            _rangeSteps,
            _paddingSteps,
            _minPositionSteps,
            _maxPositionSteps
        );
    }

    void invalidate()
    {
        _state = SOFT_END_STOP_NOT_CONFIGURED;
    }

    bool canMoveTowardMin(Mount& mount)
    {
        auto position = mount.getCurrentStepperPosition(_axis);
        return _state != SOFT_END_STOP_ACTIVE || position > _minPositionSteps;
    }

    bool canMoveTowardMax(Mount& mount)
    {
        auto position = mount.getCurrentStepperPosition(_axis);
        return _state != SOFT_END_STOP_ACTIVE || position < _maxPositionSteps;
    }

    bool checkLimits(Mount& mount)
    {
        if (_state == SOFT_END_STOP_ACTIVE)
        {
            auto position = mount.getCurrentStepperPosition(_axis);
            auto direction = mount.direction(_axis);
            auto minTriggered = position <= _minPositionSteps && direction < 0;
            auto maxTriggered = position >= _maxPositionSteps && direction > 0;

            if (minTriggered || maxTriggered)
            {
                LOG(DEBUG_MOUNT, "[SOFTENDSTOP] %s axis %s triggered: Min steps:%l Position:%l  Max steps:%l",
                        _axis == RA_STEPS ? F("RA") : F("DEC"),
                        minTriggered ? F("MIN") : F("MAX"),
                        _minPositionSteps,
                        position,
                        _maxPositionSteps
                   );
                mount.stopSlewing(_axis);
                mount.stopGuiding(_axis);
                mount.waitUntilStopped(_axis);
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
    const StepperAxis _axis;
    State _state;
    long _rangeSteps;
    long _paddingSteps;
    long _minPositionSteps;
    long _maxPositionSteps;
};

#endif
