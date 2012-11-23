#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <SFGUI\Image.hpp>

#include "DisplayableObject.hpp"
#include "Resources.h"
#include "Defines_Time.h"

class OrionSpur;
class Planet;
class DisplayableObject;
class HabitableObject;
class Game;
namespace sf
{
	class Image;
	class Sprite;
	class Texture;
};

class GameManager
{
public:
	Planet* GetHomePlanet();
	void SetHomePlanet(Planet* a_pNewHomePlanet);
	//
	static GameManager& GetSingleton()
	{
		static GameManager instance;
		return instance;
	}
	//
	static void UpdateStoredResource(Resource::ResourceType a_ResType, float a_Quantity, float a_Quality);
	static void UpdateSelectedInfrastructure(float a_NewInf);
	//
	/*enum Viewable
	{
		ORIONSPUR,
		STARSYSTEM,
		STELLARGROUP,
		PLANET,
		//
		MAXVAL
	};*/
	void Initialise(Game* a_pGameScene);
	void Uninitialise();
	void GameUpdate(float a_DeltaT);
	//
	DisplayableObject::DisplayableType GetCurrentlyViewedType();
	void ViewDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickHabitableObject(HabitableObject* a_pHabObject);
	void UpOneLevel();
	//
	void AddHabitableObject(HabitableObject* a_pNewHabObject);
	//
	Game* GetGameScene();
	void HandleEvent(sf::Event& a_NewEvent);
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
	//
	//DisplayableObject::DisplayableType m_CurView;
	DisplayableObject* m_pCurViewedObject;
	DisplayableObject* m_pCurSelectedObject;
	//
	float m_tLeftTimeTick;
	int mHours;
	int mDays;
	int mMonths;
	int mYears;
};

#endif	//GAME_MANAGER_HPP