#include "StarSystem.hpp"

#include "GameManager.hpp"

#include "Defines_Math.h"
#include "AsteroidBelt.hpp"
#include "Planet.hpp"

StarSystem::StarSystem(StellarGroup* a_pOwningGroup, bool a_IsHomeSystem)
:	mIsNebula(false)
,	mAsteroidBelt(*new AsteroidBelt())
,	mRelPosition(sf::Vector2f())
,	m_pOwningGroup(a_pOwningGroup)
{
	if(a_IsHomeSystem)
	{
		//create this system's planets
		Generate();

		//create the starting planet
		mHabitableObjects.push_back(new Planet(HabitableObject::PLANET_GAIAN, this));
		GameManager::SetHomePlanet((Planet*)mHabitableObjects.back());

		//we're at the center of the entire playable area
		mRelPosition.x = 0.5f;
		mRelPosition.y = 0.5f;
	}
	else
	{
		//5% chance of being a nebula
		mIsNebula = iRand() > 95 ? true : false;

		//calculate a random position for this group in the stellar group
		//calculate random coords with an even distribution across the internal volume of a sphere
		float phi = fRand() * PI;
		float costheta = fRand() * 2 - 1;
		float u = fRand();

		float theta = acos( costheta );
		float R = 1.f;		//distribution radius - just use 0-1 for easy distribution across screen space
		float r = R * curt( u );

		//as we're treating everything as 2D for now, just drop the zPos
		mRelPosition.x = r * sin( theta) * cos( phi );
		mRelPosition.y = r * sin( theta) * sin( phi );
		//mRelPosition.z = r * cos( theta );
	}
}

StarSystem::~StarSystem()
{
	for(auto it = mHabitableObjects.begin(); it != mHabitableObjects.end(); ++it)
	{
		HabitableObject* pCurHabitableObject = (HabitableObject*)*it;
		delete pCurHabitableObject;
		it = mHabitableObjects.erase(it);
	}

	delete &mAsteroidBelt;
}

void StarSystem::Generate()
{
	int numPlanets = iRand(20);
	for(int curPlanetNum = 0; curPlanetNum < numPlanets; ++curPlanetNum)
	{
		//create random planet type
		Planet* pCurPlanet = new Planet((HabitableObject::type)iRand((int)HabitableObject::PLANET_TERRAN, (int)HabitableObject::PLANET_GASGIANT), this);
		mHabitableObjects.push_back(pCurPlanet); 
	}
}
