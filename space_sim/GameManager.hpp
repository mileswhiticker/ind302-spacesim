#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include "DisplayableObject.hpp"

class OrionSpur;
class Planet;
class DisplayableObject;
class Game;
namespace sf
{
	class Image;
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
	void ViewDisplayableObject(DisplayableObject* a_pDisplayObject);
	void UpOneLevel();
	//
private:
	GameManager();
	//
	//void ShowView(View a_NewView);
	void ClearCurView();
	OrionSpur* m_pOrionSpur;
	Game* m_pGameScene;
	//
	DisplayableObject::DisplayableType m_CurView;
	DisplayableObject* m_pCurViewedObject;
};

#endif	//GAME_MANAGER_HPP