#ifndef PLANET_HPP
#define PLANET_HPP

#include "HabitableObject.hpp"

class StarSystem;

class Planet
:	public HabitableObject
{
public:
	Planet(type a_NewType, StarSystem* a_pOrbitingStarSystem);
	virtual ~Planet();
	//
private:
	//
};

#endif	//PLANET_HPP