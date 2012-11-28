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
	//
,	mPopulation(0)
,	mObjectMass(0)
,	mAtmosDensity(0)
,	mObjectDiameter(0)
,	mObjName("default name")
,	mCalculatedResourceSpace(0)
,	m_TotalInfrastructureLevel(0)
,	mStoredSoilForFarming(0)
,	mQSoilForFarming(0)
,	mTargetFoodProduction(0)
,	mUsedStorageSpace(0)
	//
,	m_tLeftMainUpdate(1)
,	m_NumLeftDailyUpdate(HOURS_DAY)
,	m_NumLeftWeeklyUpdate(DAYS_WEEK)
,	m_NumLeftMonthlyUpdate(WEEKS_MONTH)
,	m_NumLeftYearlyUpdate(MONTHS_YEAR)
,	mLastUpgradeSuccessful(false)
	//
,	mCriticalGrowthTarget(0)
,	mGrowthTarget(0)
,	mTargetStorageSpace(0)
,	mLastCriticalUpgrade(Infrastructure::MAXVAL)
,	mLastUtilUpgrade(Infrastructure::MAXVAL)
	//
,	m_UnallocatedPersonnel(0)
,	m_ConstructionAllocatedPersonnel(0)
,	mTotalWorkersNeeded(0)
{
	//initialise std::maps
	for(int ind = 0; ind < Resource::MAXVAL; ++ind)
	{
		m_PlanetResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		m_PlanetResAbundance.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		//
		m_StoredResNum.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		m_StoredResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
	}
	for(int ind = 0; ind < Infrastructure::MAXVAL; ++ind)
	{
		mInfrastructureLevel.insert(std::pair<Infrastructure::InfrastructureType, float>(Infrastructure::InfrastructureType(ind), 0.f));
		m_InfrastructureAllocatedPersonnel.insert(std::pair<Infrastructure::InfrastructureType, int>(Infrastructure::InfrastructureType(ind), 0));
	}

	//----- testing values - delete these later

	//mInfrastructureLevel[Infrastructure::POWER_GENERATION] = 1.f;
	//mInfrastructureLevel[Infrastructure::WASTE_RECYCLING] = 1.f;
	//mInfrastructureLevel[Infrastructure::SCRAP_RECYCLING] = 1.f;
	//mInfrastructureLevel[Infrastructure::STORAGE] = 1.f;
	//mCalculatedResourceSpace = mInfrastructureLevel[Infrastructure::STORAGE] * SPACE_PER_STORAGE;
	
	m_StoredResNum[Resource::FOOD] = 100000;
	m_StoredResQ[Resource::FOOD] = 0.5f;
	m_StoredResNum[Resource::WATER] = 100000;
	m_StoredResQ[Resource::WATER] = 0.5f;
	m_StoredResNum[Resource::FUEL] = 10000;
	m_StoredResQ[Resource::FUEL] = 0.5f;
	m_StoredResNum[Resource::COMPONENTS] = 1000;
	m_StoredResQ[Resource::COMPONENTS] = 0.5f;
	m_StoredResNum[Resource::CIRCUITRY] = 1000;
	m_StoredResQ[Resource::CIRCUITRY] = 0.5f;
	m_StoredResNum[Resource::SHEETMETAL] = 1000;
	m_StoredResQ[Resource::SHEETMETAL] = 0.5f;
	m_StoredResNum[Resource::GIRDERS] = 1000;
	m_StoredResQ[Resource::GIRDERS] = 0.5f;
	//
	mPopulation = 100;
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

float HabitableObject::GetPlanetResNum(Resource::ResourceType a_ResType)
{
	return m_PlanetResAbundance[a_ResType];
}

float HabitableObject::GetPlanetResQ(Resource::ResourceType a_ResType)
{
	return m_PlanetResQ[a_ResType];
}

float HabitableObject::GetStoredResNum(Resource::ResourceType a_ResType)
{
	return m_StoredResNum[a_ResType];
}

float HabitableObject::GetStoredResQ(Resource::ResourceType a_ResType)
{
	return m_StoredResQ[a_ResType];
}

std::string HabitableObject::GetName()
{
	return mObjName;
}

std::string HabitableObject::GetCoordsString()
{
	return num2string( round(mRelPosition.x - 0.5f, 2) ) + ", " + num2string( round(mRelPosition.y - 0.5f, 2) );
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

void HabitableObject::RecalculateInfrastructureLevel()
{
	m_TotalInfrastructureLevel = 0;
	for(int ind = 0; ind < Infrastructure::MAXVAL; ++ind)
	{
		m_TotalInfrastructureLevel += mInfrastructureLevel[Infrastructure::InfrastructureType(ind)];
	}
}

float HabitableObject::GetInfrastructureLevel()
{
	return m_TotalInfrastructureLevel;
}

void HabitableObject::RecalculateStorageNeeded()
{
	RecalculateUsedStorage();
	//
	mTargetStorageSpace = mUsedStorageSpace;
	float expectedProduction = 0;

	expectedProduction += mInfrastructureLevel[Infrastructure::MINING] * DAYS_WEEK * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::FUEL_PROCESSING] * FUEL_PRODUCTION_MULTI * DAYS_WEEK * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::WATER_PURIFICATION] * WATER_PRODUCTION_MULTI * DAYS_WEEK * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::GAS_PROCESSING] * DAYS_WEEK * WEEKS_MONTH;
		
	expectedProduction += mInfrastructureLevel[Infrastructure::WASTE_RECYCLING] * DAYS_WEEK * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::SCRAP_RECYCLING] * DAYS_WEEK * WEEKS_MONTH;
		
	expectedProduction += mInfrastructureLevel[Infrastructure::ELECTRONICS_PRODUCTION] * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::MATERIALS_PRODUCTION] * WEEKS_MONTH;
	expectedProduction += mInfrastructureLevel[Infrastructure::DOMESTICGOODS_PRODUCTION] * WEEKS_MONTH;
	
	expectedProduction += mTargetFoodProduction * FOOD_PRODUCTION_MULTI;
	//expectedProduction += mInfrastructureLevel[Infrastructure::MACHINERY_PRODUCTION];
	expectedProduction += mInfrastructureLevel[Infrastructure::LUXURYGOODS_PRODUCTION];

	expectedProduction *= MONTHS_YEAR;
	mTargetStorageSpace += expectedProduction;

	mTargetStorageSpace /= SPACE_PER_STORAGE;
}

