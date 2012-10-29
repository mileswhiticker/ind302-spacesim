#ifndef SCENE_MAINMENU_HPP
#define SCENE_MAINMENU_HPP

#include "Scene.hpp"

class MainMenu
:	public Scene
{
public:
	MainMenu();
	//
	void LaunchGame();
	void About();
	void Quit();
	//
private:
	//
};

#endif	//SCENE_MAINMENU_HPP