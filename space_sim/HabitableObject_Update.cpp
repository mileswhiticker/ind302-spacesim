#include "HabitableObject.hpp"

#include "GameManager.hpp"

#include "Resources.hpp"
#include "MathHelpers.h"

void HabitableObject::Update(float a_DeltaT, TimeRate a_TimeRate)
{
	m_tLeftMainUpdate -= a_DeltaT;
	if(m_tLeftMainUpdate <= 0)
	{
		m_tLeftMainUpdate = 1;
		switch(a_TimeRate)
		{
		case(HOURLY):
			{
				HourlyUpdate(true);
				break;
			}
		case(DAILY):
			{
				DailyUpdate(true);
				break;
			}
		case(WEEKLY):
			{
				WeeklyUpdate(true);
				break;
			}
		case(MONTHLY):
			{
				MonthlyUpdate(true);
				break;
			}
		}
	}
}

void HabitableObject::HourlyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//hourly logic here

	//consume food
	{
		//food quality represents how much a person can consume to survive
		//higher quality means less food is needed
		float qMulti = 1 - m_StoredResQ[Resource::FOOD];
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float foodNeeded = (float(mPopulation) / 24.f) * qMulti * 2.f;
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
		float waterNeeded = float(mPopulation) / 24.f;
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
		//higher quality fuel means more mileage
		//higher quality fuel is consumed at a lower rate
		//for planets etc this equates to power generation, transport and the like
		float qMulti = 1 - m_StoredResQ[Resource::FUEL];
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float fuelNeeded = (float(mInfrastructure) / 24.f) * qMulti * 2.f;
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

	//produce sewage
	{
		//sewage quality is dependant on food quality
		//higher quality organic waste affects food quality
		float newWaste = float(mPopulation) / 24.f;
		m_StoredResQ[Resource::ORGANICWASTE] = AverageWeight(m_StoredResQ[Resource::ORGANICWASTE], m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::FOOD], newWaste);
		m_StoredResNum[Resource::ORGANICWASTE] += newWaste;

		if(mIsSelected)
		{
			GameManager::UpdateStoredResource(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::ORGANICWASTE]);
		}
	}

	//two-way recursion
	if(a_PropogateUpward)
	{
		if(--m_NumLeftDailyUpdate <= 0)
		{
			DailyUpdate(true);
			m_NumLeftDailyUpdate = HOURS_DAY;
		}
	}
}

void HabitableObject::DailyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//daily logic here

	//produce raw materials
	{
		//dependant on planet type, res abundance, res quality and infrastructure level
	}
	
	//two-way recursion
	if(a_PropogateUpward)
	{
		if(--m_NumLeftWeeklyUpdate <= 0)
		{
			WeeklyUpdate(true);
			m_NumLeftDailyUpdate = DAYS_WEEK;
		}
	}
	else
	{
		HourlyUpdate(false, a_Quantity * HOURS_DAY);
	}
}

void HabitableObject::WeeklyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//weekly logic here
	//produce finished foods (including food)
	
	//two-way recursion
	if(a_PropogateUpward)
	{
		if(--m_NumLeftMonthlyUpdate <= 0)
		{
			MonthlyUpdate(true);
			m_NumLeftMonthlyUpdate = WEEKS_MONTH;
		}
	}
	else
	{
		DailyUpdate(false, a_Quantity * DAYS_WEEK);
	}
}

void HabitableObject::MonthlyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//monthly logic here
	//produce ships and infrastructure here
	//maintenance on infrastructure and ships
	//sickness from sewage and water purity
	
	//two-way recursion
	if(a_PropogateUpward)
	{
		if(--m_NumLeftYearlyUpdate <= 0)
		{
			YearlyUpdate(true);
			m_NumLeftYearlyUpdate = MONTHS_YEAR;
		}
		//nothing?
	}
	else
	{
		WeeklyUpdate(false, a_Quantity * WEEKS_MONTH);
	}
}

void HabitableObject::YearlyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//yearly logic here
	//annual financial transactions (tax, salaries etc)
	
	//two-way recursion
	if(a_PropogateUpward)
	{
		//nothing?
	}
	else
	{
		MonthlyUpdate(false, a_Quantity * MONTHS_YEAR);
	}
}
