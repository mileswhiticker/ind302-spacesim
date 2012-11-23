#include "HabitableObject.hpp"
#include "MathHelpers.h"

void HabitableObject::GenerateData()
{
	mGenerated = true;
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
			//
			m_IndustryWeighting[Industry::MINING] = 1;
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::GAS_PROCESSING] = 1;
			m_IndustryWeighting[Industry::FUEL_PROCESSING] = 1;
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
			//
			m_IndustryWeighting[Industry::WATER_PURIFICATION] = 1;
			m_IndustryWeighting[Industry::FOOD_PROCESSING] = 1;
			m_IndustryWeighting[Industry::MINING] = 1;
			m_IndustryWeighting[Industry::GAS_PROCESSING] = 1;
			m_IndustryWeighting[Industry::FUEL_PROCESSING] = 1;
			//
			m_IndustryWeighting[Industry::MATERIALS_PRODUCTION] = 1;
			m_IndustryWeighting[Industry::ELECTRONICS_PRODUCTION] = 1;
			//m_IndustryWeighting[Industry::MACHINERY_PRODUCTION] = 1;
			//m_IndustryWeighting[Industry::DOMESTICGOODS_PRODUCTION] = 1;
			//m_IndustryWeighting[Industry::LUXURYGOODS_PRODUCTION] = 1;

			mInfrastructure = 1;
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
			//
			m_IndustryWeighting[Industry::WATER_PURIFICATION] = 1;
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::GAS_PROCESSING] = 1;
			m_IndustryWeighting[Industry::FUEL_PROCESSING] = 1;
			break;
		}
	case(PLANET_GASGIANT):
		{
			mAtmosDensity = 500 + fRand() * 500.f;
			//
			mObjectDiameter = fRand(100000,1000000);
			//
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::GAS_PROCESSING] = 1;
			m_IndustryWeighting[Industry::FUEL_PROCESSING] = 1;
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
			//
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::MINING] = 1;
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
			//
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::MINING] = 1;
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
			//
			m_IndustryWeighting[Industry::ATMOSPHERICS] = 1;
			m_IndustryWeighting[Industry::MINING] = 1;
			break;
		}
	}

	RecalculateIndustryWeighting();
}
