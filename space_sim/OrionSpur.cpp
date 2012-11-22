#include "OrionSpur.hpp"
#include "StellarGroup.hpp"

#include <SFGUI\Button.hpp>
#include <SFGUI\Image.hpp>
//#include <SFGUI\Widget.hpp>

#include "SFGManager.hpp"

#include "Defines_Math.h"

//as the spur cross-section covered is forced at 3500ly by 3500ly, we can assume these approximate quantities for the number of stellar groups
#define MIN_NUM_STELLARGROUPS 5//70
#define MAX_NUM_STELLARGROUPS 15//140

#define STELLARGROUP_DIM 12

//static std::vector<StellarGroup*> StellarGroups;
//static std::vector<sfg::Widget::Ptr> StellarGroupButtons;

OrionSpur::OrionSpur()
:	DisplayableObject(DisplayableObject::ORIONSPUR, NULL)
{
	//
}

OrionSpur::~OrionSpur()
{
	//clear out stellar groups
	for(auto it = mContents.begin(); it != mContents.end(); it)
	{
		StellarGroup* pCurStellarGroup = (StellarGroup*)*it;
		delete pCurStellarGroup;
		it = mContents.erase(it);
	}
	
	//clear out stellar group buttons
	for(auto it = mContentsButtons.begin(); it != mContentsButtons.end(); it)
	{
		ClearWidget(*it);
		it = mContentsButtons.erase(it);
	}
}

void OrionSpur::GenerateContents()
{
	//we have to pre-generate all the stellar groups, so that they can be displayed on the orion spur viewscreen
	int numStellarGroups = iRand(MIN_NUM_STELLARGROUPS, MAX_NUM_STELLARGROUPS);
	/*
	#pragma omp for
      for (i=nStart; i<=nEnd; ++i) {
            #pragma omp atomic
            nSum += i;
      }
	  */
	#pragma omp for
	for(int curGroupNum = 1; curGroupNum < numStellarGroups; ++curGroupNum)
	{
		#pragma omp atomic
		//they each handle their own construction
		mContents.push_back(new StellarGroup(this));
	}

	//create the local stellar group
	mContents.push_back(new StellarGroup(this, true));
	
	mGeneratedContents = true;
}
