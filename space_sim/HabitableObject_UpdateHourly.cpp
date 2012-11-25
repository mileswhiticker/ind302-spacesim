#include "HabitableObject.hpp"

#include "GameManager.hpp"

#include "Scene_Game.hpp"
#include "Resources.h"
#include "MathHelpers.h"

void HabitableObject::HourlyUpdate(int a_PropogationDir, int a_Quantity)
{
	//hourly logic here

	//consume food
	{
		//food quality represents how much a person can consume to survive
		//higher quality means less food is needed
		float qMulti = (1 - m_StoredResQ[Resource::FOOD]) * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float foodNeeded = ((FOOD_PERPERSON_PERDAY * float(mPopulation)) / HOURS_DAY) * qMulti * a_Quantity;
		//
		if(m_StoredResNum[Resource::FOOD] < foodNeeded)
		{
			//some people starve to death
			std::cout << int(float(mPopulation) * m_StoredResNum[Resource::FOOD] / foodNeeded) << " died of starvation!" << std::endl;
			mPopulation = int(float(mPopulation) *m_StoredResNum[Resource::FOOD] / foodNeeded);
			foodNeeded = m_StoredResNum[Resource::FOOD];
		}
		//m_StoredResNum[Resource::FOOD] -= foodNeeded;
		RemoveResources(Resource::FOOD, foodNeeded);
		
		if(mIsSelected)
		{
			GameManager::UpdateDisplayedResStore(Resource::FOOD, m_StoredResNum[Resource::FOOD], m_StoredResQ[Resource::FOOD]);
			//GameManager::GetSingleton().GetGameScene()->SetPop(mPopulation);
		}
	}

	//consume water
	{
		//water quality represents purity
		//low quality means a few people may die of sickness
		float waterNeeded = (float(a_Quantity) * WATER_PERPERSON_PERDAY * float(mPopulation)) / HOURS_DAY;
		if(m_StoredResNum[Resource::WATER] < waterNeeded)
		{
			//some people die of thirst
			std::cout << mPopulation - int(mPopulation * m_StoredResNum[Resource::WATER] / waterNeeded) << " people died of thirst!" << std::endl;
			mPopulation = int(mPopulation * m_StoredResNum[Resource::WATER] / waterNeeded);
			waterNeeded = m_StoredResNum[Resource::WATER];
		}
		//m_StoredResNum[Resource::WATER] -= waterNeeded;
		RemoveResources(Resource::WATER, waterNeeded);
		
		if(mIsSelected)
		{
			GameManager::UpdateDisplayedResStore(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
			//GameManager::GetSingleton().GetGameScene()->SetPop(mPopulation);
		}
	}

	//consume fuel
	{
		//higher quality fuel is consumed at a lower rate
		float qMulti = (1 - m_StoredResQ[Resource::FUEL]) * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float fuelNeeded = mInfrastructureLevel[Infrastructure::POWER_GENERATION] * POWERUSE_PER_INF * POWER_FUEL_CONSUMPTION * qMulti * a_Quantity;
		if(m_StoredResNum[Resource::FUEL] < fuelNeeded)
		{
			//todo: running out of fuel (industry shuts down)
			float missingFuel = fuelNeeded - m_StoredResNum[Resource::FUEL];
			std::cout << missingFuel << " units of fuel short!" << std::endl;
			fuelNeeded = m_StoredResNum[Resource::FUEL];
		}

		//m_StoredResNum[Resource::FUEL] -= fuelNeeded;
		RemoveResources(Resource::FUEL, fuelNeeded);
		
		if(mIsSelected)
		{
			GameManager::UpdateDisplayedResStore(Resource::FUEL, m_StoredResNum[Resource::FUEL], m_StoredResQ[Resource::FUEL]);
		}
	}

	//consume oxygen
	{
		//higher quality oxygen is consumed at a lower rate
		float qMulti = 1 - m_StoredResQ[Resource::OXYGEN] * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float oxyNeeded = mInfrastructureLevel[Infrastructure::ATMOSPHERICS] * qMulti * a_Quantity;
		if(m_StoredResNum[Resource::OXYGEN] < oxyNeeded)
		{
			//todo: running out of oxygen (people die)
			float missingOxy = oxyNeeded - m_StoredResNum[Resource::OXYGEN];
			std::cout << missingOxy << " units of oxygen short!" << std::endl;
			oxyNeeded = m_StoredResNum[Resource::OXYGEN];
		}
		//m_StoredResNum[Resource::OXYGEN] -= oxyNeeded;
		RemoveResources(Resource::OXYGEN, oxyNeeded);
		
		if(mIsSelected)
		{
			GameManager::UpdateDisplayedResStore(Resource::OXYGEN, m_StoredResNum[Resource::OXYGEN], m_StoredResQ[Resource::OXYGEN]);
		}
	}

	//produce sewage
	{
		//sewage quality is dependant on food quality
		//higher quality organic waste affects food quality
		float newWaste = (float(mPopulation) / 24.f) * a_Quantity;
		if(newWaste > 0)
		{
			//m_StoredResQ[Resource::ORGANICWASTE] = AverageWeight(m_StoredResQ[Resource::ORGANICWASTE], m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::FOOD], newWaste);
			//m_StoredResNum[Resource::ORGANICWASTE] += newWaste;
			AddResources(Resource::ORGANICWASTE, m_StoredResQ[Resource::FOOD], newWaste);
			
			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::ORGANICWASTE]);
			}
		}
	}

	//two-way recursion
	if(a_PropogationDir & UPWARD)
	{
		if(--m_NumLeftDailyUpdate <= 0)
		{
			DailyUpdate(UPWARD);
			m_NumLeftDailyUpdate = HOURS_DAY;
		}
	}
	//can not go any lower than this
}
