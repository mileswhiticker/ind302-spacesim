#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include "DisplayableObject.hpp"
#include <SFGUI\Image.hpp>

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
	static Planet* GetHomePlanet();
	static void SetHomePlanet(Planet* a_pNewHomePlanet);
	//
	static GameManager& GetSingleton()
	{
		static GameManager instance;
		return instance;
	}
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
	//
	DisplayableObject::DisplayableType GetCurrentlyViewedType();
	void ViewDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickDisplayableObject(DisplayableObject* a_pDisplayObject);
	void ClickHabitableObject(HabitableObject* a_pHabObject);
	void UpOneLevel();
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
	//DisplayableObject::DisplayableType m_CurView;
	DisplayableObject* m_pCurViewedObject;
	DisplayableObject* m_pCurSelectedObject;
};

#endif	//GAME_MANAGER_HPP