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
	//m_pObjName = new std::string("default name");
	for(int ind = 0; ind < Resource::MAXVAL; ++ind)
	{
		m_PlanetResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		m_PlanetResAbundance.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
		//
		m_StoredResNum.insert(std::pair<Resource::ResourceType, int>(Resource::ResourceType(ind), 0));
		m_StoredResQ.insert(std::pair<Resource::ResourceType, float>(Resource::ResourceType(ind), 0.f));
	}
	
	//testing
	m_StoredResNum[Resource::FOOD] = 99999;
	m_StoredResQ[Resource::FOOD] = 0.5f;
	m_StoredResNum[Resource::WATER] = 99999;
	m_StoredResQ[Resource::WATER] = 1.f;
	mPopulation = 1;
}

void HabitableObject::GenerateData()
{
	switch(mMyHabitableType)
	{
	case(PLANET_DEAD):
		{
			m_PlanetResAbundance[Resource::HYDROCARBON] = fRand() * 0.25f;
			m_PlanetResQ[Resource::HYDROCARBON] = fRand();
			mAtmosDensity = 0.5f + fRand();
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			m_PlanetResAbundance[Resource::SILICACEOUS] = fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			m_PlanetResAbundance[Resource::METALLIC] = fRand();
			m_PlanetResQ[Resource::METALLIC] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_TERRAN):
		{
			m_PlanetResAbundance[Resource::HYDROCARBON] = 0.5f + fRand() * 0.5f;
			m_PlanetResQ[Resource::HYDROCARBON] = 0.25f + fRand() * 0.75f;
			mAtmosDensity = 0.75f + fRand() * 0.5f;
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = fRand();
			m_PlanetResAbundance[Resource::METALLIC] = fRand();
			m_PlanetResQ[Resource::METALLIC] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_ICE):
		{
			m_PlanetResAbundance[Resource::HYDROCARBON] = 0.5f + fRand() * 0.5f;
			m_PlanetResQ[Resource::HYDROCARBON] = 0.25f + fRand() * 0.75f;
			mAtmosDensity = 5 + fRand() * 10.f;
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
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
			m_PlanetResAbundance[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = 0.5f + 0.5f * fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = 0.5f + 0.5f * fRand();
			m_PlanetResAbundance[Resource::METALLIC] = 0.25f * fRand();
			m_PlanetResQ[Resource::METALLIC] = 0.25f * fRand();
			//
			mObjectDiameter = fRand(1,100);
			mObjectMass = fRand(1,100);
			break;
		}
	case(ASTEROID_SILICACEOUS):
		{
			m_PlanetResAbundance[Resource::SILICACEOUS] = 0.5f + 0.5f * fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = 0.5f + 0.5f * fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_PlanetResAbundance[Resource::METALLIC] = 0.25f * fRand();
			m_PlanetResQ[Resource::METALLIC] = 0.25f * fRand();
			//
			mObjectDiameter = fRand(1,100);
			mObjectMass = fRand(1,100);
			break;
		}
	case(ASTEROID_METALLIC):
		{
			m_PlanetResAbundance[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = 0.25f * fRand();
			m_PlanetResAbundance[Resource::METALLIC] = 0.5f + 0.5f * fRand();
			m_PlanetResQ[Resource::METALLIC] = 0.5f + 0.5f * fRand();
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
