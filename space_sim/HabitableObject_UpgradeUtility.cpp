#include "HabitableObject.hpp"

Infrastructure::InfrastructureType HabitableObject::DecideNextUtilUpgrade(float& a_AmountToUpgrade)
{
	a_AmountToUpgrade = 0;
	while(!a_AmountToUpgrade)
	{
		switch(mLastUtilUpgrade)
		{
		default:
			{
				//new cycle, do storage first
				RecalculateStorageNeeded();
				if(mTargetStorageSpace > mInfrastructureLevel[Infrastructure::STORAGE])
				{
					a_AmountToUpgrade = mTargetStorageSpace - mInfrastructureLevel[Infrastructure::STORAGE];
				}
				mLastUtilUpgrade = Infrastructure::STORAGE;
				break;
			}
		case(Infrastructure::STORAGE):
			{
				//did residential last cycle, do docking now
				float target = mTargetStorageSpace * DOCKING_PER_STORE;
				if(target > mInfrastructureLevel[Infrastructure::DOCKING])
				{
					a_AmountToUpgrade = target - mInfrastructureLevel[Infrastructure::DOCKING];
				}
				mLastUtilUpgrade = Infrastructure::DOCKING;
				break;
			}
		case(Infrastructure::DOCKING):
			{
				//did DOCKING last cycle, we're finished this cycle
				mLastUtilUpgrade = Infrastructure::MAXVAL;
				return mLastUtilUpgrade;
			}
		}
	}
	return mLastUtilUpgrade;
}
