#include "GameManager.hpp"

#include "StellarGroup.hpp"
#include "OrionSpur.hpp"
#include "Planet.hpp"
#include "StarSystem.hpp"

#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "SceneManager.hpp"

#include "MathHelpers.h"
#include "Num2StringHelper.h"
#include "GameHelpers.hpp"

#include <iostream>

static Planet* m_pHomePlanet = NULL;

GameManager::GameManager()
:	m_pCurViewedObject(NULL)
,	m_pOrionSpur(NULL)
,	m_pGameScene(NULL)
,	m_pCurSelectedObject(NULL)
	//
,	m_CurTimeRate(HOURLY)
,	mHours(0)
,	mDays(0)
,	mMonths(0)
,	mYears(2020)
,	m_tLeftTimeTick(1)
{
	//
}

void GameManager::SetHomePlanet(Planet* a_pNewHomePlanet)
{
	m_pHomePlanet = a_pNewHomePlanet;
	AddHabitableObject(a_pNewHomePlanet);
}

Planet* GameManager::GetHomePlanet()
{
	return m_pHomePlanet;
}

void GameManager::Initialise(Game* a_pGameScene)
{
	//lay out the other displayable objects
	if(!m_pSelectCircle.get())
	{
		sf::Image* pSelectImage = new sf::Image();
		pSelectImage->loadFromFile("../media/select_circle.png");
		m_pSelectCircle = sfg::Image::Create(*pSelectImage);
		m_pSelectCircle->Show(false);
		AddWidget(m_pSelectCircle);
	}
	//
	m_pOrionSpur = new OrionSpur();
	m_pGameScene = a_pGameScene;
	ViewDisplayableObject(m_pOrionSpur);
	//

	//calculate upgrade weightings for different infrastructure types
	//deciding to upgrade critical and utility infrastructure is done using a separate system
	if(!DefaultIndustryWeightingPerObject.size())
	{
		for(int habInd = 0; habInd < HabitableObject::MAXVAL; ++habInd)
		{
			DefaultIndustryWeightingPerObject.insert( std::pair<HabitableObject::HabitableType, IndustryWeightMap>(HabitableObject::HabitableType(habInd), IndustryWeightMap()) );
			for(int infInd = 0; infInd < Infrastructure::MAXVAL; ++infInd)
			{
				DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)].insert( std::pair<Infrastructure::InfrastructureType, float>(Infrastructure::InfrastructureType(infInd), 0.f) );
			}

			//default weightings for all HOs
			DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)][Infrastructure::GAS_PROCESSING] = 1;
			DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)][Infrastructure::WASTE_RECYCLING] = 1;
			DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)][Infrastructure::SCRAP_RECYCLING] = 1;
			DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)][Infrastructure::FUEL_PROCESSING] = 1;
			DefaultIndustryWeightingPerObject[HabitableObject::HabitableType(habInd)][Infrastructure::FOOD_PROCESSING] = 1;
		}
		
		//terran planets
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::WATER_PURIFICATION] = 1;
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::MATERIALS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::ELECTRONICS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::MACHINERY_PRODUCTION] = 1;
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::DOMESTICGOODS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::LUXURYGOODS_PRODUCTION] = 1;
		
		//ice planets
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_ICE][Infrastructure::WATER_PURIFICATION] = 1;
		
		//dead planets
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::MATERIALS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::ELECTRONICS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::MACHINERY_PRODUCTION] = 1;
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::DOMESTICGOODS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::LUXURYGOODS_PRODUCTION] = 1;
		
		//gas giants
		//
		
		//asteroids
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_CARBONACEOUS][Infrastructure::MINING] = 5.f;
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_CARBONACEOUS][Infrastructure::GAS_PROCESSING] = 0;
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_METALLIC][Infrastructure::MINING] = 5.f;
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_METALLIC][Infrastructure::GAS_PROCESSING] = 0;
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_SILICACEOUS][Infrastructure::MINING] = 5.f;
		DefaultIndustryWeightingPerObject[HabitableObject::ASTEROID_SILICACEOUS][Infrastructure::GAS_PROCESSING] = 0;
	}

	if(!Resource::Requirements.size())
	{
		for(Resource::ResourceType curResType = Resource::ResourceType(0); curResType < Resource::MAXVAL; curResType = Resource::ResourceType(1 + int(curResType)))
		{
			Resource::Requirements.insert( std::pair<Resource::ResourceType, std::vector<Resource::ResRequirement>>(curResType, std::vector<Resource::ResRequirement>()) );
		}
		//
		Resource::Requirements[Resource::WATER].push_back(Resource::ResRequirement(Resource::WATERCRYSTALS, 0.1f));
		Resource::Requirements[Resource::FUEL].push_back(Resource::ResRequirement(Resource::HYDROGEN, 0.1f));
		//
		Resource::Requirements[Resource::CIRCUITRY].push_back(Resource::ResRequirement(Resource::SILICACEOUS, 1.f));
		Resource::Requirements[Resource::CIRCUITRY].push_back(Resource::ResRequirement(Resource::METALLIC, 0.8f));
		Resource::Requirements[Resource::COMPONENTS].push_back(Resource::ResRequirement(Resource::SILICACEOUS, 1.f));
		Resource::Requirements[Resource::COMPONENTS].push_back(Resource::ResRequirement(Resource::METALLIC, 0.8f));
		//
		Resource::Requirements[Resource::SHEETMETAL].push_back(Resource::ResRequirement(Resource::CARBONACEOUS, 1.f));
		Resource::Requirements[Resource::SHEETMETAL].push_back(Resource::ResRequirement(Resource::METALLIC, 0.8f));
		Resource::Requirements[Resource::GIRDERS].push_back(Resource::ResRequirement(Resource::CARBONACEOUS, 1.f));
		Resource::Requirements[Resource::GIRDERS].push_back(Resource::ResRequirement(Resource::METALLIC, 0.8f));
		//
		Resource::Requirements[Resource::MACHINERY].push_back(Resource::ResRequirement(Resource::SHEETMETAL, 1.f));
		Resource::Requirements[Resource::MACHINERY].push_back(Resource::ResRequirement(Resource::GIRDERS, 1.f));
		Resource::Requirements[Resource::MACHINERY].push_back(Resource::ResRequirement(Resource::CIRCUITRY, 1.f));
		Resource::Requirements[Resource::MACHINERY].push_back(Resource::ResRequirement(Resource::COMPONENTS, 1.f));
		//
		Resource::Requirements[Resource::DOMESTICGOODS].push_back(Resource::ResRequirement(Resource::SHEETMETAL, 1.f));
		Resource::Requirements[Resource::DOMESTICGOODS].push_back(Resource::ResRequirement(Resource::GIRDERS, 1.f));
		Resource::Requirements[Resource::DOMESTICGOODS].push_back(Resource::ResRequirement(Resource::CIRCUITRY, 1.f));
		Resource::Requirements[Resource::DOMESTICGOODS].push_back(Resource::ResRequirement(Resource::COMPONENTS, 1.f));
		//
		Resource::Requirements[Resource::LUXURYGOODS].push_back(Resource::ResRequirement(Resource::SHEETMETAL, 1.f));
		Resource::Requirements[Resource::LUXURYGOODS].push_back(Resource::ResRequirement(Resource::GIRDERS, 1.f));
		Resource::Requirements[Resource::LUXURYGOODS].push_back(Resource::ResRequirement(Resource::CIRCUITRY, 1.f));
		Resource::Requirements[Resource::LUXURYGOODS].push_back(Resource::ResRequirement(Resource::COMPONENTS, 1.f));
	}
}

