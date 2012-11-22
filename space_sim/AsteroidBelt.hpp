#ifndef ASTEROID_BELT_HPP
#define ASTEROID_BELT_HPP

#include "HabitableObject.hpp"
#include "DisplayableObject.hpp"

class AsteroidBelt
:	public HabitableObject
,	public DisplayableObject
{
public:
	AsteroidBelt();
	virtual ~AsteroidBelt();
	//
private:
	//
};

#endif	//ASTEROID_BELT_HPP