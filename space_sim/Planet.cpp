#include "Planet.hpp"

Planet::Planet(HabitableObject::HabitableType a_NewType, StarSystem* a_pOrbitingStarSystem)
{
	mMyHabitableType = a_NewType;
	m_pOrbitingStarSystem = a_pOrbitingStarSystem;
}

Planet::~Planet()
{
	//
}
