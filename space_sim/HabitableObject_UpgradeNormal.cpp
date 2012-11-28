#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "MathHelpers.h"

Infrastructure::InfrastructureType HabitableObject::DecideNextIndUpgrade(float& a_AmountToUpgrade)
{
	a_AmountToUpgrade = 0;

	//loop through infrastructure to see what we need
	while(!a_AmountToUpgrade)
	//for(Infrastructure::InfrastructureType curInfType = Infrastructure::SHIP_PRODUCTION; curInfType < Infrastructure::MAXVAL; curInfType = Infrastructure::InfrastructureType(int(curInfType) + 1))
	{
		//only consider building this infrastructure if it's allowed for this HabO type
		float weighting = GameManager::GetInfWeighting(mMyHabitableType, mLastIndUpgrade);
		switch(mLastIndUpgrade)
		{
		//case(Infrastructure::WATER_PURIFICATION):
		default:
			{
				//new cycle, do FUEL_PROCESSING next
				//first, if we have fuel for the next year then don't worry about building new fuel processing infrastructure
				float fuelOverNextYear = m_TotalInfrastructureLevel * POWERUSE_PER_INF * POWER_FUEL_CONSUMPTION * (1 + CRITICAL_SAFETY_MARGIN) * DAYS_WEEK * WEEKS_MONTH * MONTHS_YEAR;
				if(m_StoredResNum[Resource::FUEL] < fuelOverNextYear)
				{
					float targetFuelInf = 0;
					if(mMyHabitableType == HabitableObject::PLANET_TERRAN || mMyHabitableType == HabitableObject::PLANET_DEAD || mMyHabitableType == HabitableObject::PLANET_GASGIANT)
					{
						//build according to what fuel we consume
						targetFuelInf = (m_TotalInfrastructureLevel * POWERUSE_PER_INF * (1 + CRITICAL_SAFETY_MARGIN)) / POWER_FUEL_CONSUMPTION;
					}
					else
					{
						//otherwise, build according to what stocks of raw material we have
						targetFuelInf = m_StoredResNum[Resource::HYDROGEN] / (DAYS_WEEK * WEEKS_MONTH);
					}
					float fuelInfNeeded = targetFuelInf - mInfrastructureLevel[Infrastructure::FUEL_PROCESSING];
					if(fuelInfNeeded > 0)
					{
						a_AmountToUpgrade = fuelInfNeeded;
					}
				}

				mLastIndUpgrade = Infrastructure::FUEL_PROCESSING;
				break;
			}
		case(Infrastructure::FUEL_PROCESSING):
			{
				//did fuel processing last, do electronics next
				//if we have enough to cover maintenance for the next year, don't worry about building new infrastructure
				float totalRes = m_StoredResNum[Resource::CIRCUITRY] + m_StoredResNum[Resource::COMPONENTS];
				if(totalRes < m_TotalInfrastructureLevel * MONTHS_YEAR / 2)
				{
					if(mMyHabitableType == HabitableObject::PLANET_TERRAN || mMyHabitableType == HabitableObject::PLANET_DEAD)
					{
						//linear upgrade
						if(mInfrastructureLevel[Infrastructure::ELECTRONICS_PRODUCTION] > 1)
							a_AmountToUpgrade = mInfrastructureLevel[Infrastructure::ELECTRONICS_PRODUCTION] * 0.1f;
						else
							a_AmountToUpgrade = 1;
					}
					else if(m_StoredResNum[Resource::METALLIC] > 0 && m_StoredResNum[Resource::SILICACEOUS] > 0)
					{
						//otherwise, build according to what stocks of raw material we have
						float a_AmountToUpgrade = min(m_StoredResNum[Resource::METALLIC], m_StoredResNum[Resource::SILICACEOUS]);
					}
				}

				mLastIndUpgrade = Infrastructure::ELECTRONICS_PRODUCTION;
				break;
			}
		case(Infrastructure::ELECTRONICS_PRODUCTION):
			{
				//did electronics last, do materials production next
				//if we have enough to cover maintenance for the next year, don't worry about building new infrastructure
				float totalRes = m_StoredResNum[Resource::SHEETMETAL] + m_StoredResNum[Resource::GIRDERS];
				if(totalRes < m_TotalInfrastructureLevel * MONTHS_YEAR / 2)
				{
					if(mMyHabitableType == HabitableObject::PLANET_TERRAN || mMyHabitableType == HabitableObject::PLANET_DEAD)
					{
						//linear upgrade
						if(mInfrastructureLevel[Infrastructure::MATERIALS_PRODUCTION] > 1)
							a_AmountToUpgrade = mInfrastructureLevel[Infrastructure::MATERIALS_PRODUCTION] * 0.1f;
						else
							a_AmountToUpgrade = 1;
					}
					else if(m_StoredResNum[Resource::METALLIC] > 0 && m_StoredResNum[Resource::SILICACEOUS] > 0)
					{
						//otherwise, build according to what stocks of raw material we have
						a_AmountToUpgrade = min(m_StoredResNum[Resource::METALLIC], m_StoredResNum[Resource::SILICACEOUS]);
					}
				}

				mLastIndUpgrade = Infrastructure::MATERIALS_PRODUCTION;
				break;
			}
		case(Infrastructure::MATERIALS_PRODUCTION):
			{
				//did MATERIALS_PRODUCTION last, do GAS_PROCESSING next
				//if we have space for a resource and can collect it, build up

				if(m_PlanetResAbundance[Resource::OXYGEN] && m_StoredResNum[Resource::OXYGEN] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				if(m_PlanetResAbundance[Resource::HYDROGEN] && m_StoredResNum[Resource::HYDROGEN] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				
				mLastIndUpgrade = Infrastructure::GAS_PROCESSING;
				break;
			}
		case(Infrastructure::GAS_PROCESSING):
			{
				//did GAS_PROCESSING last, do SCRAP_RECYCLING next
				//work out if we can clear the current stocks of scrap in a month, or if not then how much extra recycling we need
				float scrapRecycledMonthly = mInfrastructureLevel[Infrastructure::SCRAP_RECYCLING] * DAYS_WEEK * WEEKS_MONTH * SCRAP_PROCESSING_MULTIPLIER;
				float scrapRecyclingNeeded = m_StoredResNum[Resource::SCRAPWASTE] - scrapRecycledMonthly;
				if(scrapRecyclingNeeded > 0)
				{
					a_AmountToUpgrade = scrapRecyclingNeeded;
				}
					
				mLastIndUpgrade = Infrastructure::SCRAP_RECYCLING;
				break;
			}
		case(Infrastructure::SCRAP_RECYCLING):
			{
				//did SCRAP_RECYCLING last, do WASTE_RECYCLING next
				//work out if we can clear the current stocks of waste in a month, or if not then how much extra recycling we need
				float wasteRecycledMonthly = mInfrastructureLevel[Infrastructure::WASTE_RECYCLING] * DAYS_WEEK * WEEKS_MONTH * WASTE_PROCESSING_MULTIPLIER;
				float wasteRecyclingNeeded = m_StoredResNum[Resource::ORGANICWASTE] - wasteRecycledMonthly;
				if(wasteRecyclingNeeded > 0)
				{
					a_AmountToUpgrade = wasteRecyclingNeeded;
				}
					
				mLastIndUpgrade = Infrastructure::WASTE_RECYCLING;
				break;
			}
		case(Infrastructure::WASTE_RECYCLING):
			{
				//did WASTE_RECYCLING last, do MINING next
				
				if(m_PlanetResAbundance[Resource::SILICACEOUS] && m_StoredResNum[Resource::SILICACEOUS] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				if(m_PlanetResAbundance[Resource::CARBONACEOUS] && m_StoredResNum[Resource::CARBONACEOUS] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				if(m_PlanetResAbundance[Resource::METALLIC] && m_StoredResNum[Resource::METALLIC] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				if(m_PlanetResAbundance[Resource::WATERCRYSTALS] && m_StoredResNum[Resource::WATERCRYSTALS] < mCalculatedResourceSpace * (3.f / float(Resource::MAXVAL)))
				{
					a_AmountToUpgrade += 1;
				}
				
				/*if(mMyHabitableType == HabitableObject::PLANET_TERRAN || mMyHabitableType == HabitableObject::PLANET_DEAD || mMyHabitableType == HabitableObject::PLANET_ICE || mMyHabitableType == HabitableObject::ASTEROID_CARBONACEOUS || mMyHabitableType == HabitableObject::ASTEROID_SILICACEOUS || mMyHabitableType == HabitableObject::ASTEROID_METALLIC)
				{
					//work out how much will be consumed over the next year, and whether we have enough for that
					float yearlyConsumption = (mInfrastructureLevel[Infrastructure::ELECTRONICS_PRODUCTION] + mInfrastructureLevel[Infrastructure::MATERIALS_PRODUCTION]) * WEEKS_MONTH * MONTHS_YEAR;
					float totalStocks = m_StoredResNum[Resource::SILICACEOUS] + m_StoredResNum[Resource::CARBONACEOUS] + m_StoredResNum[Resource::METALLIC];
					if(mMyHabitableType != HabitableObject::PLANET_TERRAN)
					{
						yearlyConsumption += mInfrastructureLevel[Infrastructure::WATER_PURIFICATION] * WEEKS_MONTH * MONTHS_YEAR;
						totalStocks += m_StoredResNum[Resource::WATERCRYSTALS];
					}

					if(totalStocks < yearlyConsumption)
					{
						if(mInfrastructureLevel[Infrastructure::MINING] > 1)
							a_AmountToUpgrade = mInfrastructureLevel[Infrastructure::MINING] * 0.1f;
						else
							a_AmountToUpgrade = 1;
					}
				}*/
					
				mLastIndUpgrade = Infrastructure::MINING;
				break;
			}
		case(Infrastructure::MINING):
			{
				//did MINING last, do DOMESTICGOODS next
				//work out regular consumption, then work out how much we need to match that
				float targetInf = mPopulation * (1 + CRITICAL_SAFETY_MARGIN) * DOMESTICGOODS_CONSUMPTION_PPERSON;
				float infNeeded = targetInf - mInfrastructureLevel[Infrastructure::DOMESTICGOODS_PRODUCTION];
				if(infNeeded > 0)
				{
					a_AmountToUpgrade = infNeeded;
				}
				
					
				mLastIndUpgrade = Infrastructure::DOMESTICGOODS_PRODUCTION;
				break;
			}
		case(Infrastructure::DOMESTICGOODS_PRODUCTION):
			{
				//did MATERIALS_PRODUCTION last, do LUXURYGOODS_PRODUCTION next
				//work out regular consumption, then work out how much we need to match that
				float targetInf = mPopulation * (1 + CRITICAL_SAFETY_MARGIN) * LUXURYGOODS_CONSUMPTION_PPERSON;
				float infNeeded = targetInf - mInfrastructureLevel[Infrastructure::LUXURYGOODS_PRODUCTION];
				if(infNeeded > 0)
				{
					a_AmountToUpgrade = infNeeded;
				}
				
				mLastIndUpgrade = Infrastructure::LUXURYGOODS_PRODUCTION;
				break;
			}
		case(Infrastructure::LUXURYGOODS_PRODUCTION):
			{
				//finished
				mLastIndUpgrade = Infrastructure::MAXVAL;

				//so we don't infinite loop
				return mLastIndUpgrade;
			}
		}
	}

	return mLastIndUpgrade;
}
