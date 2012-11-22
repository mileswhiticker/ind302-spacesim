#include "StellarGroup.hpp"

#include "MathHelpers.h"

#include "OrionSpur.hpp"
#include "StarSystem.hpp"

#include "SFGManager.hpp"

#include <SFGUI\Button.hpp>
#include <SFGUI\Image.hpp>

#define MIN_STELLAR_GROUP_DIAMETER 20
#define MAX_STELLAR_GROUP_DIAMETER 40

#define MIN_STARSYSTEMS_PER_STELLARGROUP 5//30
#define MAX_STARSYSTEMS_PER_STELLARGROUP 15//100

#define STARSYSTEM_DIM 12

StellarGroup::StellarGroup(OrionSpur* a_pParent, bool a_IsLocalGroup)
:	DisplayableObject(DisplayableObject::STELLARGROUP, a_pParent)
,	mDiameter(0)
,	mNumStarSystems(0)
{
	//what's this used for?
	mDiameter = fRand(MIN_STELLAR_GROUP_DIAMETER, MAX_STELLAR_GROUP_DIAMETER);

	if(a_IsLocalGroup)
	{
		//we're right in the middle
		mRelPosition.x = 0.5f;
		mRelPosition.y = 0.5f;

		//create home system
		mContents.push_back(new StarSystem(this, true));
	}
	else
	{
		//calculate a random position for this group in the orion spur cross-section

		//just pick a random point in a square for now
		mRelPosition.x = fRand();
		mRelPosition.y = fRand();

		//calculate random coords with an even distribution across the internal volume of a sphere
		/*float phi = fRand() * PI;
		float costheta = fRand() * 2 - 1;
		float u = fRand();

		float theta = acos( costheta );
		float R = 1.f;		//distribution radius - just use 0-1 for easy distribution across screen space
		float r = R * curt( u );

		//as we're treating everything as 2D for now, just drop the zPos
		mRelPosition.x = r * sin( theta) * cos( phi );
		mRelPosition.y = r * sin( theta) * sin( phi );
		//mRelPosition.z = r * cos( theta );*/
	}

	//only need to generate these as we come into range of this stellar group
	int numStarSystems = iRand(MIN_STARSYSTEMS_PER_STELLARGROUP, MAX_STARSYSTEMS_PER_STELLARGROUP);
	for(int curSystemNum = 0; curSystemNum < numStarSystems; ++curSystemNum)
	{
		//create new star system
		mContents.push_back(new StarSystem(this));
	}
}

StellarGroup::~StellarGroup()
{
	for(auto it = mContents.begin(); it != mContents.end(); it)
	{
		StarSystem* pCurStarSystem = (StarSystem*)*it;
		delete pCurStarSystem;
		it = mContents.erase(it);
	}
}

void StellarGroup::GenerateContents()
{
	//
}
