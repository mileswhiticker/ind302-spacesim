#include "OrionSpur.hpp"
#include "StellarGroup.hpp"

#include "Defines_Math.h"

//as the spur cross-section covered is forced at 3500ly by 3500ly, we can assume these approximate quantities for the number of stellar groups
#define MIN_NUM_STELLARGROUPS 90
#define MAX_NUM_STELLARGROUPS 175

static std::vector<StellarGroup*> mStellarGroups;

bool OrionSpur::Generate()
{
	//return false if we've already genned everything
	if(mStellarGroups.size())
		return false;

	//we have to pre-generate all the stellar groups, so that they can be displayed on the orion spur viewscreen
	int numStellarGroups = iRand(MIN_NUM_STELLARGROUPS, MAX_NUM_STELLARGROUPS);
	for(int curGroupNum = 0; curGroupNum < numStellarGroups; ++curGroupNum)
	{
		//they each handle their own construction
		mStellarGroups.push_back(new StellarGroup());
	}

	//create the local stellar group
	mStellarGroups.push_back(new StellarGroup(true));

	return true;
}

bool OrionSpur::Clear()
{
	//return false if we've already cleared everything
	if(!mStellarGroups.size())
		return false;

	//clear out stellar groups
	for(auto it = mStellarGroups.begin(); it != mStellarGroups.end(); ++it)
	{
		StellarGroup* pCurStellarGroup = (StellarGroup*)*it;
		delete pCurStellarGroup;
		it = mStellarGroups.erase(it);
	}

	return true;
}
