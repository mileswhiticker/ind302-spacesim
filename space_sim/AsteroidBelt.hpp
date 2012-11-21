#ifndef ASTEROID_BELT_HPP
#define ASTEROID_BELT_HPP

#include "HabitableObject.hpp"
#include "DisplayableObject.hpp"

class StarSystem;

class AsteroidBelt
:	public HabitableObject
,	public DisplayableObject
{
public:
	AsteroidBelt(StarSystem* a_pParent);
	virtual ~AsteroidBelt();
	//
protected:
	void GenerateContents();
	//
private:
	//
};

#endif	//ASTEROID_BELT_HPP