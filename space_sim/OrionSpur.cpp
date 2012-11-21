#include "OrionSpur.hpp"
#include "StellarGroup.hpp"

#include <SFGUI\Button.hpp>
#include <SFGUI\Image.hpp>
//#include <SFGUI\Widget.hpp>

#include "SFGManager.hpp"

#include "Defines_Math.h"

//as the spur cross-section covered is forced at 3500ly by 3500ly, we can assume these approximate quantities for the number of stellar groups
#define MIN_NUM_STELLARGROUPS 70
#define MAX_NUM_STELLARGROUPS 140

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
	for(int curGroupNum = 1; curGroupNum < numStellarGroups; ++curGroupNum)
	{
		//they each handle their own construction
		mContents.push_back(new StellarGroup(this));
	}

	//create the local stellar group
	mContents.push_back(new StellarGroup(this, true));
	
	//lay out the stellar groups
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	windowDims.x *= 5.f/6.f;
	windowDims.x -= STELLARGROUP_DIM;
	windowDims.y *= 5.f/6.f;
	windowDims.y -= STELLARGROUP_DIM;
	for(auto it = mContents.begin(); it != mContents.end(); ++it)
	{
		StellarGroup* pStellarGroup = (StellarGroup*)*it;
		sf::Vector2f relPos = pStellarGroup->GetRelPosition();
		sfg::Button::Ptr pButton = sfg::Button::Create("");
		pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)pStellarGroup);

		sf::Image* pSFImage = new sf::Image();
		pSFImage->loadFromFile("../media/group.png");
		sfg::Image::Ptr pSFGImage = sfg::Image::Create(*pSFImage);
		pSFGImage->SetImage(*pSFImage);
		pButton->SetImage(pSFGImage);

		sf::FloatRect allocation;
		allocation.top = windowDims.y * relPos.y;
		allocation.height = STELLARGROUP_DIM;
		allocation.left = windowDims.x * relPos.x;
		allocation.width = STELLARGROUP_DIM;
		pButton->SetAllocation(allocation);
		//
		mContentsButtons.push_back(pButton);
		AddWidget(pButton);
	}

	mGeneratedContents = true;
}

void OrionSpur::DisplayContents()
{
	if(!mGeneratedContents)
		GenerateContents();
	//
	DisplayableObject::DisplayContents();
}
