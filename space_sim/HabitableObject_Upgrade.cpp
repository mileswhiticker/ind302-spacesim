#include "HabitableObject.hpp"

#include "GameManager.hpp"
#include "GameHelpers.hpp"
#include "MathHelpers.h"

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
			mCriticalGrowthTarget += max(targetUpgrade - a_TotalUpgrades, 0);
			if(targetUpgrade > a_TotalUpgrades)
			{
				//not enough to fully match the requirements
				targetUpgrade = a_TotalUpgrades;
			}

			if(targetUpgrade > 0)
			{
				//std::cout << targetUpgrade << " " << GetInfrastructureStringname(mLastCriticalUpgrade) << " upgrades." << std::endl;
				mInfrastructureLevel[mLastCriticalUpgrade] += targetUpgrade;
				a_TotalUpgrades -= targetUpgrade;

				if(mIsSelected)
				{
					UpdateUIInf(mLastCriticalUpgrade);
					/*if(mLastCriticalUpgrade == Infrastructure::WATER_PURIFICATION)
						GameManager::UpdateDisplayedResInf(Resource::WATER, mInfrastructureLevel[mLastCriticalUpgrade]);
					else if(mLastCriticalUpgrade == Infrastructure::FOOD_PROCESSING)
						GameManager::UpdateDisplayedResInf(Resource::FOOD, mInfrastructureLevel[mLastCriticalUpgrade]);
					else
						GameManager::UpdateDisplayedInf(mLastCriticalUpgrade, mInfrastructureLevel[mLastCriticalUpgrade]);*/
				}
			}
		}

		//utility infrastructure
		targetUpgrade = 0;
		while(DecideNextUtilUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			mGrowthTarget += max(targetUpgrade - a_TotalUpgrades, 0);
			if(targetUpgrade > a_TotalUpgrades)
			{
				//not enough to fully upgrade
				targetUpgrade = a_TotalUpgrades;
			}
				
			if(targetUpgrade > 0)
			{
				//std::cout << targetUpgrade << " " << GetInfrastructureStringname(mLastUtilUpgrade) << " upgrades." << std::endl;
				mInfrastructureLevel[mLastUtilUpgrade] += targetUpgrade;
				a_TotalUpgrades -= targetUpgrade;

				if(mLastUtilUpgrade == Infrastructure::STORAGE)
					mCalculatedResourceSpace = mInfrastructureLevel[Infrastructure::STORAGE] * SPACE_PER_STORAGE;

				if(mIsSelected)
				{
					//GameManager::UpdateDisplayedInf(mLastUtilUpgrade, mInfrastructureLevel[mLastUtilUpgrade]);
					UpdateUIInf(mLastUtilUpgrade);
				}
			}
		}

		//normal infrastructure (resource producing)
		targetUpgrade = 0;
		while(a_TotalUpgrades > 0 && DecideNextIndUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			mGrowthTarget += max(targetUpgrade - a_TotalUpgrades, 0);
			if(targetUpgrade > a_TotalUpgrades)
			{
				//not enough to fully upgrade
				targetUpgrade = a_TotalUpgrades;
			}
			
			if(targetUpgrade > 0)
			{
				//std::cout << targetUpgrade << " " << GetInfrastructureStringname(mLastIndUpgrade) << " upgrades." << std::endl;
				mInfrastructureLevel[mLastIndUpgrade] += targetUpgrade;
				a_TotalUpgrades -= targetUpgrade;

				if(mIsSelected)
				{
					UpdateUIInf(mLastIndUpgrade);
				}
			}
		}
		
		//special infrastructure (low priority stuff)
		targetUpgrade = 0;
		while(a_TotalUpgrades > 0 && DecideNextSpecialUpgrade(targetUpgrade) != Infrastructure::MAXVAL)
		{
			mGrowthTarget += max(targetUpgrade - a_TotalUpgrades, 0);
			if(targetUpgrade > a_TotalUpgrades)
			{
				//not enough to fully upgrade
				targetUpgrade = a_TotalUpgrades;
			}
				
			if(targetUpgrade > 0)
			{
				//std::cout << targetUpgrade << " " << GetInfrastructureStringname(mLastSpecialUpgrade) << " upgrades." << std::endl;
				mInfrastructureLevel[mLastSpecialUpgrade] += targetUpgrade;
				a_TotalUpgrades -= targetUpgrade;

				if(mIsSelected)
				{
					//GameManager::UpdateDisplayedInf(mLastSpecialUpgrade, mInfrastructureLevel[mLastSpecialUpgrade]);
					UpdateUIInf(mLastSpecialUpgrade);
				}
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
		//GameManager::UpdateSelectedInfrastructure(m_TotalInfrastructureLevel);
	}
}

void HabitableObject::DowngradeInfrastructure(float a_TotalDowngrades)
{
	//
	RecalculateInfrastructureLevel();
	if(mIsSelected)
	{
		//GameManager::UpdateSelectedInfrastructure(m_TotalInfrastructureLevel);
	}
}
