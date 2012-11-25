#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "GameHelpers.hpp"

void HabitableObject::UpgradeInfrastructure(float a_TotalUpgrades)
{
	//reset these
	mCriticalGrowthTarget = 0;
	mGrowthTarget = 0;

	bool isLooping = false;
	while(a_TotalUpgrades > 0)
	{
		//critical infrastructure
		float targetUpgrade = 0;
		while(DecideNextCriticalUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			if(a_TotalUpgrades > 0)
			{
				if(targetUpgrade > a_TotalUpgrades)
				{
					//not enough to fully match the requirements
					mInfrastructureLevel[mLastCriticalUpgrade] += a_TotalUpgrades;
					mCriticalGrowthTarget += targetUpgrade - a_TotalUpgrades;
					a_TotalUpgrades = 0;
				}
				else
				{
					mInfrastructureLevel[mLastCriticalUpgrade] += targetUpgrade;
					a_TotalUpgrades -= targetUpgrade;
				}

				if(mIsSelected)
				{
					if(mLastCriticalUpgrade == Infrastructure::WATER_PURIFICATION)
						GameManager::UpdateDisplayedResInf(Resource::WATER, mInfrastructureLevel[mLastCriticalUpgrade]);
					else if(mLastCriticalUpgrade == Infrastructure::FOOD_PROCESSING)
						GameManager::UpdateDisplayedResInf(Resource::FOOD, mInfrastructureLevel[mLastCriticalUpgrade]);
					else
						GameManager::UpdateDisplayedInf(mLastCriticalUpgrade, mInfrastructureLevel[mLastCriticalUpgrade]);
				}
			}
			else
			{
				//add to growth requirements
				mCriticalGrowthTarget += targetUpgrade;
			}
		}

		//utility infrastructure
		targetUpgrade = 0;
		while(DecideNextUtilUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			if(a_TotalUpgrades > 0)
			{
				if(targetUpgrade > a_TotalUpgrades)
				{
					//not enough to fully upgrade
					mInfrastructureLevel[mLastUtilUpgrade] += a_TotalUpgrades;
					mCriticalGrowthTarget += targetUpgrade - a_TotalUpgrades;
					a_TotalUpgrades = 0;
				}
				else
				{
					mInfrastructureLevel[mLastUtilUpgrade] += targetUpgrade;
					a_TotalUpgrades -= targetUpgrade;
				}

				if(mLastUtilUpgrade == Infrastructure::STORAGE)
					mCalculatedResourceSpace = mInfrastructureLevel[Infrastructure::STORAGE] * SPACE_PER_STORAGE;

				if(mIsSelected)
					GameManager::UpdateDisplayedInf(mLastUtilUpgrade, mInfrastructureLevel[mLastUtilUpgrade]);
			}
			else
			{
				//add to growth requirements
				mGrowthTarget += targetUpgrade;
			}
		}

		//normal infrastructure (resource producing)
		targetUpgrade = 0;
		while(a_TotalUpgrades > 0 && DecideNextIndUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			if(a_TotalUpgrades > 0)
			{
				if(targetUpgrade > a_TotalUpgrades)
				{
					//not enough to fully upgrade
					mInfrastructureLevel[mLastIndUpgrade] += a_TotalUpgrades;
					mGrowthTarget += targetUpgrade - a_TotalUpgrades;
					a_TotalUpgrades = 0;
				}
				else
				{
					mInfrastructureLevel[mLastIndUpgrade] += targetUpgrade;
					a_TotalUpgrades -= targetUpgrade;
				}
			
				if(mIsSelected)
				{
					switch(mLastIndUpgrade)
					{
					case(Infrastructure::WASTE_RECYCLING):
						{
							GameManager::UpdateDisplayedInf(mLastIndUpgrade, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::SCRAP_RECYCLING):
						{
							GameManager::UpdateDisplayedInf(mLastIndUpgrade, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::DISPOSAL):
						{
							GameManager::UpdateDisplayedInf(mLastIndUpgrade, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::MINING):
						{
							GameManager::UpdateDisplayedResInf(Resource::CARBONACEOUS, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::SILICACEOUS, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::METALLIC, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::WATERCRYSTALS, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::FUEL_PROCESSING):
						{
							GameManager::UpdateDisplayedResInf(Resource::FUEL, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::WATER_PURIFICATION):
						{
							GameManager::UpdateDisplayedResInf(Resource::WATER, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::GAS_PROCESSING):
						{
							GameManager::UpdateDisplayedResInf(Resource::OXYGEN, mInfrastructureLevel[mLastIndUpgrade]);
							//GameManager::UpdateDisplayedResInf(Resource::PERFLUOROCARBONS, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::HYDROGEN, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::ELECTRONICS_PRODUCTION):
						{
							GameManager::UpdateDisplayedResInf(Resource::CIRCUITRY, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::COMPONENTS, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::MATERIALS_PRODUCTION):
						{
							GameManager::UpdateDisplayedResInf(Resource::SHEETMETAL, mInfrastructureLevel[mLastIndUpgrade]);
							GameManager::UpdateDisplayedResInf(Resource::GIRDERS, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::DOMESTICGOODS_PRODUCTION):
						{
							GameManager::UpdateDisplayedResInf(Resource::DOMESTICGOODS, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					case(Infrastructure::FOOD_PROCESSING):
						{
							GameManager::UpdateDisplayedResInf(Resource::FOOD, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					/*case(Infrastructure::MACHINERY_PRODUCTION):
						{
							GameManager::UpdateDisplayedResInf(Resource::MACHINERY, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}*/
					case(Infrastructure::LUXURYGOODS_PRODUCTION):
						{
							GameManager::UpdateDisplayedResInf(Resource::LUXURYGOODS, mInfrastructureLevel[mLastIndUpgrade]);
							break;
						}
					}
				}
			}
			else
			{
				//add to growth requirements
				mGrowthTarget += targetUpgrade;
			}
		}
		
		//special infrastructure (low priority stuff)
		targetUpgrade = 0;
		while(a_TotalUpgrades > 0 && DecideNextSpecialUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			if(a_TotalUpgrades > 0)
			{
				if(targetUpgrade > a_TotalUpgrades)
				{
					//not enough to fully upgrade
					mInfrastructureLevel[mLastSpecialUpgrade] += a_TotalUpgrades;
					mGrowthTarget += targetUpgrade - a_TotalUpgrades;
					a_TotalUpgrades = 0;
				}
				else
				{
					mInfrastructureLevel[mLastSpecialUpgrade] += targetUpgrade;
					a_TotalUpgrades -= targetUpgrade;
				}

				if(mIsSelected)
					GameManager::UpdateDisplayedInf(mLastSpecialUpgrade, mInfrastructureLevel[mLastSpecialUpgrade]);
			}
		}

		//do this last
		RecalculateStorageNeeded();
		RecalculateInfrastructureLevel();

		if(isLooping)
			break;
		isLooping = true;
	}

	if(mIsSelected)
	{
		GameManager::UpdateSelectedInfrastructure(m_TotalInfrastructureLevel);
	}
}

void HabitableObject::DowngradeInfrastructure(float a_TotalDowngrades)
{
	//
	RecalculateInfrastructureLevel();
	if(mIsSelected)
	{
		GameManager::UpdateSelectedInfrastructure(m_TotalInfrastructureLevel);
	}
}
