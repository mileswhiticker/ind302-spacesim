#ifndef HABITABLE_OBJECT_HPP
#define HABITABLE_OBJECT_HPP

#include "DisplayableObject.hpp"
class StarSystem;
#include <map>
#include <string>
#include "Resources.hpp"
#include "Defines_Time.h"

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
	//
	float GetResNum(Resource::ResourceType a_ResType);
	float GetResQ(Resource::ResourceType a_ResType);
	//
	void Update(float a_DeltaT, TimeRate a_TimeRate);
	//
protected:
	void HourlyUpdate(bool a_PropogateUpward, int a_Quantity = 1);
	void DailyUpdate(bool a_PropogateUpward, int a_Quantity = 1);
	void WeeklyUpdate(bool a_PropogateUpward, int a_Quantity = 1);
	void MonthlyUpdate(bool a_PropogateUpward, int a_Quantity = 1);
	void YearlyUpdate(bool a_PropogateUpward, int a_Quantity = 1);
	//
	HabitableType mMyHabitableType;
	std::string mObjName;
	int mPopulation;
	float mInfrastructure;
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
	//
	std::map<Resource::ResourceType, float> m_PlanetResQ;
	std::map<Resource::ResourceType, float> m_PlanetResAbundance;
	//todo: atmospheric composition
	//
	StarSystem* m_pOrbitingStarSystem;
	HabitableObject* m_pOrbitingObject;

	int mCalculatedResourceSpace;
	std::map<Resource::ResourceType, float> m_StoredResNum;
	std::map<Resource::ResourceType, float> m_StoredResQ;
};

#endif	//HABITABLE_OBJECT_HPP