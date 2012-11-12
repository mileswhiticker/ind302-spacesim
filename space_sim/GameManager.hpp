#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <SFGUI\Widget.hpp>

class Planet;
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
	enum View
	{
		ORIONSPUR,
		STELLARGROUP,
		STARSYSTEM,
		PLANET,
		//
		MAXVAL
	};
	void Initialise();
	void Uninitialise();
	//
private:
	GameManager();
	//
	void ShowView(View a_NewView);
	void ClearCurView();
	//
	View m_CurView;
	//
	std::vector<sfg::Widget::Ptr> m_ClickableObjects;
};

#endif	//GAME_MANAGER_HPP