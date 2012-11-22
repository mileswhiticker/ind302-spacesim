#include "HabitableObject.hpp"

#include "GameManager.hpp"

#include "Num2StringHelper.h"
#include "Defines_Math.h"
#define NULL 0

HabitableObject::HabitableObject(HabitableType a_MyType, StarSystem* a_pStarSystem)
:	DisplayableObject(DisplayableObject::PLANET, (DisplayableObject*)a_pStarSystem)
,	mMyHabitableType(a_MyType)
,	m_pOrbitingStarSystem(NULL)
,	m_pOrbitingObject(NULL)
	//
,	mPopulation(0)
,	mObjectMass(0)
,	mAtmosDensity(0)
,	mObjectDiameter(0)
,	mObjName("default name")
,	mCalculatedResourceSpace(0)
,	mInfrastructure(0)
	//
,	m_tLeftMainUpdate(1)
,	m_NumLeftDailyUpdate(HOURS_DAY)
,	m_NumLeftWeeklyUpdate(DAYS_WEEK)
,	m_NumLeftMonthlyUpdate(WEEKS_MONTH)
{
	//m_pObjName = new std::string("default name");
	for(int ind = 0; ind < Resource::MAXVAL; ++ind)
	{
		m_ResourceQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		m_ResourceNum.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
	}
}

void HabitableObject::GenerateData()
{
	switch(mMyHabitableType)
	{
	case(PLANET_DEAD):
		{
			m_ResourceNum[Resource::HYDROCARBON] = fRand() * 0.25f;
			m_ResourceQ[Resource::HYDROCARBON] = fRand();
			mAtmosDensity = 0.5f + fRand();
			//
			m_ResourceNum[Resource::SILICACEOUS] = fRand();
			m_ResourceQ[Resource::SILICACEOUS] = fRand();
			m_ResourceNum[Resource::SILICACEOUS] = fRand();
			m_ResourceQ[Resource::SILICACEOUS] = fRand();
			m_ResourceNum[Resource::METALLIC] = fRand();
			m_ResourceQ[Resource::METALLIC] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_TERRAN):
		{
			m_ResourceNum[Resource::HYDROCARBON] = 0.5f + fRand() * 0.5f;
			m_ResourceQ[Resource::HYDROCARBON] = 0.25f + fRand() * 0.75f;
			mAtmosDensity = 0.75f + fRand() * 0.5f;
			//
			m_ResourceNum[Resource::SILICACEOUS] = fRand();
			m_ResourceQ[Resource::SILICACEOUS] = fRand();
			m_ResourceNum[Resource::CARBONACEOUS] = fRand();
			m_ResourceQ[Resource::CARBONACEOUS] = fRand();
			m_ResourceNum[Resource::METALLIC] = fRand();
			m_ResourceQ[Resource::METALLIC] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_ICE):
		{
			m_ResourceNum[Resource::HYDROCARBON] = 0.5f + fRand() * 0.5f;
			m_ResourceQ[Resource::HYDROCARBON] = 0.25f + fRand() * 0.75f;
			mAtmosDensity = 5 + fRand() * 10.f;
			//
			m_ResourceNum[Resource::SILICACEOUS] = 0.25f * fRand();
			m_ResourceQ[Resource::SILICACEOUS] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_GASGIANT):
		{
			mAtmosDensity = 500 + fRand() * 500.f;
			//
			mObjectDiameter = fRand(100000,1000000);
			break;
		}
	case(ASTEROID_CARBONACEOUS):
		{
			m_ResourceNum[Resource::SILICACEOUS] = 0.25f * fRand();
			m_ResourceQ[Resource::SILICACEOUS] = 0.25f * fRand();
			m_ResourceNum[Resource::CARBONACEOUS] = 0.5f + 0.5f * fRand();
			m_ResourceQ[Resource::CARBONACEOUS] = 0.5f + 0.5f * fRand();
			m_ResourceNum[Resource::METALLIC] = 0.25f * fRand();
			m_ResourceQ[Resource::METALLIC] = 0.25f * fRand();
			//
			mObjectDiameter = fRand(1,100);
			mObjectMass = fRand(1,100);
			break;
		}
	case(ASTEROID_SILICACEOUS):
		{
			m_ResourceNum[Resource::SILICACEOUS] = 0.5f + 0.5f * fRand();
			m_ResourceQ[Resource::SILICACEOUS] = 0.5f + 0.5f * fRand();
			m_ResourceNum[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_ResourceQ[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_ResourceNum[Resource::METALLIC] = 0.25f * fRand();
			m_ResourceQ[Resource::METALLIC] = 0.25f * fRand();
			//
			mObjectDiameter = fRand(1,100);
			mObjectMass = fRand(1,100);
			break;
		}
	case(ASTEROID_METALLIC):
		{
			m_ResourceNum[Resource::SILICACEOUS] = 0.25f * fRand();
			m_ResourceQ[Resource::SILICACEOUS] = 0.25f * fRand();
			m_ResourceNum[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_ResourceQ[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_ResourceNum[Resource::METALLIC] = 0.5f + 0.5f * fRand();
			m_ResourceQ[Resource::METALLIC] = 0.5f + 0.5f * fRand();
			//
			mObjectDiameter = fRand(1,100);
			mObjectMass = fRand(1,100);
			break;
		}
	}
}

HabitableObject::~HabitableObject()
{
	//
}

StarSystem* HabitableObject::GetOrbitingStarSystem()
{
	return m_pOrbitingStarSystem;
}

HabitableObject* HabitableObject::GetOrbitingObject()
{
	return m_pOrbitingObject;
}

HabitableObject::HabitableType HabitableObject::GetHabitableType()
{
	return mMyHabitableType;
}

float HabitableObject::ObjectMass()
{
	return mObjectMass;
}

int HabitableObject::Population()
{
	return mPopulation;
}

float HabitableObject::Diameter()
{
	return mObjectDiameter;
}

float HabitableObject::AtmosDensity()
{
	return mAtmosDensity;
}

float HabitableObject::GetResNum(Resource::ResourceType a_ResType)
{
	return m_ResourceNum[a_ResType];
}

float HabitableObject::GetResQ(Resource::ResourceType a_ResType)
{
	return m_ResourceQ[a_ResType];
}

std::string HabitableObject::GetName()
{
	return mObjName;
}

std::string HabitableObject::GetCoordsString()
{
	return num2string(mRelPosition.x - 0.5f) + "," + num2string(mRelPosition.y - 0.5f);
}

void HabitableObject::OnClick()
{
	//std::cout << "DisplayableObject::OnClick()" << std::endl;
	GameManager::GetSingleton().ClickHabitableObject(this);
}

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
	//consume food, water, fuel

	if(a_PropogateUpward)
	{
		if(--m_NumLeftDailyUpdate <= 0)
		{
			DailyUpdate(true);
			m_NumLeftDailyUpdate = HOURS_DAY;
		}
	}
	else
	{
		//nothing?
	}
}

void HabitableObject::DailyUpdate(bool a_PropogateUpward, int a_Quantity)
{
	//daily logic here
	//produce raw materials

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
	//todo

	if(a_PropogateUpward)
	{
		//nothing?
	}
	else
	{
		WeeklyUpdate(false, a_Quantity * WEEKS_MONTH);
	}
}
