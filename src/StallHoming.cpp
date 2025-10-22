#include "Configuration.hpp"
#include "Utility.hpp"
#include "StallHoming.hpp"


/////////////////////////////////
//
// getHomingState
//
/////////////////////////////////
String StallHoming::getHomingState(const State state)
{
    static String lookupTable[STALL_HOMING_TERMINATOR] = {
        F("START FIND LIMIT"),
        F("FINDING_LIMIT"),
        F("LIMIT FOUND"),
        F("TRAVEL TO OFFSET"),
        F("FAILED"),
        F("SUCCESSFUL"),
        F("NOT_ACTIVE")
    };
    return lookupTable[state];
}

StallHoming::State StallHoming::getHomingState() const
{
    return _state;
}

/////////////////////////////////
//
// getLastResult
//
/////////////////////////////////
String StallHoming::getLastResult() const
{
    switch (_lastResult) {
        case STALL_HOMING_RESULT_SUCCEEDED:
            return F("SUCCEEDED");
        case STALL_HOMING_RESULT_HOMING_NEVER_RUN:
            return F("NEVER RUN");
        case STALL_HOMING_RESULT_HOMING_IN_PROGRESS:
            return F("IN PROGRESS");
    }
    return "UNKNOWN RESULT";
}

void StallHoming::ISRDiagTriggered()
{
    if (_state == STALL_HOMING_FINDING_LIMIT)
    {
        _pMount.axisStalled(_axis);
        _state = STALL_HOMING_LIMIT_FOUND;
    }
}

/////////////////////////////////
//
// findHomeByHallSensor
//
/////////////////////////////////
bool StallHoming::findHome()
{
    _lastResult = STALL_HOMING_RESULT_HOMING_IN_PROGRESS;
    // IMPORTANT: Make sure all tracking and slewing are stopped before getting here,
    // otherwise we overdrive the steppers when they hit.

    _savedRate = _pMount.getSlewRate();     // Wrong
    _pMount.setSlewRate(4);                 // Wrong!
    _pMount.setStatusFlag(STATUS_FINDING_HOME); // TODO: MWK This flags is not per-axis, this concurrent homing will break
    _state = STALL_HOMING_START_FIND_LIMIT;

    LOG(DEBUG_STEPPERS, "[HOMING]: Start homing procedure. Axis %d", (int) _axis);
    return true;
}

/////////////////////////////////
//
// processHomingProgress
//
/////////////////////////////////
void StallHoming::processHomingProgress()
{
    switch (_state)
    {
        case STALL_HOMING_NOT_ACTIVE:
            break;
        case STALL_HOMING_START_FIND_LIMIT:
            {
                LOG(DEBUG_STEPPERS, "[HOMING]: Finding limit. Moving until motor stalls.");
                auto maxDistance = _pMount.getStepsPerDegree(_axis) * 360; // 360 is too much, but that's fine - we will stop when we hit the limit
                _pMount.moveStepperBy(_axis, -maxDistance);
                _state = STALL_HOMING_FINDING_LIMIT;
            }
            break;
        case STALL_HOMING_FINDING_LIMIT:
            // The interrupt handles this and will transition into STALL_HOMING_LIMIT_FOUND

            // Uncomment this line if you need to tune stallguard.
            // LOG(DEBUG_STEPPERS, "[HOMING]: SG_RESULT: %d  TSTEP:%d", _pMount.getSgResult(_axis), _pMount.getTSTEP(_axis));
            break;
        case STALL_HOMING_LIMIT_FOUND:
            {
                LOG(DEBUG_STEPPERS, "[HOMING]: Stall Homing Limit Found");
                _state = STALL_HOMING_TRAVEL_TO_OFFSET;
                _pMount.stopSlewing(_axis);
                _pMount.homeAxisMin(_axis);
                _pMount.clearAxisStall(_axis);
                _pMount.moveStepperTo(_axis, 0);
            }
            break;
        case STALL_HOMING_TRAVEL_TO_OFFSET:
            if (_pMount.getCurrentStepperPosition(_axis) == 0)
            {
                _state = STALL_HOMING_SUCCESSFUL;
            }
            break;
        case STALL_HOMING_SUCCESSFUL:
            {
                LOG(DEBUG_STEPPERS,
                    "[HOMING]: Successfully homed! Setting home and restoring Rate setting. Advance to %s",
                    getHomingState(STALL_HOMING_NOT_ACTIVE).c_str());
                _lastResult = STALL_HOMING_RESULT_SUCCEEDED;
                _state = STALL_HOMING_NOT_ACTIVE;
                _pMount.setSlewRate(_savedRate);// TODO: MWK This should be per axis
                _pMount.clearStatusFlag(STATUS_FINDING_HOME);// TODO: MWK This should be per axis
                if (_wasTracking)
                {
                    _pMount.startSlewing(TRACKING);// TODO: MWK This should be per axis
                }
            }
            break;

        case STALL_HOMING_FAILED:
            {
                LOG(DEBUG_STEPPERS,
                    "[HOMING]: Failed to home! Restoring Rate setting. Advance to %s",
                    getHomingState(STALL_HOMING_NOT_ACTIVE).c_str());
                _state = STALL_HOMING_NOT_ACTIVE;
                _pMount.setSlewRate(_savedRate);// TODO: MWK This should be per axis
                _pMount.clearStatusFlag(STATUS_FINDING_HOME);// TODO: MWK This should be per axis
            }
            break;

        default:
            LOG(DEBUG_STEPPERS, "[HOMING]: Unhandled state (%d)! ", _state);
            break;
    }
}