void GameManager::Uninitialise()
{
	//clear out gamey things
	delete m_pOrionSpur;
	m_pOrionSpur = NULL;
	m_pCurViewedObject = NULL;
	m_pGameScene = NULL;

	//ShowView(MAXVAL);
}

void GameManager::ViewDisplayableObject(DisplayableObject* a_pDisplayObject)
{
	if(!a_pDisplayObject)
	{
		std::cout << "Unable to view NULL object!" << std::endl;
		return;
	}
	
	//std::cout << "GameManager::ViewDisplayableObject()" << std::endl;
	//clear out the previous view
	ClearCurView();
	
	a_pDisplayObject->ShowContents();
	m_pCurViewedObject = a_pDisplayObject;
	//std::cout << "	" << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " displaying contents" << std::endl;
	m_pGameScene->ChangeView(m_pCurViewedObject);
	m_pSelectCircle->Show(false);
}

void GameManager::ClearCurView()
{
	if(!m_pCurViewedObject)
		return;
	//std::cout << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " hiding contents" << std::endl;
	//setup special cases here
	/*switch(m_pCurViewedObject->GetDisplayableType())
	{
	default:
		{
			m_pCurViewedObject->HideContents();
			break;
		}
	}*/
	m_pCurViewedObject->ShowContents(false);
}

void GameManager::UpOneLevel()
{
	DisplayableObject* pParent = m_pCurViewedObject->GetParent();
	if(pParent)
	{
		ViewDisplayableObject(pParent);
	}
	else
	{
		SceneManager::GetSingleton().LaunchScene(MAIN_MENU);
	}
}

DisplayableObject::DisplayableType GameManager::GetCurrentlyViewedType()
{
	return m_pCurViewedObject->GetDisplayableType();
}

