#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <SFGUI\Image.hpp>

#include "DisplayableObject.hpp"
#include "Resources.h"
#include "TimeRate.h"
#include "HabitableObject.hpp"

class OrionSpur;
class Planet;
class DisplayableObject;
class HabitableObject;
class Game;
class Trader;
namespace sf
{
	class Image;
	class Sprite;
	class Texture;
};

typedef std::map<Infrastructure::InfrastructureType, float> IndustryWeightMap;
typedef std::pair<Infrastructure::InfrastructureType, float> IndustryWeightPair;

class GameManager
{
public:
	static Planet* GetHomePlanet();
	static void SetHomePlanet(Planet* a_pNewHomePlanet);
	//
	static GameManager& GetSingleton()
	{
		static GameManager instance;
		return instance;
	}
	
	//static void UpdateDisplayedResStore(Resource::ResourceType a_ResType, float a_Quantity, float a_Quality);
	//static void UpdateDisplayedResInf(Resource::ResourceType a_ResType, float a_InfLevel);
	//static void UpdateDisplayedInf(Infrastructure::InfrastructureType a_InfType, float a_InfLevel);
	//
	//static void UpdateSelectedInfrastructure(float a_NewInf);
	
	void Initialise(Game* a_pGameScene);
	void Uninitialise();
	void Update(float a_DeltaT);
	void HandleEvent(sf::Event& a_NewEvent);
	//
	static DisplayableObject::DisplayableType GetCurrentlyViewedType();
	static DisplayableObject* GetCurrentlyViewedObject();
	//
	void ViewDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickHabitableObject(HabitableObject* a_pHabObject);
	void UpOneLevel();
	//
	void AddHabitableObject(HabitableObject* a_pNewHabObject);
	//
	Game* GetGameScene();
	HabitableObject* GetSelectedHabObj();

	static float GetInfWeighting(HabitableObject::HabitableType a_MyHabType, Infrastructure::InfrastructureType a_MyInfType);
	std::map<HabitableObject::HabitableType, IndustryWeightMap> DefaultIndustryWeightingPerObject;
	//
	IndustryWeightMap PersonnelAllocationWeighting;
	//
	static std::vector<Planet*> GetValidDestinations();
	static void AddSettletPlanet(Planet* a_pNewColony);
	static void ShipChangeLevel(Trader* a_pTrader);
	static Planet* GetRandomTraderDestination(Trader* a_pTrader);
	//
	static float GetAveragePrice(Resource::ResourceType a_ResType);
	static float GetBasePrice(Resource::ResourceType a_ResType);
	static float GetMaxStoredGlobally(Resource::ResourceType a_ResType);
	//static Resource::ResourceType GetRandomLowPrice(HabitableObject& a_TargetPlanet);
	//static Planet* GetHighestPrice(Resource::ResourceType a_ResType);
	//
private:
	GameManager();
	//
	//void ShowView(View a_NewView);
	void ClearCurView();
	OrionSpur* m_pOrionSpur;
	Game* m_pGameScene;
	sfg::Image::Ptr m_pSelectCircle;
	//
	TimeRate m_CurTimeRate;
	std::vector<HabitableObject*> m_HabitableObjects;
	std::vector<Planet*> m_SettledPlanets;
	std::vector<Trader*> m_Traders;
	//
	//DisplayableObject::DisplayableType m_CurView;
	DisplayableObject* m_pCurViewedObject;
	DisplayableObject* m_pCurSelectedDispObject;
	HabitableObject* m_pCurSelectedHabObject;
	//
	float m_tLeftTimeTick;
	int mHours;
	int mDays;
	int mMonths;
	int mYears;
	//
	std::map<Resource::ResourceType, float> m_AveragePrices;
	std::map<Resource::ResourceType, float> m_BasePrices;
	std::map<Resource::ResourceType, float> m_MaxGloballyStored;
	std::map<Resource::ResourceType, HabitableObject*> m_MaxGlobalStorees;
	std::map<Resource::ResourceType, HabitableObject*> m_LowestGlobalPrices;
	void RecalculateAveragePrices();
};

#endif	//GAME_MANAGER_HPP