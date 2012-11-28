#ifndef HABITABLE_OBJECT_HPP
#define HABITABLE_OBJECT_HPP

#include "DisplayableObject.hpp"
class StarSystem;
#include <map>
#include <string>

#include "Industry.h"
#include "Resources.h"
#include "Defines_Time.h"

#define UPWARD 1
#define DOWNWARD 2

//abstract base class for all colonisable entities in space (including space stations)
class HabitableObject
:	public DisplayableObject
{
public:
	enum HabitableType
	{
		INVALID = 0,
		STAR,
		//
		PLANET_DEAD,
		PLANET_TERRAN,
		PLANET_ICE,
		PLANET_GASGIANT,
		//
		ASTEROID_CARBONACEOUS,
		ASTEROID_SILICACEOUS,
		ASTEROID_METALLIC,
		ASTEROID_BELT,
		//
		SPACESTATION,
		//
		MAXVAL
	};
	HabitableObject(HabitableType a_MyType, StarSystem* a_pStarSystem);
	virtual ~HabitableObject()=0;
	//
	StarSystem* GetOrbitingStarSystem();
	HabitableObject* GetOrbitingObject();
	HabitableType GetHabitableType();
	//
	//virtual void SelectThis();
	//virtual void UnselectThis();
	//
	std::string GetName();
	std::string GetCoordsString();
	float ObjectMass();
	int Population();
	float Diameter();
	float AtmosDensity();
	virtual void OnClick();

	float GetInfrastructureLevel();
	float GetInfrastructureLevel(Infrastructure::InfrastructureType a_InfType);
	float GetUsedStorageSpace();
	float GetMonthlyFuelUsage();
	float GetMonthlyOxyUsage();
	float GetYearlyProduction();
	int GetNumJobs();
	float GetSoilQ();
	float GetSoilAmount();
	//
	float GetPersonnelMultiplier(Infrastructure::InfrastructureType a_InfType);
	//
	float GetPlanetResNum(Resource::ResourceType a_ResType);
	float GetPlanetResQ(Resource::ResourceType a_ResType);
	float GetStoredResNum(Resource::ResourceType a_ResType);
	float GetStoredResQ(Resource::ResourceType a_ResType);

	void Update(float a_DeltaT, TimeRate a_TimeRate);
	//
protected:
	void HourlyUpdate(int a_PropogationDir, int a_Quantity = 1);
	void DailyUpdate(int a_PropogationDir, int a_Quantity = 1);
	void WeeklyUpdate(int a_PropogationDir, int a_Quantity = 1);
	void MonthlyUpdate(int a_PropogationDir, int a_Quantity = 1);
	void YearlyUpdate(int a_PropogationDir, int a_Quantity = 1);
	void UpdateUIRes(Resource::ResourceType a_ResType);
	void UpdateUIInf(Infrastructure::InfrastructureType a_InfType);
	//
	HabitableType mMyHabitableType;
	std::string mObjName;
	int mPopulation;
	float mObjectMass;				//absolute mass (assume constant density)
	float mObjectDiameter;			//absolute diameter (assume perfectly spherical)
	float mAtmosDensity;			//liquid volume per meter^3
	//
	float m_tLeftMainUpdate;
	int m_NumLeftDailyUpdate;
	int m_NumLeftWeeklyUpdate;
	int m_NumLeftMonthlyUpdate;
	int m_NumLeftYearlyUpdate;
	//
	void GenerateData();
	bool mGenerated;
	//
	std::map<Resource::ResourceType, float> m_PlanetResQ;
	std::map<Resource::ResourceType, float> m_PlanetResAbundance;
	//todo: atmospheric composition
	//
	StarSystem* m_pOrbitingStarSystem;
	HabitableObject* m_pOrbitingObject;

	void UpgradeInfrastructure(float a_TotalUpgrades);
	void DowngradeInfrastructure(float a_TotalDowngrades);
	bool mLastUpgradeSuccessful;
	//
	void RecalculateInfrastructureLevel();
	void RecalculateStorageNeeded();
	void RecalculateTargetFoodProduction();
	void RecalculateUsedStorage();
	
	void AddResources(Resource::ResourceType a_NewType, float a_Quality, float a_Quantity);
	void RemoveResources(Resource::ResourceType a_NewType, float a_Quantity);
	//
	float mCalculatedResourceSpace;
	float mUsedStorageSpace;
	float m_TotalInfrastructureLevel;
	float mTargetStorageSpace;
	float mTargetFoodProduction;
	//
	float mCriticalGrowthTarget;
	float mGrowthTarget;
	//
	float mStoredSoilForFarming;
	float mQSoilForFarming;

	std::map<Resource::ResourceType, float> m_StoredResNum;
	std::map<Resource::ResourceType, float> m_StoredResQ;
	std::map<Infrastructure::InfrastructureType, float> mInfrastructureLevel;

	Infrastructure::InfrastructureType DecideNextCriticalUpgrade(float& a_AmountToUpgrade);
	Infrastructure::InfrastructureType mLastCriticalUpgrade;
	//
	Infrastructure::InfrastructureType DecideNextUtilUpgrade(float& a_AmountToUpgrade);
	Infrastructure::InfrastructureType mLastUtilUpgrade;
	//
	Infrastructure::InfrastructureType DecideNextIndUpgrade(float& a_AmountToUpgrade);
	Infrastructure::InfrastructureType mLastIndUpgrade;
	//
	Infrastructure::InfrastructureType DecideNextSpecialUpgrade(float& a_AmountToUpgrade);
	Infrastructure::InfrastructureType mLastSpecialUpgrade;

	void AllocateNewPersonnel(int a_NumNewPersonnel);
	void ReallocateAllPersonnel();
	//
	std::map<Infrastructure::InfrastructureType, int> m_InfrastructureAllocatedPersonnel;
	int m_ConstructionAllocatedPersonnel;
	int m_UnallocatedPersonnel;
	void RecalculateWorkersNeeded();
	int mTotalWorkersNeeded;
};

#endif	//HABITABLE_OBJECT_HPP