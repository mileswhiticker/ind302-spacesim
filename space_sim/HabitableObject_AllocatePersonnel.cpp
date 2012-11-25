#include "HabitableObject.hpp"

#include "GameManager.hpp"

void HabitableObject::AllocateNewPersonnel(int a_NumNewPersonnel)
{
	//
}

void HabitableObject::ReallocateAllPersonnel()
{
	//10% of the population to work on construction
	int unassignedPopulation = mPopulation;
	m_ConstructionAllocatedPersonnel = int(0.1f * mPopulation);
	if(!m_ConstructionAllocatedPersonnel && mPopulation)
		m_ConstructionAllocatedPersonnel = 1;
	unassignedPopulation -= m_ConstructionAllocatedPersonnel;

	RecalculateWorkersNeeded();
	int& derp = mTotalWorkersNeeded;

	//we have enough, and there's probably a few unemployed
	for(auto it = m_InfrastructureAllocatedPersonnel.begin(); it != m_InfrastructureAllocatedPersonnel.end(); ++it)
	{
		int workersNeeded = int(it->second * GameManager::GetSingleton().PersonnelAllocationWeighting[it->first]);
		//
		if(!workersNeeded && mInfrastructureLevel[it->first])
			workersNeeded = 1;
		if(workersNeeded > unassignedPopulation)
			workersNeeded = unassignedPopulation;
		//
		unassignedPopulation -= workersNeeded;
		it->second = workersNeeded;
	}
}

//std::map<Infrastructure::InfrastructureType, int> m_InfrastructureAllocatedPersonnel;
//int m_ConstructionAllocatedPersonnel;
void HabitableObject::RecalculateWorkersNeeded()
{
	//work out how many workers we need
	mTotalWorkersNeeded = 1;
	for(auto it = mInfrastructureLevel.begin(); it != mInfrastructureLevel.end(); ++it)
	{
		int workersNeeded = int(it->second * GameManager::GetSingleton().PersonnelAllocationWeighting[it->first]);
		if(!workersNeeded)
			workersNeeded = 1;
		mTotalWorkersNeeded += workersNeeded;
	}
}
