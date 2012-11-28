#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "MathHelpers.h"

void HabitableObject::WeeklyUpdate(int a_PropogationDir, int a_Quantity)
{
	//weekly logic here
	//produce basic finished goods
	{
		float maxUsableMetal = m_StoredResNum[Resource::METALLIC] / 2.f;

		//circuitry and components
		float maxAmountProduceable = mInfrastructureLevel[Infrastructure::ELECTRONICS_PRODUCTION] * a_Quantity;
		float amountProduced = maxAmountProduceable;

		if(amountProduced > maxUsableMetal)
			amountProduced = maxUsableMetal;
		if(amountProduced > m_StoredResNum[Resource::SILICACEOUS])
			amountProduced = m_StoredResNum[Resource::SILICACEOUS];
		
		amountProduced *= GetPersonnelMultiplier(Infrastructure::ELECTRONICS_PRODUCTION);

		if(amountProduced > 0)
		{
			float producedQ = AverageWeight(m_StoredResQ[Resource::METALLIC], 1, m_StoredResQ[Resource::SILICACEOUS], 1);
			
			//m_StoredResQ[Resource::COMPONENTS] = AverageWeight(m_StoredResQ[Resource::COMPONENTS], m_StoredResNum[Resource::COMPONENTS], producedQ, amountProduced / 2.f);
			//m_StoredResNum[Resource::COMPONENTS] += LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f;
			//m_StoredResQ[Resource::CIRCUITRY] = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], m_StoredResNum[Resource::CIRCUITRY], producedQ, amountProduced / 2.f);
			//m_StoredResNum[Resource::CIRCUITRY] += LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f;
			AddResources(Resource::COMPONENTS, producedQ, LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f);
			AddResources(Resource::CIRCUITRY, producedQ, LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f);
			//
			//m_StoredResNum[Resource::METALLIC] -= amountProduced;
			//m_StoredResNum[Resource::SILICACEOUS] -= amountProduced - amountProduced;
			RemoveResources(Resource::SILICACEOUS, amountProduced / 2.f);
			RemoveResources(Resource::METALLIC, amountProduced / 2.f);
			
			//produce a bit of scrap waste
			//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
			//m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;
			AddResources(Resource::SCRAPWASTE, producedQ, amountProduced / 4.f);

			if(mIsSelected)
			{
				UpdateUIRes(Resource::METALLIC);
				//UpdateUIRes(Resource::SILICACEOUS);
				UpdateUIRes(Resource::COMPONENTS);
				//UpdateUIRes(Resource::CIRCUITRY);
				UpdateUIRes(Resource::SCRAPWASTE);
				/*GameManager::UpdateDisplayedResStore(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateDisplayedResStore(Resource::SILICACEOUS, m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SILICACEOUS]);
				GameManager::UpdateDisplayedResStore(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
				GameManager::UpdateDisplayedResStore(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
				GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);*/
			}
		}

		//sheets and girders
		maxAmountProduceable = mInfrastructureLevel[Infrastructure::MATERIALS_PRODUCTION] * a_Quantity;
		amountProduced = maxAmountProduceable;
		if(amountProduced > maxUsableMetal)
			amountProduced = maxUsableMetal;
		if(amountProduced > m_StoredResNum[Resource::CARBONACEOUS])
			amountProduced = m_StoredResNum[Resource::CARBONACEOUS];
		
		amountProduced *= GetPersonnelMultiplier(Infrastructure::MATERIALS_PRODUCTION);

		if(amountProduced > 0)
		{
			float producedQ = AverageWeight(m_StoredResQ[Resource::METALLIC], 1, m_StoredResQ[Resource::CARBONACEOUS], 1);
			
			//m_StoredResQ[Resource::SHEETMETAL] = AverageWeight(m_StoredResQ[Resource::SHEETMETAL], m_StoredResNum[Resource::SHEETMETAL], producedQ, amountProduced / 2.f);
			//m_StoredResNum[Resource::SHEETMETAL] += LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f;
			//m_StoredResQ[Resource::GIRDERS] = AverageWeight(m_StoredResQ[Resource::GIRDERS], m_StoredResNum[Resource::GIRDERS], producedQ, amountProduced / 2.f);
			//m_StoredResNum[Resource::GIRDERS] += LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f;
			AddResources(Resource::GIRDERS, producedQ, LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f);
			AddResources(Resource::SHEETMETAL, producedQ, LOWLEVEL_PRODUCTION_MULTI * amountProduced / 2.f);
			//
			//m_StoredResNum[Resource::METALLIC] -= amountProduced / 2.f;
			//m_StoredResNum[Resource::CARBONACEOUS] -= amountProduced / 2.f;
			RemoveResources(Resource::METALLIC, amountProduced / 2.f);
			RemoveResources(Resource::CARBONACEOUS, amountProduced / 2.f);
			
			//produce a bit of scrap waste
			//m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
			//m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;
			AddResources(Resource::SCRAPWASTE, producedQ, amountProduced / 4.f);

			if(mIsSelected)
			{
				UpdateUIRes(Resource::METALLIC);
				//UpdateUIRes(Resource::CARBONACEOUS);
				UpdateUIRes(Resource::SHEETMETAL);
				//UpdateUIRes(Resource::GIRDERS);
				UpdateUIRes(Resource::SCRAPWASTE);
				/*GameManager::UpdateDisplayedResStore(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateDisplayedResStore(Resource::CARBONACEOUS, m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::CARBONACEOUS]);
				GameManager::UpdateDisplayedResStore(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
				GameManager::UpdateDisplayedResStore(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
				GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);*/
			}
		}
		
		//domestic goods
		if(mLastUpgradeSuccessful)
		{
			maxAmountProduceable = mInfrastructureLevel[Infrastructure::DOMESTICGOODS_PRODUCTION] * a_Quantity;
			amountProduced = maxAmountProduceable;
			if(amountProduced > m_StoredResNum[Resource::GIRDERS] * 4)
				amountProduced = m_StoredResNum[Resource::GIRDERS] * 4;
			if(amountProduced > m_StoredResNum[Resource::SHEETMETAL] * 4)
				amountProduced = m_StoredResNum[Resource::SHEETMETAL] * 4;
			if(amountProduced > m_StoredResNum[Resource::COMPONENTS] * 4)
				amountProduced = m_StoredResNum[Resource::COMPONENTS] * 4;
			if(amountProduced > m_StoredResNum[Resource::CIRCUITRY] * 4)
				amountProduced = m_StoredResNum[Resource::CIRCUITRY] * 4;

			amountProduced *= GetPersonnelMultiplier(Infrastructure::DOMESTICGOODS_PRODUCTION);

			if(amountProduced > 0)
			{
				float q1 = AverageWeight(m_StoredResQ[Resource::GIRDERS], 1, m_StoredResQ[Resource::SHEETMETAL], 1);
				float q2 = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], 1, m_StoredResQ[Resource::COMPONENTS], 1);
				float producedQ = AverageWeight(q1, 1, q2, 1);
				
				//m_StoredResQ[Resource::DOMESTICGOODS] = AverageWeight(m_StoredResQ[Resource::DOMESTICGOODS], m_StoredResNum[Resource::DOMESTICGOODS], producedQ, amountProduced);
				//m_StoredResNum[Resource::DOMESTICGOODS] += BASICGOODS_PRODUCTION_MULTI * amountProduced;
				AddResources(Resource::DOMESTICGOODS, producedQ, BASICGOODS_PRODUCTION_MULTI * amountProduced);
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
					UpdateUIRes(Resource::COMPONENTS);
					//UpdateUIRes(Resource::CIRCUITRY);
					UpdateUIRes(Resource::SHEETMETAL);
					//UpdateUIRes(Resource::GIRDERS);
					UpdateUIRes(Resource::DOMESTICGOODS);
					UpdateUIRes(Resource::SCRAPWASTE);
					/*GameManager::UpdateDisplayedResStore(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
					GameManager::UpdateDisplayedResStore(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
					GameManager::UpdateDisplayedResStore(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
					GameManager::UpdateDisplayedResStore(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
					GameManager::UpdateDisplayedResStore(Resource::DOMESTICGOODS, m_StoredResNum[Resource::DOMESTICGOODS], m_StoredResQ[Resource::DOMESTICGOODS]);
					GameManager::UpdateDisplayedResStore(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);*/
				}
			}
		}
	}
	
	//two-way recursion
	if(a_PropogationDir & UPWARD)
	{
		if(--m_NumLeftMonthlyUpdate <= 0)
		{
			MonthlyUpdate(UPWARD);
			m_NumLeftMonthlyUpdate = DAYS_WEEK;
		}
	}
	if(a_PropogationDir & DOWNWARD)
	{
		DailyUpdate(DOWNWARD, a_Quantity * DAYS_WEEK);
	}
}
