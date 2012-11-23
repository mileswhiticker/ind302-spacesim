#include "HabitableObject.hpp"
#include "GameManager.hpp"
#include "MathHelpers.h"

void HabitableObject::DailyUpdate(int a_PropogationDir, int a_Quantity)
{
	//daily logic here

	//mining
	{
		float newMinerals = (m_IndustryWeighting[Industry::MINING] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		
		if(newMinerals > 0)
		{
			m_StoredResQ[Resource::CARBONACEOUS] = AverageWeight(m_StoredResQ[Resource::CARBONACEOUS], m_StoredResNum[Resource::CARBONACEOUS], m_PlanetResQ[Resource::CARBONACEOUS], newMinerals * m_PlanetResAbundance[Resource::CARBONACEOUS]);
			m_StoredResNum[Resource::CARBONACEOUS] += newMinerals * m_PlanetResAbundance[Resource::CARBONACEOUS];

			m_StoredResQ[Resource::METALLIC] = AverageWeight(m_StoredResQ[Resource::METALLIC], m_StoredResNum[Resource::METALLIC], m_PlanetResQ[Resource::METALLIC], newMinerals * m_PlanetResAbundance[Resource::METALLIC]);
			m_StoredResNum[Resource::METALLIC] += newMinerals * m_PlanetResAbundance[Resource::METALLIC];

			m_StoredResQ[Resource::SILICACEOUS] = AverageWeight(m_StoredResQ[Resource::SILICACEOUS], m_StoredResNum[Resource::SILICACEOUS], m_PlanetResQ[Resource::SILICACEOUS], newMinerals * m_PlanetResAbundance[Resource::SILICACEOUS]);
			m_StoredResNum[Resource::SILICACEOUS] += newMinerals * m_PlanetResAbundance[Resource::SILICACEOUS];

			m_StoredResQ[Resource::HYDROCARBON] = AverageWeight(m_StoredResQ[Resource::HYDROCARBON], m_StoredResNum[Resource::HYDROCARBON], m_PlanetResQ[Resource::HYDROCARBON], newMinerals * m_PlanetResAbundance[Resource::HYDROCARBON]);
			m_StoredResNum[Resource::HYDROCARBON] += newMinerals * m_PlanetResAbundance[Resource::HYDROCARBON];
		
			//produce a bit of scrap waste
			m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), newMinerals / 4.f);
			m_StoredResNum[Resource::SCRAPWASTE] += newMinerals / 4.f;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::CARBONACEOUS, m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::CARBONACEOUS]);
				GameManager::UpdateStoredResource(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateStoredResource(Resource::SILICACEOUS, m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SILICACEOUS]);
				GameManager::UpdateStoredResource(Resource::HYDROCARBON, m_StoredResNum[Resource::HYDROCARBON], m_StoredResQ[Resource::HYDROCARBON]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}
	}

	//water processing (hydrocarbons -> h20, because screw chemistry)
	{
		float waterProduced = (m_IndustryWeighting[Industry::WATER_PURIFICATION] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		if(waterProduced > m_StoredResNum[Resource::HYDROCARBON])
			waterProduced = m_StoredResNum[Resource::HYDROCARBON];

		if(waterProduced > 0)
		{
			m_StoredResQ[Resource::WATER] = AverageWeight(m_StoredResQ[Resource::WATER], m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::HYDROCARBON], waterProduced);
			m_StoredResNum[Resource::WATER] += waterProduced;

			m_StoredResNum[Resource::HYDROCARBON] -= waterProduced;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
			}
		}
	}

	//gas processing
	{
		float gasProduced = (m_IndustryWeighting[Industry::GAS_PROCESSING] / mTotalIndWeighting) * mInfrastructure * mAtmosDensity * a_Quantity;
		
		if(gasProduced > 0)
		{
			m_StoredResQ[Resource::HYDROGEN] = AverageWeight(m_StoredResQ[Resource::HYDROGEN], m_StoredResNum[Resource::HYDROGEN], m_PlanetResQ[Resource::HYDROGEN], m_PlanetResAbundance[Resource::HYDROGEN] * gasProduced);
			m_StoredResNum[Resource::HYDROGEN] += m_PlanetResAbundance[Resource::HYDROGEN] * gasProduced;
		
			m_StoredResQ[Resource::OXYGEN] = AverageWeight(m_StoredResQ[Resource::OXYGEN], m_StoredResNum[Resource::OXYGEN], m_PlanetResQ[Resource::OXYGEN], m_PlanetResAbundance[Resource::OXYGEN] * gasProduced);
			m_StoredResNum[Resource::OXYGEN] += m_PlanetResAbundance[Resource::OXYGEN] * gasProduced;
		
			m_StoredResQ[Resource::PERFLUOROCARBONS] = AverageWeight(m_StoredResQ[Resource::PERFLUOROCARBONS], m_StoredResNum[Resource::PERFLUOROCARBONS], m_PlanetResQ[Resource::PERFLUOROCARBONS], m_PlanetResAbundance[Resource::PERFLUOROCARBONS] * gasProduced);
			m_StoredResNum[Resource::PERFLUOROCARBONS] += m_PlanetResAbundance[Resource::PERFLUOROCARBONS] * gasProduced;
		
			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::OXYGEN, m_StoredResNum[Resource::OXYGEN], m_StoredResQ[Resource::OXYGEN]);
				GameManager::UpdateStoredResource(Resource::HYDROGEN, m_StoredResNum[Resource::HYDROGEN], m_StoredResQ[Resource::HYDROGEN]);
				GameManager::UpdateStoredResource(Resource::PERFLUOROCARBONS, m_StoredResNum[Resource::PERFLUOROCARBONS], m_StoredResQ[Resource::PERFLUOROCARBONS]);
			}
		}
	}

	//waste processing
	{
		//preference recycling above disposal

		//organic (sewage) recycling into water
		float amountWasteProcessed = (m_IndustryWeighting[Industry::WASTE_RECYCLING] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		
		if(amountWasteProcessed > 0)
		{
			m_StoredResQ[Resource::WATER] = AverageWeight(m_StoredResQ[Resource::WATER], m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::ORGANICWASTE], amountWasteProcessed);
			m_StoredResNum[Resource::WATER] += amountWasteProcessed;
			
			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::ORGANICWASTE]);
			}
		}
		
		//scrap recycling into ore
		amountWasteProcessed = (m_IndustryWeighting[Industry::SCRAP_RECYCLING] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		if(amountWasteProcessed > m_StoredResNum[Resource::SCRAPWASTE])
			amountWasteProcessed = m_StoredResNum[Resource::SCRAPWASTE];
		
		if(amountWasteProcessed > 0)
		{
			float metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			m_StoredResQ[Resource::CARBONACEOUS] = AverageWeight(m_StoredResQ[Resource::CARBONACEOUS], m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			m_StoredResNum[Resource::CARBONACEOUS] += metalProcessed;
		
			metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			m_StoredResQ[Resource::SILICACEOUS] = AverageWeight(m_StoredResQ[Resource::SILICACEOUS], m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			m_StoredResNum[Resource::SILICACEOUS] += metalProcessed;
		
			metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			m_StoredResQ[Resource::METALLIC] = AverageWeight(m_StoredResQ[Resource::METALLIC], m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			m_StoredResNum[Resource::METALLIC] += metalProcessed;
		
			m_StoredResNum[Resource::SCRAPWASTE] -= amountWasteProcessed;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}
	}
	
	//two-way recursion
	if(a_PropogationDir & UPWARD)
	{
		if(--m_NumLeftWeeklyUpdate <= 0)
		{
			WeeklyUpdate(UPWARD);
			m_NumLeftWeeklyUpdate = DAYS_WEEK;
		}
	}
	if(a_PropogationDir & DOWNWARD)
	{
		HourlyUpdate(DOWNWARD, a_Quantity * HOURS_DAY);
	}
}
