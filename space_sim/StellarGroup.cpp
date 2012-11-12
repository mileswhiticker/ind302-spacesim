#include "StellarGroup.hpp"

#include "Defines_Math.h"
#include "StarSystem.hpp"

#define MIN_STELLAR_GROUP_DIAMETER 20
#define MAX_STELLAR_GROUP_DIAMETER 40

#define MIN_STARSYSTEMS_PER_STELLARGROUP 30
#define MAX_STARSYSTEMS_PER_STELLARGROUP 100

StellarGroup::StellarGroup(bool a_IsLocalGroup)
:	mDiameter(0)
,	mNumStarSystems(0)
{
	//what's this used for?
	mDiameter = fRand(MIN_STELLAR_GROUP_DIAMETER, MAX_STELLAR_GROUP_DIAMETER);

	if(a_IsLocalGroup)
	{
		//we're right in the middle
		mRelPosition.x = 0.5f;
		mRelPosition.y = 0.5f;

		//fill out or star systems
		Generate();

		//create home system
		mStarSystems.push_back(new StarSystem(this, true));
	}
	else
	{
		//calculate a random position for this group in the orion spur cross-section
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

StellarGroup::~StellarGroup()
{
	for(auto it = mStarSystems.begin(); it != mStarSystems.end(); ++it)
	{
		StarSystem* pCurStarSystem = (StarSystem*)*it;
		delete pCurStarSystem;
		it = mStarSystems.erase(it);
	}
}

void StellarGroup::Generate()
{
	//only need to generate these as we come into range of this stellar group
	int numStarSystems = iRand(MIN_STARSYSTEMS_PER_STELLARGROUP, MAX_STARSYSTEMS_PER_STELLARGROUP);
	for(int curSystemNum = 0; curSystemNum < numStarSystems; ++curSystemNum)
	{
		//create new star system
		mStarSystems.push_back(new StarSystem(this)); 
	}
}
