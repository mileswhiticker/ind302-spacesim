#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "MathHelpers.h"

#define BASIC_GOODS_MULTIPLIER 2.f
#define METAL_USAGE_RATIO 0.8f

void HabitableObject::WeeklyUpdate(int a_PropogationDir, int a_Quantity)
{
	//weekly logic here
	//produce basic finished foods
	{
		//circuitry and components
		float maxAmountProduceable = BASIC_GOODS_MULTIPLIER * (m_IndustryWeighting[Industry::ELECTRONICS_PRODUCTION] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		float amountProduced = maxAmountProduceable;
		if(amountProduced * METAL_USAGE_RATIO > m_StoredResNum[Resource::METALLIC])
			amountProduced = m_StoredResNum[Resource::METALLIC] / METAL_USAGE_RATIO;
		if(amountProduced > m_StoredResNum[Resource::SILICACEOUS])
			amountProduced = m_StoredResNum[Resource::SILICACEOUS];

		if(amountProduced > 0)
		{
			float producedQ = AverageWeight(m_StoredResQ[Resource::METALLIC], 1, m_StoredResQ[Resource::SILICACEOUS], 1);

			m_StoredResQ[Resource::COMPONENTS] = AverageWeight(m_StoredResQ[Resource::COMPONENTS], m_StoredResNum[Resource::COMPONENTS], producedQ, amountProduced / 2.f);
			m_StoredResNum[Resource::COMPONENTS] += amountProduced / 2.f;
			m_StoredResQ[Resource::CIRCUITRY] = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], m_StoredResNum[Resource::CIRCUITRY], producedQ, amountProduced / 2.f);
			m_StoredResNum[Resource::CIRCUITRY] += amountProduced / 2.f;
			//
			m_StoredResNum[Resource::METALLIC] -= amountProduced * METAL_USAGE_RATIO;
			m_StoredResNum[Resource::SILICACEOUS] -= amountProduced - amountProduced * METAL_USAGE_RATIO;
			
			//produce a bit of scrap waste
			m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
			m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateStoredResource(Resource::SILICACEOUS, m_StoredResNum[Resource::SILICACEOUS], m_StoredResQ[Resource::SILICACEOUS]);
				GameManager::UpdateStoredResource(Resource::COMPONENTS, m_StoredResNum[Resource::COMPONENTS], m_StoredResQ[Resource::COMPONENTS]);
				GameManager::UpdateStoredResource(Resource::CIRCUITRY, m_StoredResNum[Resource::CIRCUITRY], m_StoredResQ[Resource::CIRCUITRY]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}

		//sheets and girders
		maxAmountProduceable = BASIC_GOODS_MULTIPLIER * (m_IndustryWeighting[Industry::MATERIALS_PRODUCTION] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		amountProduced = maxAmountProduceable;
		if(amountProduced * METAL_USAGE_RATIO > m_StoredResNum[Resource::METALLIC])
			amountProduced = m_StoredResNum[Resource::METALLIC] / METAL_USAGE_RATIO;
		if(amountProduced > m_StoredResNum[Resource::CARBONACEOUS])
			amountProduced = m_StoredResNum[Resource::CARBONACEOUS];
		
		if(amountProduced > 0)
		{
			float producedQ = AverageWeight(m_StoredResQ[Resource::METALLIC], 1, m_StoredResQ[Resource::CARBONACEOUS], 1);

			m_StoredResQ[Resource::SHEETMETAL] = AverageWeight(m_StoredResQ[Resource::SHEETMETAL], m_StoredResNum[Resource::SHEETMETAL], producedQ, amountProduced / 2.f);
			m_StoredResNum[Resource::SHEETMETAL] += amountProduced / 2.f;
			m_StoredResQ[Resource::GIRDERS] = AverageWeight(m_StoredResQ[Resource::GIRDERS], m_StoredResNum[Resource::GIRDERS], producedQ, amountProduced / 2.f);
			m_StoredResNum[Resource::GIRDERS] += amountProduced / 2.f;
			//
			m_StoredResNum[Resource::METALLIC] -= amountProduced * METAL_USAGE_RATIO;
			m_StoredResNum[Resource::CARBONACEOUS] -= amountProduced - amountProduced * METAL_USAGE_RATIO;
			
			//produce a bit of scrap waste
			m_StoredResQ[Resource::SCRAPWASTE] = AverageWeight(m_StoredResQ[Resource::SCRAPWASTE], m_StoredResNum[Resource::SCRAPWASTE], producedQ, amountProduced / 4.f);
			m_StoredResNum[Resource::SCRAPWASTE] += amountProduced / 4.f;

			if(mIsSelected)
			{
				GameManager::UpdateStoredResource(Resource::METALLIC, m_StoredResNum[Resource::METALLIC], m_StoredResQ[Resource::METALLIC]);
				GameManager::UpdateStoredResource(Resource::CARBONACEOUS, m_StoredResNum[Resource::CARBONACEOUS], m_StoredResQ[Resource::CARBONACEOUS]);
				GameManager::UpdateStoredResource(Resource::SHEETMETAL, m_StoredResNum[Resource::SHEETMETAL], m_StoredResQ[Resource::SHEETMETAL]);
				GameManager::UpdateStoredResource(Resource::GIRDERS, m_StoredResNum[Resource::GIRDERS], m_StoredResQ[Resource::GIRDERS]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
			}
		}
		
		//domestic goods
		maxAmountProduceable = BASIC_GOODS_MULTIPLIER * (m_IndustryWeighting[Industry::DOMESTICGOODS_PRODUCTION] / mTotalIndWeighting) * mInfrastructure * a_Quantity;
		amountProduced = maxAmountProduceable;
		if(amountProduced > m_StoredResNum[Resource::GIRDERS] * 4)
			amountProduced = m_StoredResNum[Resource::GIRDERS] * 4;
		if(amountProduced > m_StoredResNum[Resource::SHEETMETAL] * 4)
			amountProduced = m_StoredResNum[Resource::SHEETMETAL] * 4;
		if(amountProduced > m_StoredResNum[Resource::COMPONENTS] * 4)
			amountProduced = m_StoredResNum[Resource::COMPONENTS] * 4;
		if(amountProduced > m_StoredResNum[Resource::CIRCUITRY] * 4)
			amountProduced = m_StoredResNum[Resource::CIRCUITRY] * 4;
		
		if(amountProduced > 0)
		{
			float q1 = AverageWeight(m_StoredResQ[Resource::GIRDERS], 1, m_StoredResQ[Resource::SHEETMETAL], 1);
			float q2 = AverageWeight(m_StoredResQ[Resource::CIRCUITRY], 1, m_StoredResQ[Resource::COMPONENTS], 1);
			float producedQ = AverageWeight(q1, 1, q2, 1);

			m_StoredResQ[Resource::DOMESTICGOODS] = AverageWeight(m_StoredResQ[Resource::DOMESTICGOODS], m_StoredResNum[Resource::DOMESTICGOODS], producedQ, amountProduced);
			m_StoredResNum[Resource::DOMESTICGOODS] += amountProduced;
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
				GameManager::UpdateStoredResource(Resource::DOMESTICGOODS, m_StoredResNum[Resource::DOMESTICGOODS], m_StoredResQ[Resource::DOMESTICGOODS]);
				GameManager::UpdateStoredResource(Resource::SCRAPWASTE, m_StoredResNum[Resource::SCRAPWASTE], m_StoredResQ[Resource::SCRAPWASTE]);
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
