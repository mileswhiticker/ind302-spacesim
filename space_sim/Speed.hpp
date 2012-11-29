#ifndef SPEED_H
#define SPEED_H

#include "DisplayableObject.hpp"
#include "TimeRate.h"

#define HOURS_PLANET 1.f
#define DAYS_STARSYSTEM 3.f
#define WEEKS_STELLARGROUP 6.f
#define MONTHS_ORIONSPUR 12.f

//amount of real life time to go 1 descartan unit (halfway across the screen) at the scale of the specified DisplayableObject
float GetRealtimeToCross(TimeRate a_TimeRate, DisplayableObject::DisplayableType a_DispType);

#endif	//SPEED_H