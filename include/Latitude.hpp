#pragma once

#include "DayTime.hpp"

// 90 at north pole, -90 at south pole
class Latitude : public DayTime // TODO: (MWK) Why is latitude derived from DayTime?
{
  public:
    Latitude() : DayTime()
    {
    }
    Latitude(const Latitude &other);
    Latitude(int h, int m, int s);
    Latitude(float inDegrees);

    static Latitude ParseFromMeade(String const &s);
    float getDegrees() const { return _degrees; }
  protected:
    float _degrees = NAN;
    virtual void checkHours() override;
};
