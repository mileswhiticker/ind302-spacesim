#include "GameManager.hpp"

#include "StellarGroup.hpp"
#include "OrionSpur.hpp"
#include "Planet.hpp"
#include "StarSystem.hpp"
#include "Traders.hpp"

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
,	m_pCurSelectedDispObject(NULL)
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
	GameManager::GetSingleton().AddHabitableObject(a_pNewHomePlanet);
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

	RecalculateAveragePrices();
	
	for(int index = 0; index < 10; ++index)
	{
		m_Traders.push_back(new Trader(m_pHomePlanet));
		m_pGameScene->AddTrader(m_Traders.back());
	}
	
	if(!m_AveragePrices.size())
	{
		for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
		{
			m_AveragePrices.insert( std::pair<Resource::ResourceType, float>(Resource::ResourceType(resInd), 0.f) );
		}
	}
	
	if(!m_MaxGloballyStored.size())
	{
		for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
		{
			m_MaxGloballyStored.insert( std::pair<Resource::ResourceType, float>(Resource::ResourceType(resInd), 0.f) );
			m_MaxGlobalStorees.insert( std::pair<Resource::ResourceType, HabitableObject*>(Resource::ResourceType(resInd), (HabitableObject*)NULL) );
		}
	}
	
	if(!m_LowestGlobalPrices.size())
	{
		for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
		{
			m_LowestGlobalPrices.insert( std::pair<Resource::ResourceType, HabitableObject*>(Resource::ResourceType(resInd), (HabitableObject*)NULL) );
		}
	}
	
	if(!m_BasePrices.size())
	{
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::CARBONACEOUS, 30.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::SILICACEOUS, 30.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::METALLIC, 40.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::WATERCRYSTALS, 30.f) );
		//
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::CIRCUITRY, 50.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::COMPONENTS, 50.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::SHEETMETAL, 50.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::GIRDERS, 50.f) );
		//
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::ORGANICWASTE, 10.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::SCRAPWASTE, 10.f) );
		//
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::FUEL, 35.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::WATER, 30.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::FOOD, 30.f) );
		//
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::DOMESTICGOODS, 75.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::LUXURYGOODS, 100.f) );
		//
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::OXYGEN, 30.f) );
		m_BasePrices.insert( std::pair<Resource::ResourceType, float>(Resource::HYDROGEN, 30.f) );
	}
	
	//unused
	//calculate upgrade weightings for different infrastructure types
	//deciding to upgrade critical and utility infrastructure is done using a separate system
	/*if(!DefaultIndustryWeightingPerObject.size())
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
		//DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::MACHINERY_PRODUCTION] = 1;
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::DOMESTICGOODS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_TERRAN][Infrastructure::LUXURYGOODS_PRODUCTION] = 1;
		
		//ice planets
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_ICE][Infrastructure::WATER_PURIFICATION] = 1;
		
		//dead planets
		//
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::MATERIALS_PRODUCTION] = 1;
		DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::ELECTRONICS_PRODUCTION] = 1;
		//DefaultIndustryWeightingPerObject[HabitableObject::PLANET_DEAD][Infrastructure::MACHINERY_PRODUCTION] = 1;
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
	}*/

	//unused
	/*if(!Resource::Requirements.size())
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
	}*/
	
	//ordered by priority
	if(!PersonnelAllocationWeighting.size())
	{
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::ATMOSPHERICS, 0.01f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::POWER_GENERATION, 0.1f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::STORAGE, 0.01f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::FOOD_PROCESSING, 0.01f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::WATER_PURIFICATION, 0.01f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::DOCKING, 1.f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::FUEL_PROCESSING, 1.f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::GAS_PROCESSING, 1.f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::MINING, 10.f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::WASTE_RECYCLING, 0.1f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::SCRAP_RECYCLING, 0.1f));
		//PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::DISPOSAL, 0.1f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::MATERIALS_PRODUCTION, 1.f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::ELECTRONICS_PRODUCTION, 1.f));
		//
		//PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::MACHINERY_PRODUCTION, 1.f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::DOMESTICGOODS_PRODUCTION, 1.f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::LUXURYGOODS_PRODUCTION, 1.f));
		//
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::RESIDENTIAL, 0.1f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::COMMERCIAL, 1.f));
		PersonnelAllocationWeighting.insert(IndustryWeightPair(Infrastructure::SHIP_PRODUCTION, 1.f));
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
	
	//display any traders on this level
	for(auto it = m_Traders.begin(); it != m_Traders.end(); ++it)
	{
		if((*it)->GetParentDisplayableObject() == a_pDisplayObject)
		{
			(*it)->ShowDisplayIcon();
		}
	}
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
	
	for(auto it = m_Traders.begin(); it != m_Traders.end(); ++it)
	{
		(*it)->ShowDisplayIcon(false);
	}

	m_pCurViewedObject->ShowContents(false);
}

void GameManager::UpOneLevel()
{
	DisplayableObject* pParent = m_pCurViewedObject->GetParentDisplayableObject();
	m_pCurSelectedDispObject = NULL;
	if(pParent)
	{
		ViewDisplayableObject(pParent);
	}
	else
	{
		SceneManager::GetSingleton().LaunchScene(MAIN_MENU);
	}
}

DisplayableObject* GameManager::GetCurrentlyViewedObject()
{
	return GameManager::GetSingleton().m_pCurViewedObject;
}

DisplayableObject::DisplayableType GameManager::GetCurrentlyViewedType()
{
	return GameManager::GetSingleton().m_pCurViewedObject->GetDisplayableType();
}

