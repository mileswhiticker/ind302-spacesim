#include "HabitableObject.hpp"
#include "MathHelpers.h"

void HabitableObject::GenerateData()
{
	mGenerated = true;
	switch(mMyHabitableType)
	{
	case(PLANET_DEAD):
		{
			if(prob(25))
			{
				m_PlanetResAbundance[Resource::WATERCRYSTALS] = fRand() * 0.25f;
				m_PlanetResQ[Resource::WATERCRYSTALS] = fRand();
			}
			mAtmosDensity = 0.5f + fRand();
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = 1 + fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = 1 + fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = fRand();
			m_PlanetResAbundance[Resource::METALLIC] = 1.25f + 0.75f * fRand();
			m_PlanetResQ[Resource::METALLIC] = fRand();
			//
			m_PlanetResAbundance[Resource::HYDROGEN] = 0.25f + 0.75f * fRand();
			m_PlanetResQ[Resource::HYDROGEN] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_TERRAN):
		{
			m_PlanetResAbundance[Resource::WATERCRYSTALS] = 0.5f + fRand() * 0.5f;
			m_PlanetResQ[Resource::WATERCRYSTALS] = 0.75f + fRand() * 0.25f;
			mAtmosDensity = 0.75f + fRand() * 0.5f;
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			m_PlanetResAbundance[Resource::CARBONACEOUS] = fRand();
			m_PlanetResQ[Resource::CARBONACEOUS] = fRand();
			m_PlanetResAbundance[Resource::METALLIC] = fRand();
			m_PlanetResQ[Resource::METALLIC] = fRand();
			//
			m_PlanetResAbundance[Resource::HYDROGEN] = 0.5f * fRand();
			m_PlanetResQ[Resource::HYDROGEN] = fRand();
			//m_PlanetResAbundance[Resource::PERFLUOROCARBONS] = 0.001f * fRand();
			//m_PlanetResQ[Resource::PERFLUOROCARBONS] = fRand();
			m_PlanetResAbundance[Resource::OXYGEN] = 0.5f + 0.5f * fRand();
			m_PlanetResQ[Resource::OXYGEN] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			//
			RecalculateStorageNeeded();
			break;
		}
	case(PLANET_ICE):
		{
			m_PlanetResAbundance[Resource::WATERCRYSTALS] = 0.25f + fRand() * 0.75f;
			m_PlanetResQ[Resource::WATERCRYSTALS] = fRand();
			mAtmosDensity = 10 + fRand() * 100.f;
			//
			m_PlanetResAbundance[Resource::SILICACEOUS] = 0.25f * fRand();
			m_PlanetResQ[Resource::SILICACEOUS] = fRand();
			//
			m_PlanetResAbundance[Resource::HYDROGEN] = 0.5f * fRand();
			m_PlanetResQ[Resource::HYDROGEN] = fRand();
			//
			mObjectDiameter = fRand(10000,100000);
			mObjectMass = fRand(10000,100000);
			break;
		}
	case(PLANET_GASGIANT):
		{
			mAtmosDensity = 100 + fRand() * 1000.f;
			//
			m_PlanetResAbundance[Resource::HYDROGEN] = 0.75f + 0.25f * fRand();
			m_PlanetResQ[Resource::HYDROGEN] = 0.5f + 0.5f * fRand();
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

	RecalculateInfrastructureLevel();
}
