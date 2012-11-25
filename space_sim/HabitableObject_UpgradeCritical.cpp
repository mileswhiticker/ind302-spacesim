#include "HabitableObject.hpp"

Infrastructure::InfrastructureType HabitableObject::DecideNextCriticalUpgrade(float& a_AmountToUpgrade)
{
	a_AmountToUpgrade = 0;
	while(!a_AmountToUpgrade)
	{
		switch(mLastCriticalUpgrade)
		{
		default:
			{
				//new cycle, do POWER_GENERATION now
				float target = POWERUSE_PER_INF * m_TotalInfrastructureLevel * (1 + CRITICAL_SAFETY_MARGIN);
				if(target > mInfrastructureLevel[Infrastructure::POWER_GENERATION])
				{
					a_AmountToUpgrade = target - mInfrastructureLevel[Infrastructure::POWER_GENERATION];
				}
				mLastCriticalUpgrade = Infrastructure::POWER_GENERATION;
				break;
			}
		case(Infrastructure::POWER_GENERATION):
			{
				//did POWER_GENERATION last, do ATMOSPHERICS now
				if(mMyHabitableType != HabitableObject::PLANET_TERRAN)
				{
					//only need atmospherics if we dont have a breathable atmosphere
					float target = ATMOSUSE_PER_INF * m_TotalInfrastructureLevel * (1 + CRITICAL_SAFETY_MARGIN);
					if(target > mInfrastructureLevel[Infrastructure::ATMOSPHERICS])
					{
						a_AmountToUpgrade = target - mInfrastructureLevel[Infrastructure::ATMOSPHERICS];
					}
				}
				mLastCriticalUpgrade = Infrastructure::ATMOSPHERICS;
				break;
			}
		case(Infrastructure::ATMOSPHERICS):
			{
				//did ATMOSPHERICS last, do FOOD_PROCESSING now
				//first, if we have enough to feed everyone for the next year then don't worry about building new farms
				if(m_StoredResNum[Resource::FOOD] < mPopulation * FOOD_PERPERSON_PERDAY * (1 + CRITICAL_SAFETY_MARGIN) * DAYS_WEEK * WEEKS_MONTH * MONTHS_YEAR)
				{
					//work out if we're producing enough to feed everyone per month
					float targetFoodInf = (mPopulation * FOOD_PERPERSON_PERDAY * (1 + CRITICAL_SAFETY_MARGIN) * DAYS_WEEK * WEEKS_MONTH) / FOOD_PRODUCTION_MULTI;
					float foodInfNeeded = targetFoodInf - mInfrastructureLevel[Infrastructure::FOOD_PROCESSING];
					if(foodInfNeeded > 0)
					{
						a_AmountToUpgrade = foodInfNeeded;
					}
				}

				mLastCriticalUpgrade = Infrastructure::FOOD_PROCESSING;
				break;
			}
		case(Infrastructure::FOOD_PROCESSING):
			{
				//did FOOD_PROCESSING last, do WATER_PURIFICATION now
				//first, if we have water for everyone for the next year then don't worry about building new purification plants
				if(m_StoredResNum[Resource::WATER] < mPopulation * WATER_PERPERSON_PERDAY * (1 + CRITICAL_SAFETY_MARGIN) * DAYS_WEEK * WEEKS_MONTH * MONTHS_YEAR)
				{
					float targetWaterProduction = 0;
					if(mMyHabitableType == HabitableObject::PLANET_TERRAN || mMyHabitableType == HabitableObject::PLANET_ICE)
					{
						//if we're a terran or ice planet, build according to what water we consume
						targetWaterProduction = (mPopulation * WATER_PERPERSON_PERDAY * (1 + CRITICAL_SAFETY_MARGIN)) / WATER_PRODUCTION_MULTI;
					}
					else
					{
						//otherwise, build according to what stocks of raw material we have
						targetWaterProduction = m_StoredResNum[Resource::WATERCRYSTALS] / (DAYS_WEEK * WEEKS_MONTH);
					}

					float waterProductionNeeded = targetWaterProduction - mInfrastructureLevel[Infrastructure::WATER_PURIFICATION];
					if(waterProductionNeeded > 0)
					{
						a_AmountToUpgrade = waterProductionNeeded;
					}
				}
				
				mLastCriticalUpgrade = Infrastructure::WATER_PURIFICATION;
				break;
			}
		case(Infrastructure::WATER_PURIFICATION):
			{
				//did WATER_PURIFICATION last, we're finished this cycle
				mLastCriticalUpgrade = Infrastructure::MAXVAL;
				return mLastCriticalUpgrade;
			}
		}
	}
	return mLastCriticalUpgrade;
}
