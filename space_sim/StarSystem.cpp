#include "StarSystem.hpp"

#include "GameManager.hpp"
#include "SFGManager.hpp"
#include "StellarGroup.hpp"

#include "Defines_Math.h"
#include "AsteroidBelt.hpp"
#include "Planet.hpp"

StarSystem::StarSystem(StellarGroup* a_pParent, bool a_IsHomeSystem)
:	DisplayableObject(DisplayableObject::STARSYSTEM, a_pParent)
,	mIsNebula(false)
//,	mAsteroidBelt(*new AsteroidBelt())
{
	if(a_IsHomeSystem)
	{
		//create the starting planet
		mContents.push_back(new Planet(this, HabitableObject::PLANET_GAIAN));
		GameManager::SetHomePlanet((Planet*)mContents.back());

		//create this system's planets
		GenerateContents();
		HideContents();

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

#define PLANET_DIM 12

void StarSystem::GenerateContents()
{
	int numPlanets = iRand(20);
	for(int curPlanetNum = 0; curPlanetNum < numPlanets; ++curPlanetNum)
	{
		//create random planet type
		Planet* pCurPlanet = new Planet(this, (HabitableObject::HabitableType)iRand((int)HabitableObject::PLANET_TERRAN, (int)HabitableObject::PLANET_GASGIANT));
		mContents.push_back(pCurPlanet); 
	}
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	windowDims.x *= 5.f/6.f;
	windowDims.x -= PLANET_DIM;
	windowDims.y *= 5.f/6.f;
	windowDims.y -= PLANET_DIM;
	for(auto it = mContents.begin(); it != mContents.end(); ++it)
	{
		StarSystem* pStarSystem = (StarSystem*)*it;
		sf::Vector2f relPos = pStarSystem->GetRelPosition();
		sfg::Button::Ptr pButton = sfg::Button::Create("");
		pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)pStarSystem);
		
		sf::Image* pSFImage = new sf::Image();
		pSFImage->loadFromFile("../media/planet.png");
		sfg::Image::Ptr pSFGImage = sfg::Image::Create(*pSFImage);
		pSFGImage->SetImage(*pSFImage);
		pButton->SetImage(pSFGImage);

		sf::FloatRect allocation;
		allocation.top = windowDims.y * relPos.y;
		allocation.height = PLANET_DIM;
		allocation.left = windowDims.x * relPos.x;
		allocation.width = PLANET_DIM;
		pButton->SetAllocation(allocation);
		//
		mContentsButtons.push_back(pButton);
		AddWidget(pButton);
	}

	//create the star
	mContents.push_back(new Star(this));
	sfg::Button::Ptr pButton = sfg::Button::Create("");
	pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)mContents.back());
		
	sf::Image* pSFImage = new sf::Image();
	pSFImage->loadFromFile("../media/star.png");
	sfg::Image::Ptr pSFGImage = sfg::Image::Create(*pSFImage);
	pSFGImage->SetImage(*pSFImage);
	pButton->SetImage(pSFGImage);

	sf::FloatRect allocation;
	allocation.top = windowDims.y * 0.5f;
	allocation.height = PLANET_DIM;
	allocation.left = windowDims.x * 0.5f;
	allocation.width = PLANET_DIM;
	pButton->SetAllocation(allocation);
	//
	mContentsButtons.push_back(pButton);
	AddWidget(pButton);

	//
	mGeneratedContents = true;
}

void StarSystem::DisplayContents()
{
	if(!mGeneratedContents)
		GenerateContents();
	//
	DisplayableObject::DisplayContents();
}
