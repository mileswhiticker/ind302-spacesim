#include "StarSystem.hpp"

#include "GameManager.hpp"
#include "SFGManager.hpp"
#include "StellarGroup.hpp"

#include "Defines_Math.h"
#include "Asteroid.hpp"
#include "Planet.hpp"

#define PLANET_DIM 12

StarSystem::StarSystem(StellarGroup* a_pParent, bool a_IsHomeSystem)
:	DisplayableObject(DisplayableObject::STARSYSTEM, a_pParent)
,	mIsNebula(false)
//,	mAsteroidBelt(*new AsteroidBelt())
{
	if(a_IsHomeSystem)
	{
		//create the starting planet
		mContents.push_back(new Planet(this, HabitableObject::PLANET_TERRAN));
		GameManager::SetHomePlanet((Planet*)mContents.back());

		//create this system's planets
		GenerateContents();
		ShowContents(false);

		//we're at the center of the entire playable area
		mRelPosition.x = 0.5f;
		mRelPosition.y = 0.5f;
	}
	else
	{
		//5% chance of being a nebula
		mIsNebula = iRand() > 95 ? true : false;
		
		mRelPosition.x = fRand();
		mRelPosition.y = fRand();

		/*
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
		*/
	}
}

StarSystem::~StarSystem()
{
	//delete &mAsteroidBelt;
}

void StarSystem::GenerateContents()
{
	int numPlanets = iRand(20);
	for(int curPlanetNum = 0; curPlanetNum < numPlanets; ++curPlanetNum)
	{
		//create random planet type
		if(fRand() < 0.001)
		{
			// 0.01%
			mContents.push_back(new Planet(this, HabitableObject::PLANET_TERRAN));
		}
		else if(fRand() < 0.199)
		{
			// 19.9%
			mContents.push_back(new Planet(this, HabitableObject::PLANET_ICE));
		}
		else if(fRand() < 0.2)
		{
			// 20%
			mContents.push_back(new Planet(this, HabitableObject::PLANET_GASGIANT));
		}
		else
		{
			// 60%
			mContents.push_back(new Planet(this, HabitableObject::PLANET_DEAD));
		}
	}
	//create the star
	mContents.push_back(new Star(this));
	//
	mGeneratedContents = true;
}
