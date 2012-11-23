#include "HabitableObject.hpp"

#include "GameManager.hpp"

#include "Resources.h"
#include "MathHelpers.h"

void HabitableObject::HourlyUpdate(int a_PropogationDir, int a_Quantity)
{
	//hourly logic here

	//consume food
	{
		//food quality represents how much a person can consume to survive
		//higher quality means less food is needed
		float qMulti = 1 - m_StoredResQ[Resource::FOOD] * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float foodNeeded = (float(mPopulation) / 24.f) * qMulti * a_Quantity;
		//
		if(m_StoredResNum[Resource::FOOD] < foodNeeded)
		{
			//todo: starving
			float missingFood = foodNeeded - m_StoredResNum[Resource::FOOD];
		}
		else
		{
			m_StoredResNum[Resource::FOOD] -= foodNeeded;
		}

		if(mIsSelected)
		{
			GameManager::UpdateStoredResource(Resource::FOOD, m_StoredResNum[Resource::FOOD], m_StoredResQ[Resource::FOOD]);
		}
	}

	//consume water
	{
		//water quality represents purity
		//low quality means a few people may die of sickness
		float waterNeeded = (float(mPopulation) / 24.f) * a_Quantity;
		if(m_StoredResNum[Resource::WATER] < waterNeeded)
		{
			//todo: dying of thirst
			float missingWater = waterNeeded - m_StoredResNum[Resource::WATER];
		}
		else
		{
			m_StoredResNum[Resource::WATER] -= waterNeeded;
		}

		if(mIsSelected)
		{
			GameManager::UpdateStoredResource(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
		}
	}

	//consume fuel
	{
		//higher quality fuel is consumed at a lower rate
		float qMulti = 1 - m_StoredResQ[Resource::FUEL] * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float fuelNeeded = (m_IndustryWeighting[Industry::POWER_GENERATION] * mInfrastructure) * qMulti * a_Quantity;
		if(m_StoredResNum[Resource::FUEL] < fuelNeeded)
		{
			//todo: running out of fuel (industry shuts down)
			float missingFuel = fuelNeeded - m_StoredResNum[Resource::FUEL];
		}
		else
		{
			m_StoredResNum[Resource::FUEL] -= fuelNeeded;
		}

		if(mIsSelected)
		{
			GameManager::UpdateStoredResource(Resource::FUEL, m_StoredResNum[Resource::FUEL], m_StoredResQ[Resource::FUEL]);
		}
	}

	//consume oxygen
	{
		//higher quality oxygen is consumed at a lower rate
		float qMulti = 1 - m_StoredResQ[Resource::OXYGEN] * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float oxyNeeded = (m_IndustryWeighting[Industry::ATMOSPHERICS] * mInfrastructure) * qMulti * a_Quantity;
		if(m_StoredResNum[Resource::OXYGEN] < oxyNeeded)
		{
			//todo: running out of fuel (industry shuts down)
			float missingOxy = oxyNeeded - m_StoredResNum[Resource::OXYGEN];
		}
		else
		{
			m_StoredResNum[Resource::OXYGEN] -= oxyNeeded;
		}

		if(mIsSelected)
		{
			GameManager::UpdateStoredResource(Resource::OXYGEN, m_StoredResNum[Resource::OXYGEN], m_StoredResQ[Resource::OXYGEN]);
		}
	}

	//produce sewage
	{
		//sewage quality is dependant on food quality
		//higher quality organic waste affects food quality
		float newWaste = (float(mPopulation) / 24.f) * a_Quantity;
		if(newWaste > 0)
		{
			m_StoredResQ[Resource::ORGANICWASTE] = AverageWeight(m_StoredResQ[Resource::ORGANICWASTE], m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::FOOD], newWaste);
			m_StoredResNum[Resource::ORGANICWASTE] += newWaste;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::ORGANICWASTE]);
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
