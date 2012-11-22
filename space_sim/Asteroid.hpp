#ifndef ASTEROID_BELT_HPP
#define ASTEROID_BELT_HPP

#include "HabitableObject.hpp"
#include "DisplayableObject.hpp"

class StarSystem;

class Asteroid
:	public HabitableObject
{
public:
	Asteroid(HabitableObject::HabitableType a_MyType, StarSystem* a_pParent);
	virtual ~Asteroid();
	//
protected:
	void GenerateContents();
	//
private:
	//
};

#endif	//ASTEROID_BELT_HPP