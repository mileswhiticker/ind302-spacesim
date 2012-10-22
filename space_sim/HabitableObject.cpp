#include "HabitableObject.hpp"

#define NULL 0

HabitableObject::HabitableObject()
:	mPopulation(0)
,	mMyType(INVALID)
,	m_pOrbitingStarSystem(NULL)
,	m_pOrbitingObject(NULL)
{
	//
}

HabitableObject::~HabitableObject()
{
	//
}

StarSystem* HabitableObject::GetOrbitingStarSystem()
{
	return m_pOrbitingStarSystem;
}

HabitableObject* HabitableObject::GetOrbitingObject()
{
	return m_pOrbitingObject;
}
