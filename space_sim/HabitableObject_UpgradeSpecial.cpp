#include "HabitableObject.hpp"

Infrastructure::InfrastructureType HabitableObject::DecideNextSpecialUpgrade(float& a_AmountToUpgrade)
{
	a_AmountToUpgrade = 0;
	while(!a_AmountToUpgrade)
	{
		switch(mLastSpecialUpgrade)
		{
		default:
			{
				//new cycle, do COMMERCIAL first
				//work out if we need new commercial buildings
				//todo: add a bonus to this if the colony is doing well financially (and in general?)
				float targetCommercial = COMMERCIAL_TO_RESIDENTIAL_RATIO * mInfrastructureLevel[Infrastructure::RESIDENTIAL];
				float commercialNeeded = targetCommercial - mInfrastructureLevel[Infrastructure::COMMERCIAL];
				if(commercialNeeded > 0)
				{
					a_AmountToUpgrade = commercialNeeded;
				}

				mLastSpecialUpgrade = Infrastructure::COMMERCIAL;
				break;
			}
		case(Infrastructure::COMMERCIAL):
			{
				//did commercial last cycle, do shipbuilding now
				//upgrade this if we have enough of a commercial base
				if(mInfrastructureLevel[Infrastructure::COMMERCIAL] >= MIN_COMMERCIAL_FOR_SHIPBUILDING)
				{
					float targetShipbuilding = SHIPBUILDING_TO_COMMERCIAL_RATIO * mInfrastructureLevel[Infrastructure::COMMERCIAL];
					float shipbuildingNeeded = targetShipbuilding - mInfrastructureLevel[Infrastructure::SHIP_PRODUCTION];
					if(shipbuildingNeeded > 0)
					{
						a_AmountToUpgrade = shipbuildingNeeded;
					}
				}

				mLastSpecialUpgrade = Infrastructure::SHIP_PRODUCTION;
				break;
			}
		case(Infrastructure::SHIP_PRODUCTION):
			{
				//did shipbuilding last cycle, we're finished this cycle
				mLastSpecialUpgrade = Infrastructure::MAXVAL;
				return mLastSpecialUpgrade;
			}
		}
	}
	return mLastSpecialUpgrade;
}