void GameManager::ClickDisplayableObject(DisplayableObject* a_pDisplayObject)
{
	if(m_pCurSelectedDispObject)
	{
		if(m_pCurSelectedDispObject == a_pDisplayObject)
		{
			ViewDisplayableObject(m_pCurSelectedDispObject);
			return;
		}
		m_pCurSelectedDispObject->UnselectThis();
		m_pCurSelectedDispObject = NULL;
		m_pCurSelectedHabObject = NULL;
	}
	//
	a_pDisplayObject->SelectThis();
	m_pCurSelectedDispObject = a_pDisplayObject;
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
	m_pCurSelectedHabObject = a_pHabObject;
}

Game* GameManager::GetGameScene()
{
	return m_pGameScene;
}

void GameManager::Update(float a_DeltaT)
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
					//
					RecalculateAveragePrices();
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
				//
				RecalculateAveragePrices();
			}
			while(mMonths >= MONTHS_YEAR)
			{
				mMonths -= MONTHS_YEAR;
				mYears++;
			}
			m_pGameScene->SetDate( num2string(mHours) + ":00, " + num2string(mDays) + "/" + num2string(mMonths) + "/" + num2string(mYears) );
		}

		//update colonies
		for(auto it = m_HabitableObjects.begin(); it != m_HabitableObjects.end(); ++it)
		{
			(*it)->Update(a_DeltaT, m_CurTimeRate);
		}

		//update traders
		for(auto it = m_Traders.begin(); it != m_Traders.end(); ++it)
		{
			(*it)->Update(m_CurTimeRate, a_DeltaT);
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

float GameManager::GetInfWeighting(HabitableObject::HabitableType a_MyHabType, Infrastructure::InfrastructureType a_MyInfType)
{
	return GameManager::GetSingleton().DefaultIndustryWeightingPerObject[a_MyHabType][a_MyInfType];
}

HabitableObject* GameManager::GetSelectedHabObj()
{
	return m_pCurSelectedHabObject;
}

std::vector<Planet*> GameManager::GetValidDestinations()
{
	return GameManager::GetSingleton().m_SettledPlanets;
}

void GameManager::AddSettletPlanet(Planet* a_pNewColony)
{
	GameManager::GetSingleton().m_SettledPlanets.push_back(a_pNewColony);
}

void GameManager::ShipChangeLevel(Trader* a_pTrader)
{
	//check if a_pTrader need to be displayed
	if(a_pTrader == GameManager::GetSingleton().m_pCurSelectedDispObject)
	{
		GameManager::GetSingleton().ViewDisplayableObject(a_pTrader->GetParentDisplayableObject());
	}
	else if(a_pTrader->GetParentDisplayableObject() == GameManager::GetSingleton().m_pCurViewedObject)
	{
		a_pTrader->ShowDisplayIcon();
	}
	else
	{
		a_pTrader->ShowDisplayIcon(false);
	}
}

Planet* GameManager::GetRandomTraderDestination(Trader* a_pTrader)
{
	Planet* pDestPlanet = NULL;
	while(pDestPlanet == a_pTrader->GetParentDisplayableObject() || !pDestPlanet)
	{
		std::vector<Planet*> viableChoices = GameManager::GetValidDestinations();
		if(viableChoices.size() == 1)
			break;

		int numChoices = viableChoices.size();
		if(numChoices)
		{
			int destIndex = iRand(0, numChoices);
			pDestPlanet = viableChoices[destIndex];
		}
	}

	return pDestPlanet;
}

float GameManager::GetAveragePrice(Resource::ResourceType a_ResType)
{
	return GameManager::GetSingleton().m_AveragePrices[a_ResType];
}

void GameManager::RecalculateAveragePrices()
{
	for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
	{
		m_AveragePrices[Resource::ResourceType(resInd)] = 0;
	}

	for(auto it = m_SettledPlanets.begin(); it != m_SettledPlanets.end(); ++it)
	{
		for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
		{
			Resource::ResourceType curResType = Resource::ResourceType(resInd);
			//
			m_AveragePrices[Resource::ResourceType(resInd)] += (*it)->GetResPrice(curResType);
			
			float numStored = (*it)->GetStoredResNum(curResType);
			if(m_MaxGlobalStorees[curResType] == *it)
			{
				m_MaxGloballyStored[curResType] = numStored;
			}
			else if(numStored > m_MaxGloballyStored[curResType])
			{
				m_MaxGloballyStored[curResType] = numStored;
				m_MaxGlobalStorees[curResType] = *it;
			}
		}
	}
	
	for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
	{
		m_AveragePrices[Resource::ResourceType(resInd)] /= float(m_SettledPlanets.size());
	}

	//also recalculate the lowest prices globally
	for(auto it = m_SettledPlanets.begin(); it != m_SettledPlanets.end(); ++it)
	{
		//if(!m_LowestGlobalPrices[]
	}
}

float GameManager::GetBasePrice(Resource::ResourceType a_ResType)
{
	return GameManager::GetSingleton().m_BasePrices[a_ResType];
}

float GameManager::GetMaxStoredGlobally(Resource::ResourceType a_ResType)
{
	return GameManager::GetSingleton().m_MaxGloballyStored[a_ResType];
}

/*Planet* GameManager::GetHighestPrice(Resource::ResourceType a_ResType)
{
	std::vector<Planet*>& colonies = GameManager::GetSingleton().m_SettledPlanets;
	Planet* pCurPlanet = colonies[0];
	float curHighestPrice = pCurPlanet->GetResPrice(a_ResType);
	for(auto it = colonies.begin(); it != colonies.end(); ++it)
	{
		if((*it)->GetResPrice(a_ResType) > curHighestPrice)
		{
			curHighestPrice = (*it)->GetResPrice(a_ResType);
			pCurPlanet = *it;
		}
	}

	return pCurPlanet;
}*/
