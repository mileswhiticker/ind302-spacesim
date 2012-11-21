#include "Planet.hpp"

#include "StarSystem.hpp"
#include "Defines_Math.h"

Planet::Planet(StarSystem* a_pParent, HabitableObject::HabitableType a_NewType)
:	DisplayableObject(DisplayableObject::PLANET, a_pParent)
{
	mMyHabitableType = a_NewType;
	//
	mRelPosition.x = fRand();
	mRelPosition.y = fRand();
}

void Planet::GenerateContents()
{
	//
}

Star::Star(StarSystem* a_pParent)
:	DisplayableObject(DisplayableObject::PLANET, a_pParent)
{
	mMyHabitableType = STAR;
	//
	mRelPosition.x = 0.5f;
	mRelPosition.y = 0.5f;
}

void Star::GenerateContents()
{
	//
}