void GameManager::ClickDisplayableObject(DisplayableObject* a_pDisplayObject)
{
	if(m_pCurSelectedObject)
	{
		if(m_pCurSelectedObject == a_pDisplayObject)
		{
			ViewDisplayableObject(m_pCurSelectedObject);
			return;
		}
		m_pCurSelectedObject->UnselectThis();
		m_pCurSelectedObject = NULL;
	}
	//
	a_pDisplayObject->SelectThis();
	m_pCurSelectedObject = a_pDisplayObject;
	//
	m_pSelectCircle->Show(true);
	m_pSelectCircle->SetPosition(a_pDisplayObject->GetClickableWidget()->GetAbsolutePosition());
	//
}

void GameManager::ClickHabitableObject(HabitableObject* a_pHabObject)
{
	ClickDisplayableObject((DisplayableObject*)a_pHabObject);
	//
	m_pGameScene->SelectObject(a_pHabObject);
}

Game* GameManager::GetGameScene()
{
	return m_pGameScene;
}

void GameManager::GameUpdate(float a_DeltaT)
{
	if(m_pOrionSpur)
	{
		//increase the current date
		m_tLeftTimeTick -= a_DeltaT;

		if(m_tLeftTimeTick <= 0)
		{
			m_tLeftTimeTick = 1;
			//
			switch(m_CurTimeRate)
			{
			case(HOURLY):
				{
					mHours++;
					break;
				}
			case(DAILY):
				{
					mDays++;
					break;
				}
			case(WEEKLY):
				{
					mDays += 7;
					break;
				}
			case(MONTHLY):
				{
					mMonths++;
					break;
				}
			}
			while(mHours >= HOURS_DAY)
			{
				mHours -= HOURS_DAY;
				mDays++;
			}
			while(mDays >= DAYS_WEEK * WEEKS_MONTH)
			{
				mDays -= DAYS_WEEK * WEEKS_MONTH;
				mMonths++;
			}
			while(mMonths >= MONTHS_YEAR)
			{
				mMonths -= MONTHS_YEAR;
				mYears++;
			}
			m_pGameScene->SetDate( num2string(mHours) + ":00, " + num2string(mDays) + "/" + num2string(mMonths) + "/" + num2string(mYears) );
		}

		for(auto it = m_HabitableObjects.begin(); it != m_HabitableObjects.end(); ++it)
		{
			(*it)->Update(a_DeltaT, m_CurTimeRate);
		}
	}
}

void GameManager::AddHabitableObject(HabitableObject* a_pNewHabObject)
{
	m_HabitableObjects.push_back(a_pNewHabObject);
}

void GameManager::HandleEvent(sf::Event& a_NewEvent)
{
	if(a_NewEvent.type == sf::Event::KeyPressed)
	{
		if(a_NewEvent.key.code == sf::Keyboard::Left || a_NewEvent.key.code == sf::Keyboard::Down)
		{
			if(int(m_CurTimeRate) - 1 >= PAUSED)
				m_CurTimeRate = TimeRate(int(m_CurTimeRate) - 1);
		}
		else if(a_NewEvent.key.code == sf::Keyboard::Right || a_NewEvent.key.code == sf::Keyboard::Up)
		{
			if(int(m_CurTimeRate) + 1 < int(MAXTIMEVAL))
				m_CurTimeRate = TimeRate(int(m_CurTimeRate) + 1);
		}
	}
}

void GameManager::UpdateDisplayedResStore(Resource::ResourceType a_ResType, float a_Quantity, float a_Quality)
{
	GameManager::GetSingleton().GetGameScene()->mResourceValueLabels[a_ResType]->SetText(num2string( round(a_Quantity, 2) ) + " (Q " + num2string( round(a_Quality, 2) ) + ")");
}

void GameManager::UpdateDisplayedResInf(Resource::ResourceType a_ResType, float a_InfLevel)
{
	GameManager::GetSingleton().GetGameScene()->mResourceNameLabels[a_ResType]->SetText(GetResourceStringname(a_ResType) + " (" + num2string(round(a_InfLevel, 2)) + ")");
}

void GameManager::UpdateDisplayedInf(Infrastructure::InfrastructureType a_InfType, float a_InfLevel)
{
	if(a_InfType <= Infrastructure::DISPOSAL)
	{
		GameManager::GetSingleton().GetGameScene()->mInfrastructureLabels[a_InfType]->SetText(GetInfrastructureStringname(a_InfType) + " (" + num2string(round(a_InfLevel, 2)) + ")");
	}
	else
	{
		std::cout << "Warning! Trying to set level display of a resource producing building incorrectly!" << std::endl;
	}
}

void GameManager::UpdateSelectedInfrastructure(float a_NewInf)
{
	GameManager::GetSingleton().GetGameScene()->SetInf(a_NewInf);
}

float GameManager::GetInfWeighting(HabitableObject::HabitableType a_MyHabType, Infrastructure::InfrastructureType a_MyInfType)
{
	return GameManager::GetSingleton().DefaultIndustryWeightingPerObject[a_MyHabType][a_MyInfType];
}
