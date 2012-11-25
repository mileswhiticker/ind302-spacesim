#include "HabitableObject.hpp"
#include "GameManager.hpp"
#include "MathHelpers.h"

void HabitableObject::DailyUpdate(int a_PropogationDir, int a_Quantity)
{
	//daily logic here

	//mining
	{
		float newMinerals = mInfrastructureLevel[Infrastructure::MINING] * a_Quantity * MINING_MULTI;
		
		if(newMinerals > 0)
		{
			//m_StoredResQ[Resource::CARBONACEOUS] = AverageWeight(m_StoredResQ[Resource::CARBONACEOUS], m_StoredResNum[Resource::CARBONACEOUS], m_PlanetResQ[Resource::CARBONACEOUS], newMinerals * m_PlanetResAbundance[Resource::CARBONACEOUS]);
			//m_StoredResNum[Resource::CARBONACEOUS] += newMinerals * m_PlanetResAbundance[Resource::CARBONACEOUS];
			AddResources(Resource::CARBONACEOUS, m_PlanetResQ[Resource::CARBONACEOUS], newMinerals * m_PlanetResAbundance[Resource::CARBONACEOUS]);

			//m_StoredResQ[Resource::METALLIC] = AverageWeight(m_StoredResQ[Resource::METALLIC], m_StoredResNum[Resource::METALLIC], m_PlanetResQ[Resource::METALLIC], newMinerals * m_PlanetResAbundance[Resource::METALLIC]);
			//m_StoredResNum[Resource::METALLIC] += newMinerals * m_PlanetResAbundance[Resource::METALLIC];
			AddResources(Resource::METALLIC, m_PlanetResQ[Resource::METALLIC], newMinerals * m_PlanetResAbundance[Resource::METALLIC]);

			//m_StoredResQ[Resource::SILICACEOUS] = AverageWeight(m_StoredResQ[Resource::SILICACEOUS], m_StoredResNum[Resource::SILICACEOUS], m_PlanetResQ[Resource::SILICACEOUS], newMinerals * m_PlanetResAbundance[Resource::SILICACEOUS]);
			//m_StoredResNum[Resource::SILICACEOUS] += newMinerals * m_PlanetResAbundance[Resource::SILICACEOUS];
			AddResources(Resource::SILICACEOUS, m_PlanetResQ[Resource::SILICACEOUS], newMinerals * m_PlanetResAbundance[Resource::SILICACEOUS]);

			//m_StoredResQ[Resource::WATERCRYSTALS] = AverageWeight(m_StoredResQ[Resource::WATERCRYSTALS], m_StoredResNum[Resource::WATERCRYSTALS], m_PlanetResQ[Resource::WATERCRYSTALS], newMinerals * m_PlanetResAbundance[Resource::WATERCRYSTALS]);
			//m_StoredResNum[Resource::WATERCRYSTALS] += newMinerals * m_PlanetResAbundance[Resource::WATERCRYSTALS];
			AddResources(Resource::WATERCRYSTALS, m_PlanetResQ[Resource::WATERCRYSTALS], newMinerals * m_PlanetResAbundance[Resource::WATERCRYSTALS]);

			//produce a bit of scrap waste
			//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), newMinerals / 4.f);
			//m_StoredResNum[Resource::SCRAPWASTE] += newMinerals / 4.f;
			AddResources(Resource::SCRAPWASTE, fRand(), newMinerals / 4.f);
			
			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::CARBONACEOUS, m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::CARBONACEOUS]);
				GameManager::UpdateDisplayedResStore(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateDisplayedResStore(Resource::SILICACEOUS, m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SILICACEOUS]);
				GameManager::UpdateDisplayedResStore(Resource::WATERCRYSTALS, m_StoredResNum[Resource::WATERCRYSTALS], m_StoredResQ[Resource::WATERCRYSTALS]);
				GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}
	}

	//water processing (WATERCRYSTALS -> h20, because screw chemistry)
	{
		//terran planets dont need to process water crystals, instead pull it straight from the environment (Q1)
		float waterProduced = mInfrastructureLevel[Infrastructure::WATER_PURIFICATION] * a_Quantity;
		if(mMyHabitableType != HabitableObject::PLANET_TERRAN && waterProduced > m_StoredResNum[Resource::WATERCRYSTALS])
			waterProduced = m_StoredResNum[Resource::WATERCRYSTALS];
		
		if(waterProduced > 0)
		{
			if(mMyHabitableType == HabitableObject::PLANET_TERRAN)
			{
				//m_StoredResQ[Resource::WATER] = AverageWeight(m_StoredResQ[Resource::WATER], m_StoredResNum[Resource::WATER], 1, waterProduced * WATER_PRODUCTION_MULTI);
				AddResources(Resource::WATER, 1, waterProduced * WATER_PRODUCTION_MULTI);
			}
			else
			{
				AddResources(Resource::WATER, m_StoredResQ[Resource::WATERCRYSTALS], waterProduced * WATER_PRODUCTION_MULTI);
				//m_StoredResQ[Resource::WATER] = AverageWeight(m_StoredResQ[Resource::WATER], m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATERCRYSTALS], waterProduced * WATER_PRODUCTION_MULTI);
			}
			//m_StoredResNum[Resource::WATER] += waterProduced * WATER_PRODUCTION_MULTI;*/

			if(mMyHabitableType != HabitableObject::PLANET_TERRAN)
			{
				RemoveResources(Resource::WATERCRYSTALS, waterProduced);
				//m_StoredResNum[Resource::WATERCRYSTALS] -= waterProduced;
			}

			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
				GameManager::UpdateDisplayedResStore(Resource::WATERCRYSTALS, m_StoredResNum[Resource::WATERCRYSTALS], m_StoredResQ[Resource::WATERCRYSTALS]);
			}
		}
	}

	//gas processing
	{
		float gasProduced = mInfrastructureLevel[Infrastructure::GAS_PROCESSING] * mAtmosDensity * a_Quantity;
		
		if(gasProduced > 0)
		{
			//m_StoredResQ[Resource::HYDROGEN] = AverageWeight(m_StoredResQ[Resource::HYDROGEN], m_StoredResNum[Resource::HYDROGEN], m_PlanetResQ[Resource::HYDROGEN], m_PlanetResAbundance[Resource::HYDROGEN] * gasProduced);
			//m_StoredResNum[Resource::HYDROGEN] += m_PlanetResAbundance[Resource::HYDROGEN] * gasProduced;
			AddResources(Resource::HYDROGEN, m_PlanetResQ[Resource::HYDROGEN], m_PlanetResAbundance[Resource::HYDROGEN] * gasProduced);
		
			//m_StoredResQ[Resource::OXYGEN] = AverageWeight(m_StoredResQ[Resource::OXYGEN], m_StoredResNum[Resource::OXYGEN], m_PlanetResQ[Resource::OXYGEN], m_PlanetResAbundance[Resource::OXYGEN] * gasProduced);
			//m_StoredResNum[Resource::OXYGEN] += m_PlanetResAbundance[Resource::OXYGEN] * gasProduced;
			AddResources(Resource::OXYGEN, m_PlanetResQ[Resource::OXYGEN], m_PlanetResAbundance[Resource::OXYGEN] * gasProduced);
		
			//m_StoredResQ[Resource::PERFLUOROCARBONS] = AverageWeight(m_StoredResQ[Resource::PERFLUOROCARBONS], m_StoredResNum[Resource::PERFLUOROCARBONS], m_PlanetResQ[Resource::PERFLUOROCARBONS], m_PlanetResAbundance[Resource::PERFLUOROCARBONS] * gasProduced);
			//m_StoredResNum[Resource::PERFLUOROCARBONS] += m_PlanetResAbundance[Resource::PERFLUOROCARBONS] * gasProduced;
		
			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::OXYGEN, m_StoredResNum[Resource::OXYGEN], m_StoredResQ[Resource::OXYGEN]);
				GameManager::UpdateDisplayedResStore(Resource::HYDROGEN, m_StoredResNum[Resource::HYDROGEN], m_StoredResQ[Resource::HYDROGEN]);
				//GameManager::UpdateDisplayedResStore(Resource::PERFLUOROCARBONS, m_StoredResNum[Resource::PERFLUOROCARBONS], m_StoredResQ[Resource::PERFLUOROCARBONS]);
			}
		}
	}

	//fuel processing
	{
		//turn hydrogen into fuel
		float fuelProduced = mInfrastructureLevel[Infrastructure::FUEL_PROCESSING] * a_Quantity;
		if(fuelProduced > m_StoredResNum[Resource::HYDROGEN])
			fuelProduced = m_StoredResNum[Resource::HYDROGEN];
		
		if(fuelProduced > 0)
		{
			//m_StoredResQ[Resource::FUEL] = AverageWeight(m_StoredResQ[Resource::FUEL], m_StoredResNum[Resource::FUEL], m_StoredResQ[Resource::HYDROGEN], m_StoredResNum[Resource::HYDROGEN]);
			//m_StoredResNum[Resource::FUEL] += fuelProduced * FUEL_PRODUCTION_MULTI;
			AddResources(Resource::FUEL, m_StoredResQ[Resource::HYDROGEN], fuelProduced * FUEL_PRODUCTION_MULTI);

			//m_StoredResNum[Resource::HYDROGEN] -= fuelProduced;
			RemoveResources(Resource::HYDROGEN, fuelProduced);

			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::FUEL, m_StoredResNum[Resource::FUEL], m_StoredResQ[Resource::FUEL]);
				GameManager::UpdateDisplayedResStore(Resource::HYDROGEN, m_StoredResNum[Resource::HYDROGEN], m_StoredResQ[Resource::HYDROGEN]);
			}
		}
	}
	
	//soil for farming
	{
		if(mMyHabitableType == HabitableObject::PLANET_TERRAN)
		{
			//if we're a terran planet, get soil from the ground (Q1)
			mStoredSoilForFarming = mInfrastructureLevel[Infrastructure::FOOD_PROCESSING];
			mQSoilForFarming = 1;
			/*if(mStoredSoilForFarming < mInfrastructureLevel[Infrastructure::FOOD_PROCESSING])
			{
				//mQSoilForFarming = AverageWeight(mQSoilForFarming, mStoredSoilForFarming, 1, mInfrastructureLevel[Infrastructure::FOOD_PROCESSING] * 0.2f);
				//mStoredSoilForFarming = max(mInfrastructureLevel[Infrastructure::FOOD_PROCESSING] * 1.2f, mInfrastructureLevel[Infrastructure::FOOD_PROCESSING]);
			}
			else
			{
				//
			}*/
		}
		else
		{
			if(mStoredSoilForFarming >= mInfrastructureLevel[Infrastructure::FOOD_PROCESSING])
			{
				//check to see if we want to replace some soil
				if(m_StoredResQ[Resource::ORGANICWASTE] > mQSoilForFarming)
				{
					float removedSoil = min(mStoredSoilForFarming * 0.95f, m_StoredResNum[Resource::ORGANICWASTE]);
					float removedQuality = mQSoilForFarming;
					//
					mQSoilForFarming = AverageWeight(mQSoilForFarming, mStoredSoilForFarming - removedSoil, m_StoredResQ[Resource::ORGANICWASTE], removedSoil);
					m_StoredResQ[Resource::ORGANICWASTE] = AverageWeight(m_StoredResQ[Resource::ORGANICWASTE] - removedSoil, m_StoredResNum[Resource::ORGANICWASTE], removedQuality, removedSoil);
				}
			}
			else
			{
				//turn some organic waste into soil
				float maxNewSoil = mInfrastructureLevel[Infrastructure::FOOD_PROCESSING] * 0.05f;
				if(maxNewSoil > m_StoredResNum[Resource::ORGANICWASTE])
					maxNewSoil = m_StoredResNum[Resource::ORGANICWASTE];
				if(mStoredSoilForFarming + maxNewSoil > mInfrastructureLevel[Infrastructure::FOOD_PROCESSING])
					maxNewSoil = mInfrastructureLevel[Infrastructure::FOOD_PROCESSING] - mStoredSoilForFarming;
				//
				mQSoilForFarming = AverageWeight(mQSoilForFarming, mStoredSoilForFarming, m_StoredResQ[Resource::ORGANICWASTE], maxNewSoil);
				mStoredSoilForFarming += maxNewSoil;
				//m_StoredResNum[Resource::ORGANICWASTE] -= maxNewSoil;
				RemoveResources(Resource::ORGANICWASTE, maxNewSoil);
			}
		}
	}
	
	//waste processing
	{
		//preference recycling above disposal

		//organic (sewage) recycling into water
		float amountWasteProcessed = mInfrastructureLevel[Infrastructure::WASTE_RECYCLING] * a_Quantity * WASTE_PROCESSING_MULTIPLIER;
		if(amountWasteProcessed > m_StoredResNum[Resource::ORGANICWASTE])
			amountWasteProcessed = m_StoredResNum[Resource::ORGANICWASTE];
		
		if(amountWasteProcessed > 0)
		{
			//m_StoredResQ[Resource::WATER] = AverageWeight(m_StoredResQ[Resource::WATER], m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::ORGANICWASTE], amountWasteProcessed / WASTE_PROCESSING_MULTIPLIER);
			//m_StoredResNum[Resource::WATER] += amountWasteProcessed / WASTE_PROCESSING_MULTIPLIER;
			AddResources(Resource::WATER, m_StoredResQ[Resource::ORGANICWASTE], amountWasteProcessed / WASTE_PROCESSING_MULTIPLIER);
			
			//m_StoredResNum[Resource::ORGANICWASTE] -= amountWasteProcessed;
			RemoveResources(Resource::ORGANICWASTE, amountWasteProcessed);

			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::ORGANICWASTE, m_StoredResNum[Resource::ORGANICWASTE], m_StoredResQ[Resource::ORGANICWASTE]);
				GameManager::UpdateDisplayedResStore(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
			}
		}
		
		//scrap recycling into ore
		amountWasteProcessed = mInfrastructureLevel[Infrastructure::SCRAP_RECYCLING] * a_Quantity * SCRAP_PROCESSING_MULTIPLIER;
		if(amountWasteProcessed > m_StoredResNum[Resource::SCRAPWASTE])
			amountWasteProcessed = m_StoredResNum[Resource::SCRAPWASTE];
		
		if(amountWasteProcessed > 0)
		{
			//float metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			//m_StoredResQ[Resource::CARBONACEOUS] = AverageWeight(m_StoredResQ[Resource::CARBONACEOUS], m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			//m_StoredResNum[Resource::CARBONACEOUS] += metalProcessed;
			AddResources(Resource::CARBONACEOUS, fRand(), (amountWasteProcessed / 3.f) * fRand());
		
			//metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			//m_StoredResQ[Resource::SILICACEOUS] = AverageWeight(m_StoredResQ[Resource::SILICACEOUS], m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			//m_StoredResNum[Resource::SILICACEOUS] += metalProcessed;
			AddResources(Resource::SILICACEOUS, fRand(), (amountWasteProcessed / 3.f) * fRand());
		
			//metalProcessed = (amountWasteProcessed / 3.f) * fRand();
			//m_StoredResQ[Resource::METALLIC] = AverageWeight(m_StoredResQ[Resource::METALLIC], m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::SCRAPWASTE], metalProcessed);
			//m_StoredResNum[Resource::METALLIC] += metalProcessed;
			AddResources(Resource::METALLIC, fRand(), (amountWasteProcessed / 3.f) * fRand());
		
			//m_StoredResNum[Resource::SCRAPWASTE] -= amountWasteProcessed;
			RemoveResources(Resource::SCRAPWASTE, amountWasteProcessed);

			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
				GameManager::UpdateDisplayedResStore(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateDisplayedResStore(Resource::SILICACEOUS, m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SILICACEOUS]);
				GameManager::UpdateDisplayedResStore(Resource::CARBONACEOUS, m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::CARBONACEOUS]);
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
