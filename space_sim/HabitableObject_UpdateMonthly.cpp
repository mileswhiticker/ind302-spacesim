#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "MathHelpers.h"

void HabitableObject::MonthlyUpdate(int a_PropogationDir, int a_Quantity)
{
	//monthly logic here
	//monthly production
	{
		//luxury goods
		float maxAmountProduceable = (m_IndustryWeighting[Industry::LUXURYGOODS_PRODUCTION] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
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

			m_StoredResQ[Resource::LUXURYGOODS] = AverageWeight(m_StoredResQ[Resource::LUXURYGOODS], m_StoredResNum[Resource::LUXURYGOODS], producedQ, amountProduced);
			m_StoredResNum[Resource::LUXURYGOODS] += amountProduced;
			//
			m_StoredResQ[Resource::GIRDERS] -= amountProduced / 4.f;
			m_StoredResQ[Resource::SHEETMETAL] -= amountProduced / 4.f;
			m_StoredResQ[Resource::CIRCUITRY] -= amountProduced / 4.f;
			m_StoredResQ[Resource::COMPONENTS] -= amountProduced / 4.f;

			//produce a bit of scrap waste
			m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
			m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
				GameManager::UpdateStoredResource(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
				GameManager::UpdateStoredResource(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
				GameManager::UpdateStoredResource(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
				GameManager::UpdateStoredResource(Resource::LUXURYGOODS, m_StoredResNum[Resource::LUXURYGOODS], m_StoredResQ[Resource::LUXURYGOODS]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}
	}
	
	//maintain infrastructure
	{
		float maintenanceNeeded = mInfrastructure * a_Quantity;
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

				float infLost = mInfrastructure * 0.1f * (maintenanceNeeded - maxMaintenancePossible) / (0.5f + avgQ);
				mInfrastructure -= infLost;
			
				//turn it into scrap waste
				m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), infLost);
				m_StoredResNum[Resource::SCRAPWASTE] += infLost;
			}
		
			m_StoredResNum[Resource::GIRDERS] -= maxMaintenancePossible / 4.f;
			m_StoredResNum[Resource::SHEETMETAL] -= maxMaintenancePossible / 4.f;
			m_StoredResNum[Resource::COMPONENTS] -= maxMaintenancePossible / 4.f;
			m_StoredResNum[Resource::CIRCUITRY] -= maxMaintenancePossible / 4.f;

			if(maxMaintenancePossible > 0)
			{
				if(mIsSelected)
				{
					GameManager::UpdateStoredResource(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
					GameManager::UpdateStoredResource(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
					GameManager::UpdateStoredResource(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
					GameManager::UpdateStoredResource(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
					GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
					//
					GameManager::UpdateSelectedInfrastructure(mInfrastructure);
				}
			}
		}
	}

	//upgrade infrastructure
	{
		float maxGrowthPossible = mInfrastructure * 0.1f * a_Quantity;
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
			mInfrastructure += infGained;
			
			//a bit of scrap waste from materials left over
			m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], fRand(), infGained / 4);
			m_StoredResNum[Resource::SCRAPWASTE] += infGained / 4;
		
			m_StoredResNum[Resource::GIRDERS] -= infGained / 4.f;
			m_StoredResNum[Resource::SHEETMETAL] -= infGained / 4.f;
			m_StoredResNum[Resource::COMPONENTS] -= infGained / 4.f;
			m_StoredResNum[Resource::CIRCUITRY] -= infGained / 4.f;
			
			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
				GameManager::UpdateStoredResource(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
				GameManager::UpdateStoredResource(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
				GameManager::UpdateStoredResource(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
				//
				GameManager::UpdateSelectedInfrastructure(mInfrastructure);
			}
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
