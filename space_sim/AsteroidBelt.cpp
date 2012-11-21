#include "AsteroidBelt.hpp"

#include "StarSystem.hpp"

AsteroidBelt::AsteroidBelt(StarSystem* a_pParent)
:	DisplayableObject(DisplayableObject::ASTEROIDBELT, a_pParent)
{
	mMyHabitableType = ASTEROID_BELT;
}

AsteroidBelt::~AsteroidBelt()
{
	//
}

void AsteroidBelt::GenerateContents()
{
	//
}
