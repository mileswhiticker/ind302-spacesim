#ifndef SCENE_GAME_HPP
#define SCENE_GAME_HPP

#include <map>

#include "Scene.hpp"
#include "Resources.hpp"

#include <SFGUI\Button.hpp>
#include <SFGUI\Table.hpp>
#include <SFGUI\Label.hpp>

class DisplayableObject;
class HabitableObject;
namespace sf
{
	class Sprite;
	class Texture;
};

class Game
:	public Scene
{
public:
	Game();
	//
	void UpOneLevel();
	void ChangeView(DisplayableObject* a_pNewFocus);
	void SelectObject(HabitableObject* a_pNewSelect);
	//
	std::map<Resource::ResourceType, sfg::Label::Ptr> mResourceValueLabels;
	//
private:
	std::map<Resource::ResourceType, sfg::Label::Ptr> mResourceNameLabels;
	//
	sfg::Button::Ptr m_pMainMenuButton;
	sfg::Table::Ptr m_pStatusTable;
	sfg::Label::Ptr m_pTitleLabel;
	//
	sf::Texture* m_pBGTexture;
	sf::Sprite* m_pBGSprite;

	//resource storage data
	sfg::Table::Ptr m_pRawResStoreTable;
	sfg::Table::Ptr m_pFinishedResStoreTable;

	//object data
	sfg::Table::Ptr m_pObjectDataTable;
	//
	sfg::Label::Ptr m_pObjnameLabel;
	sfg::Label::Ptr m_pObjtypeLabel;
	sfg::Label::Ptr m_pObjpopLabel;
	sfg::Label::Ptr m_pObjcoordsLabel;
	sfg::Label::Ptr m_pObjmassLabel;
	sfg::Label::Ptr m_pObjdiameterLabel;
	//
	sfg::Label::Ptr m_pAtmosDensityLabel;
	sfg::Label::Ptr m_pAtmosCompPlaceholderLabel;
	//
	sfg::Label::Ptr m_pCarbNumLabel;
	sfg::Label::Ptr m_pSiliNumLabel;
	sfg::Label::Ptr m_pMetalNumLabel;
	sfg::Label::Ptr m_pHydroNumLabel;
	sfg::Label::Ptr m_pCarbQLabel;
	sfg::Label::Ptr m_pSiliQLabel;
	sfg::Label::Ptr m_pMetalQLabel;
	sfg::Label::Ptr m_pHydroQLabel;
};

#endif SCENE_GAME_HPP