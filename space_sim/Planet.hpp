#ifndef PLANET_HPP
#define PLANET_HPP

#include "HabitableObject.hpp"
#include "DisplayableObject.hpp"

class StarSystem;

class Planet
:	public HabitableObject
,	public DisplayableObject
{
public:
	Planet(HabitableObject::HabitableType a_NewType, StarSystem* a_pOrbitingStarSystem);
	virtual ~Planet();
	//
private:
	//
};

#endif	//PLANET_HPP