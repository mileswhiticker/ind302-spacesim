#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "MathHelpers.h"

void HabitableObject::MonthlyUpdate(int a_PropogationDir, int a_Quantity)
{
	//monthly logic here
	//monthly production
	{
		float maxAmountProduceable = 0;
		//luxury goods
		if(mLastUpgradeSuccessful)
		{
			maxAmountProduceable = mInfrastructureLevel[Infrastructure::LUXURYGOODS_PRODUCTION] * a_Quantity;
			float amountProduced = maxAmountProduceable;
			if(amountProduced > m_StoredResNum[Resource::GIRDERS] * 4)
				amountProduced = m_StoredResNum[Resource::GIRDERS] * 4;
			if(amountProduced > m_StoredResNum[Resource::SHEETMETAL] * 4)
				amountProduced = m_StoredResNum[Resource::SHEETMETAL] * 4;
			if(amountProduced > m_StoredResNum[Resource::COMPONENTS] * 4)
				amountProduced = m_StoredResNum[Resource::COMPONENTS] * 4;
			if(amountProduced > m_StoredResNum[Resource::CIRCUITRY] * 4)
				amountProduced = m_StoredResNum[Resource::CIRCUITRY] * 4;
		
			if(amountProduced)
			{
				float q1 = AverageWeight(m_StoredResQ[Resource::GIRDERS], 1, m_StoredResQ[Resource::SHEETMETAL], 1);
				float q2 = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], 1, m_StoredResQ[Resource::COMPONENTS], 1);
				float producedQ = AverageWeight(q1, 1, q2, 1);

				//m_StoredResQ[Resource::LUXURYGOODS] = AverageWeight(m_StoredResQ[Resource::LUXURYGOODS], m_StoredResNum[Resource::LUXURYGOODS], producedQ, amountProduced);
				//m_StoredResNum[Resource::LUXURYGOODS] += amountProduced;
				AddResources(Resource::LUXURYGOODS, producedQ, amountProduced);
				//
				//m_StoredResNum[Resource::GIRDERS] -= amountProduced / 4.f;
				//m_StoredResNum[Resource::SHEETMETAL] -= amountProduced / 4.f;
				//m_StoredResNum[Resource::CIRCUITRY] -= amountProduced / 4.f;
				//m_StoredResNum[Resource::COMPONENTS] -= amountProduced / 4.f;
				RemoveResources(Resource::GIRDERS, amountProduced / 4.f);
				RemoveResources(Resource::SHEETMETAL, amountProduced / 4.f);
				RemoveResources(Resource::CIRCUITRY, amountProduced / 4.f);
				RemoveResources(Resource::COMPONENTS, amountProduced / 4.f);

				//produce a bit of scrap waste
				//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
				//m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;
				AddResources(Resource::SCRAPWASTE, producedQ, amountProduced / 4.f);


				if(mIsSelected)
				{
					GameManager::UpdateDisplayedResStore(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
					GameManager::UpdateDisplayedResStore(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
					GameManager::UpdateDisplayedResStore(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
					GameManager::UpdateDisplayedResStore(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
					GameManager::UpdateDisplayedResStore(Resource::LUXURYGOODS, m_StoredResNum[Resource::LUXURYGOODS], m_StoredResQ[Resource::LUXURYGOODS]);
					GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
				}
			}
		}

		//food
		maxAmountProduceable = mInfrastructureLevel[Infrastructure::FOOD_PROCESSING] * a_Quantity;
		//only produce as much as we have soil capacity for
		if(maxAmountProduceable > mStoredSoilForFarming)
			maxAmountProduceable = mStoredSoilForFarming;
		//if we don't have enough water, equalise the two as much as possible
		if(maxAmountProduceable > m_StoredResNum[Resource::WATER])
		{
			//todo
			maxAmountProduceable = m_StoredResNum[Resource::WATER];
		}

		if(maxAmountProduceable)
		{
			float producedQ = AverageWeight(mQSoilForFarming, 1, m_StoredResQ[Resource::WATER], 1);
			maxAmountProduceable *= FOOD_PRODUCTION_MULTI;

			//grow food
			//m_StoredResQ[Resource::FOOD] = AverageWeight(m_StoredResQ[Resource::FOOD], m_StoredResNum[Resource::FOOD], producedQ, maxAmountProduceable);
			//m_StoredResNum[Resource::FOOD] += maxAmountProduceable;
			//m_StoredResNum[Resource::WATER] -= maxAmountProduceable / FOOD_PRODUCTION_MULTI;
			AddResources(Resource::FOOD, producedQ, maxAmountProduceable);
			RemoveResources(Resource::WATER, maxAmountProduceable / FOOD_PRODUCTION_MULTI);

			//soil quality goes down a bit
			if(mMyHabitableType != HabitableObject::PLANET_TERRAN)
				mQSoilForFarming *= 0.75f;

			//produce a bit of organic waste
			//m_StoredResQ[Resource::ORGANICWASTE] = AverageWeight(m_StoredResQ[Resource::ORGANICWASTE], m_StoredResNum[Resource::ORGANICWASTE], producedQ, maxAmountProduceable * 0.1f);
			//m_StoredResNum[Resource::ORGANICWASTE] += maxAmountProduceable * 0.1f;
			AddResources(Resource::ORGANICWASTE, producedQ, maxAmountProduceable * 0.1f);

			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::FOOD, m_StoredResNum[Resource::FOOD], m_StoredResQ[Resource::FOOD]);
				GameManager::UpdateDisplayedResStore(Resource::WATER, m_StoredResNum[Resource::WATER], m_StoredResQ[Resource::WATER]);
			}
		}
	}
	
	//births and natural deaths
	{
		//todo: sickness from poor Q water (food also?)
		//first, check if there's enough room to grow
		int popRoom = int(mInfrastructureLevel[Infrastructure::RESIDENTIAL] * POP_PER_RESIDENTIAL);
		if(popRoom > mPopulation)
		{
			int newBorns = int(mPopulation * fRand(POP_GROWTH_FLOOR, POP_GROWTH_CEILING));
			mPopulation += newBorns;
			if(mPopulation > popRoom)
			{
				std::cout << mPopulation - popRoom << " people are homeless " << "(" << newBorns << " are newborns)!" << std::endl;
			}
		}

		//some people die of old age
		mPopulation -= int(mPopulation * fRand(NATDEATH_GROWTH_FLOOR, NATDEATH_GROWTH_CEILING));
	}

	//the colony citizens buy stuff
	{
		//#define LUXURYGOODS_CONSUMPTION_PPERSON 0.0001f
		//#define DOMESTICGOODS_CONSUMPTION_PPERSON 0.001f
		
		//todo: financial implications of this? (colony earns money, citizens lose money w/e)

		//domestic goods
		float qMulti = (1 - m_StoredResQ[Resource::DOMESTICGOODS]) * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		float goodsNeeded = DOMESTICGOODS_CONSUMPTION_PPERSON * mPopulation * qMulti;
		//
		if(goodsNeeded > m_StoredResNum[Resource::DOMESTICGOODS])
		{
			//not enough! the people get unhappy
			//todo
			goodsNeeded = m_StoredResNum[Resource::DOMESTICGOODS];
		}
		//m_StoredResNum[Resource::DOMESTICGOODS] -= goodsNeeded;
		RemoveResources(Resource::DOMESTICGOODS, goodsNeeded);

		//luxury goods
		qMulti = (1 - m_StoredResQ[Resource::LUXURYGOODS]) * 2.f;
		if(qMulti < 0.1f)
			qMulti = 0.1f;
		goodsNeeded = LUXURYGOODS_CONSUMPTION_PPERSON * mPopulation * qMulti;
		//
		if(goodsNeeded > m_StoredResNum[Resource::LUXURYGOODS])
		{
			//not enough! the people get unhappy
			//todo
			goodsNeeded = m_StoredResNum[Resource::LUXURYGOODS];
		}
		//m_StoredResNum[Resource::LUXURYGOODS] -= goodsNeeded;
		RemoveResources(Resource::LUXURYGOODS, goodsNeeded);
	}

	//maintain infrastructure
	{
		float maintenanceNeeded = m_TotalInfrastructureLevel * a_Quantity;
		float maxMaintenancePossible = maintenanceNeeded;
		if(maxMaintenancePossible > m_StoredResNum[Resource::GIRDERS] * 4)
			maxMaintenancePossible = m_StoredResNum[Resource::GIRDERS] * 4;
		if(maxMaintenancePossible > m_StoredResNum[Resource::SHEETMETAL] * 4)
			maxMaintenancePossible = m_StoredResNum[Resource::SHEETMETAL] * 4;
		if(maxMaintenancePossible > m_StoredResNum[Resource::COMPONENTS] * 4)
			maxMaintenancePossible = m_StoredResNum[Resource::COMPONENTS] * 4;
		if(maxMaintenancePossible > m_StoredResNum[Resource::CIRCUITRY] * 4)
			maxMaintenancePossible = m_StoredResNum[Resource::CIRCUITRY] * 4;

		if(maxMaintenancePossible > 0)
		{
			if(maxMaintenancePossible < maintenanceNeeded)
			{
				//higher quality materials result in less development lost
				float q1 = AverageWeight(m_StoredResQ[Resource::GIRDERS], 1, m_StoredResQ[Resource::SHEETMETAL], 1);
				float q2 = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], 1, m_StoredResQ[Resource::COMPONENTS], 1);
				float avgQ = AverageWeight(q1, 1, q2, 1);

				float infLost = m_TotalInfrastructureLevel * 0.1f * (maintenanceNeeded - maxMaintenancePossible) / (0.5f + avgQ);
				DowngradeInfrastructure(infLost);
			
				//turn it into scrap waste
				//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), infLost);
				//m_StoredResNum[Resource::SCRAPWASTE] += infLost;
				AddResources(Resource::SCRAPWASTE, fRand(), infLost);

				mLastUpgradeSuccessful = false;
			}
		
			//m_StoredResNum[Resource::GIRDERS] -= maxMaintenancePossible / 4.f;
			//m_StoredResNum[Resource::SHEETMETAL] -= maxMaintenancePossible / 4.f;
			//m_StoredResNum[Resource::COMPONENTS] -= maxMaintenancePossible / 4.f;
			//m_StoredResNum[Resource::CIRCUITRY] -= maxMaintenancePossible / 4.f;
			RemoveResources(Resource::GIRDERS, maxMaintenancePossible / 4.f);
			RemoveResources(Resource::SHEETMETAL, maxMaintenancePossible / 4.f);
			RemoveResources(Resource::COMPONENTS, maxMaintenancePossible / 4.f);
			RemoveResources(Resource::CIRCUITRY, maxMaintenancePossible / 4.f);

			if(!m_StoredResNum[Resource::GIRDERS] || m_StoredResNum[Resource::SHEETMETAL] || m_StoredResNum[Resource::COMPONENTS] || m_StoredResNum[Resource::CIRCUITRY])
				mLastUpgradeSuccessful = false;

			if(maxMaintenancePossible > 0)
			{
				if(mIsSelected)
				{
					GameManager::UpdateDisplayedResStore(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
					GameManager::UpdateDisplayedResStore(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
					GameManager::UpdateDisplayedResStore(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
					GameManager::UpdateDisplayedResStore(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
					GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
					//
					GameManager::UpdateSelectedInfrastructure(m_TotalInfrastructureLevel);
				}
			}
		}
		else
		{
			mLastUpgradeSuccessful = false;
		}
	}

	//upgrade infrastructure
	{
		float maxGrowthPossible = (m_TotalInfrastructureLevel > 0 ? m_TotalInfrastructureLevel : 1) * 0.25f * a_Quantity;
		if(maxGrowthPossible > m_StoredResNum[Resource::GIRDERS] * 4)
			maxGrowthPossible = m_StoredResNum[Resource::GIRDERS] * 4;
		if(maxGrowthPossible > m_StoredResNum[Resource::SHEETMETAL] * 4)
			maxGrowthPossible = m_StoredResNum[Resource::SHEETMETAL] * 4;
		if(maxGrowthPossible > m_StoredResNum[Resource::COMPONENTS] * 4)
			maxGrowthPossible = m_StoredResNum[Resource::COMPONENTS] * 4;
		if(maxGrowthPossible > m_StoredResNum[Resource::CIRCUITRY] * 4)
			maxGrowthPossible = m_StoredResNum[Resource::CIRCUITRY] * 4;

		if(maxGrowthPossible > 0)
		{
			//higher quality materials result in faster development
			float q1 = AverageWeight(m_StoredResQ[Resource::GIRDERS], 1, m_StoredResQ[Resource::SHEETMETAL], 1);
			float q2 = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], 1, m_StoredResQ[Resource::COMPONENTS], 1);
			float avgQ = AverageWeight(q1, 1, q2, 1);

			float infGained = maxGrowthPossible * (0.5f + avgQ);
			UpgradeInfrastructure(infGained);
			
			//a bit of scrap waste from materials left over
			//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), infGained / 4);
			//m_StoredResNum[Resource::SCRAPWASTE] += infGained / 4;
			AddResources(Resource::SCRAPWASTE, fRand(), infGained / 4);

			//m_StoredResNum[Resource::GIRDERS] -= infGained / 4.f;
			//m_StoredResNum[Resource::SHEETMETAL] -= infGained / 4.f;
			//m_StoredResNum[Resource::COMPONENTS] -= infGained / 4.f;
			//m_StoredResNum[Resource::CIRCUITRY] -= infGained / 4.f;
			RemoveResources(Resource::GIRDERS, infGained / 4.f);
			RemoveResources(Resource::SHEETMETAL, infGained / 4.f);
			RemoveResources(Resource::COMPONENTS, infGained / 4.f);
			RemoveResources(Resource::CIRCUITRY, infGained / 4.f);
			
			if(mIsSelected)
			{
				GameManager::UpdateDisplayedResStore(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
				GameManager::UpdateDisplayedResStore(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
				GameManager::UpdateDisplayedResStore(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
				GameManager::UpdateDisplayedResStore(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
				GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
				//
			}
			mLastUpgradeSuccessful = true;
		}
		else
		{
			mLastUpgradeSuccessful = false;
		}
	}
	
	//two-way recursion
	if(a_PropogationDir & UPWARD)
	{
		if(--m_NumLeftYearlyUpdate <= 0)
		{
			YearlyUpdate(UPWARD);
			m_NumLeftYearlyUpdate = DAYS_WEEK;
		}
	}
	if(a_PropogationDir & DOWNWARD)
	{
		WeeklyUpdate(DOWNWARD, a_Quantity * WEEKS_MONTH);
	}
}
