#ifndef SCENE_GAME_HPP
#define SCENE_GAME_HPP

#include "Scene.hpp"
#include <SFGUI\Button.hpp>
#include <SFGUI\Table.hpp>
#include <SFGUI\Label.hpp>

class DisplayableObject;

class Game
:	public Scene
{
public:
	Game();
	//
	void UpOneLevel();
	void ChangeView(DisplayableObject* a_pNewFocus);
	//
private:
	sfg::Button::Ptr m_pMainMenuButton;
	sfg::Table::Ptr m_pStatusTable;
	sfg::Label::Ptr m_pTitleLabel;
	//
};

#endif SCENE_GAME_HPP