#ifndef TRADERS_HPP
#define TRADERS_HPP

#include "DisplayableObject.hpp"

class HabitableObject;
#include <SFML\System\Vector2.hpp>
#include "TimeRate.h"
#include "Resources.h"

class Trader
:	public DisplayableObject
{
public:
	Trader(DisplayableObject* a_pStartLocation);
	void JumpToLocation(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords = sf::Vector2f());
	virtual void GenerateContents();
	//
	void Update(TimeRate a_CurTimeRate, float a_DeltaT);
	std::string GetName();
	//
private:
	void HourlyUpdate(int a_Quantity);
	void DailyUpdate(int a_Quantity);
	void WeeklyUpdate(int a_Quantity);
	void MonthlyUpdate(int a_Quantity);
	float m_tLeftMainUpdate;
	void ArrivedAtDestination();
	//
	//DisplayableObject* m_pCurrentLocation;
	//sf::Vector2f m_CurrentCoords;
	//
	float m_Money;
	std::string m_Name;
	HabitableObject* m_pCurrentDestination;
	DisplayableObject* m_pCurrentDownwardTarget;
	void JumpToLocationMaintainHeading(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords = sf::Vector2f());
	//
	sf::Vector2f m_TargetCoords;
	sf::Vector2f m_MoveDir;
	float m_PercentTravelledThisLevel;
	float m_LastSqrdDist;
	void CalculateHeading();
	//
	//
	std::map<Resource::ResourceType, float> m_CargoHold;
	std::map<Resource::ResourceType, float> m_CargoQ;
	float m_TotalCargoSpace;
	float m_UsedCargoSpace;
};

#endif	//TRADERS_HPP