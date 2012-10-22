#include "Planet.hpp"

Planet::Planet(type a_NewType, StarSystem* a_pOrbitingStarSystem)
{
	mMyType = a_NewType;
	m_pOrbitingStarSystem = a_pOrbitingStarSystem;
}

Planet::~Planet()
{
	//
}