void HabitableObject::RecalculateTargetFoodProduction()
{
	//work out how much food we need to produce a month to feed everyone, with room to spare
	mTargetFoodProduction = (mPopulation * FOOD_PERPERSON_PERDAY * (1 + CRITICAL_SAFETY_MARGIN) * DAYS_WEEK * WEEKS_MONTH) / FOOD_PRODUCTION_MULTI;
}

void HabitableObject::RecalculateUsedStorage()
{
	mUsedStorageSpace = 0;
	for(auto it = m_StoredResNum.begin(); it != m_StoredResNum.end(); ++it)
	{
		mUsedStorageSpace += it->second;
	}
}

void HabitableObject::RemoveResources(Resource::ResourceType a_NewType, float a_Quantity)
{
	if(a_Quantity > m_StoredResNum[a_NewType])
		a_Quantity = m_StoredResNum[a_NewType];
	m_StoredResNum[a_NewType] -= a_Quantity;
	//
	RecalculateUsedStorage();
}

void HabitableObject::AddResources(Resource::ResourceType a_NewType, float a_Quality, float a_Quantity)
{
	if(mUsedStorageSpace + a_Quantity > mCalculatedResourceSpace)
	{
		//std::cout << "Dumping " << m_StoredResNum[Resource::ORGANICWASTE] + m_StoredResNum[Resource::SCRAPWASTE] << " of accumulated waste!" << std::endl;
		RemoveResources(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE]);
		RemoveResources(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE]);
	}

	if(mUsedStorageSpace + a_Quantity <= mCalculatedResourceSpace)
	{
		//add it to the 'pile
	}
	else
	{
		//not enough room, have to dump something
		//std::cout << "	Short of " << mUsedStorageSpace + a_Quantity - mCalculatedResourceSpace << " storage space!" << std::endl;
		a_Quantity = mCalculatedResourceSpace - mUsedStorageSpace;
		if(a_Quantity < 0)
			a_Quantity = 0;
	}

	//just add it for now
	m_StoredResQ[a_NewType] = AverageWeight(m_StoredResQ[a_NewType], m_StoredResNum[a_NewType], a_Quality, a_Quantity);
	m_StoredResNum[a_NewType] += a_Quantity;

	RecalculateUsedStorage();
}

float HabitableObject::GetInfrastructureLevel(Infrastructure::InfrastructureType a_InfType)
{
	return mInfrastructureLevel[a_InfType];
}

float HabitableObject::GetUsedStorageSpace()
{
	return mUsedStorageSpace;
}

float HabitableObject::GetMonthlyFuelUsage()
{
	return m_TotalInfrastructureLevel * POWERUSE_PER_INF * POWER_FUEL_CONSUMPTION * DAYS_WEEK * WEEKS_MONTH;
}

float HabitableObject::GetMonthlyOxyUsage()
{
	return mPopulation * OXY_PERPERSON_PERDAY * DAYS_WEEK * WEEKS_MONTH;
}

int HabitableObject::GetNumJobs()
{
	return mTotalWorkersNeeded;
}

float HabitableObject::GetYearlyProduction()
{
	//todo
	return 0.f;
}

float HabitableObject::GetSoilQ()
{
	return mQSoilForFarming;
}

float HabitableObject::GetSoilAmount()
{
	return mStoredSoilForFarming;
}
