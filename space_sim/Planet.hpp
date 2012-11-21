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
	Planet(StarSystem* a_pParent, HabitableObject::HabitableType a_NewType);
	//
protected:
	void GenerateContents();
	//
private:
	//
};

class Star
:	public HabitableObject
,	public DisplayableObject
{
public:
	Star(StarSystem* a_pParent);
	//
protected:
	void GenerateContents();
	//
private:
	//
};


#endif	//PLANET_HPP