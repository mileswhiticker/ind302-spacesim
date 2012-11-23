#include "HabitableObject.hpp"

#include "GameManager.hpp"

#include "Num2StringHelper.h"
#include "MathHelpers.h"
#define NULL 0

HabitableObject::HabitableObject(HabitableType a_MyType, StarSystem* a_pStarSystem)
:	DisplayableObject(DisplayableObject::PLANET, (DisplayableObject*)a_pStarSystem)
,	mMyHabitableType(a_MyType)
,	m_pOrbitingStarSystem(NULL)
,	m_pOrbitingObject(NULL)
,	mGenerated(false)
,	mTotalIndWeighting(0)
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
,	m_NumLeftYearlyUpdate(MONTHS_YEAR)
{
	//initialise maps
	for(int ind = 0; ind < Resource::MAXVAL; ++ind)
	{
		m_PlanetResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		m_PlanetResAbundance.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		//
		m_StoredResNum.insert(std::pair<Resource::ResourceType, int>(Resource::ResourceType(ind), 0.f));
		m_StoredResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
	}
	for(int ind = 0; ind < Industry::MAXVAL; ++ind)
	{
		m_IndustryWeighting.insert(std::pair<Industry::IndustryType, float>(Industry::IndustryType(ind), 0.f));
	}
	m_IndustryWeighting[Industry::POWER_GENERATION] = 1;
	m_IndustryWeighting[Industry::WASTE_RECYCLING] = 1;
	m_IndustryWeighting[Industry::SCRAP_RECYCLING] = 1;
	m_IndustryWeighting[Industry::STORAGE] = 1;
	
	//testing
	m_StoredResNum[Resource::FOOD] = 99999;
	m_StoredResQ[Resource::FOOD] = 0.5f;
	m_StoredResNum[Resource::WATER] = 99999;
	m_StoredResQ[Resource::WATER] = 1.f;
	mPopulation = 1;
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
	return m_PlanetResAbundance[a_ResType];
}

float HabitableObject::GetResQ(Resource::ResourceType a_ResType)
{
	return m_PlanetResQ[a_ResType];
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
	if(!mGenerated)
		return;

	m_tLeftMainUpdate -= a_DeltaT;
	if(m_tLeftMainUpdate <= 0)
	{
		m_tLeftMainUpdate = 1;
		switch(a_TimeRate)
		{
		case(HOURLY):
			{
				HourlyUpdate(UPWARD | DOWNWARD);
				break;
			}
		case(DAILY):
			{
				DailyUpdate(UPWARD | DOWNWARD);
				break;
			}
		case(WEEKLY):
			{
				WeeklyUpdate(UPWARD | DOWNWARD);
				break;
			}
		case(MONTHLY):
			{
				MonthlyUpdate(UPWARD | DOWNWARD);
				break;
			}
		}
	}
}

void HabitableObject::RecalculateIndustryWeighting()
{
	for(int ind = 0; ind < Industry::MAXVAL; ++ind)
	{
		mTotalIndWeighting += m_IndustryWeighting[Industry::IndustryType(ind)];
	}
}

float HabitableObject::GetInfrastructureLevel()
{
	return mInfrastructure;
}
