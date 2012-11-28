#ifndef SCENE_GAME_HPP
#define SCENE_GAME_HPP

#include <map>

#include "Scene.hpp"
#include "Resources.h"
#include "Industry.h"

#include <SFGUI\Button.hpp>
#include <SFGUI\Table.hpp>
#include <SFGUI\Label.hpp>
#include <SFGUI\Notebook.hpp>

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
	std::map<Resource::ResourceType, sfg::Label::Ptr> mResourceNameLabels;
	std::map<Infrastructure::InfrastructureType, sfg::Label::Ptr> mInfrastructureLabels;
	//
	void SetDate(std::string a_NewDate);
	void BottomPanelClick();
	//
private:
	sfg::Notebook::Ptr m_pBottomPanel;
	sfg::Notebook::Ptr m_pRightPanel;

	sfg::Table::Ptr m_pStatusTable;
	//
	sfg::Button::Ptr m_pMainMenuButton;
	sfg::Label::Ptr m_pTitleLabel;
	sfg::Label::Ptr m_pDateLabel;
	//
	sf::Texture* m_pBGTexture;
	sf::Sprite* m_pBGSprite;
	//
	HabitableObject* m_pCurSelect;
	//
public:
	void DisplayInf(HabitableObject* a_pNewSelect);
	//
	void DisplayPower(HabitableObject* a_pNewSelect);
	void DisplayAtmos(HabitableObject* a_pNewSelect);
	void DisplayStorage(HabitableObject* a_pNewSelect);
	void DisplayYearlyProd(HabitableObject* a_pNewSelect);
	void DisplayEmploy(HabitableObject* a_pNewSelect);
	void DisplayComm(HabitableObject* a_pNewSelect);
	void DisplayResidential(HabitableObject* a_pNewSelect);
	//
	void DisplayMining(HabitableObject* a_pNewSelect);
	void DisplayGasCollection(HabitableObject* a_pNewSelect);
	void DisplayWasteRec(HabitableObject* a_pNewSelect);
	void DisplayScrapRec(HabitableObject* a_pNewSelect);
	//
	void DisplayElectronic(HabitableObject* a_pNewSelect);
	void DisplayMaterials(HabitableObject* a_pNewSelect);
	void DisplayDomesticG(HabitableObject* a_pNewSelect);
	void DisplayLuxuryG(HabitableObject* a_pNewSelect);
	//
	void DisplayFood(HabitableObject* a_pNewSelect);
	void DisplayWater(HabitableObject* a_pNewSelect);
	void DisplayFuel(HabitableObject* a_pNewSelect);
	//
private:
	//---- BOTTOM PANEL ----//

	//object data
	sfg::Table::Ptr m_pObjectDataTable;
	//
	sfg::Label::Ptr m_pObjnameLabel;
	sfg::Label::Ptr m_pObjlocLabel;
	sfg::Label::Ptr m_pObjtypeLabel;
	sfg::Label::Ptr m_pObjinfLabel;
	//
	sfg::Label::Ptr m_pObjcoordsLabel;
	sfg::Label::Ptr m_pObjmassLabel;
	sfg::Label::Ptr m_pObjdiameterLabel;
	//empty
	//
	sfg::Label::Ptr m_pCarbLabel;
	sfg::Label::Ptr m_pSiliLabel;
	sfg::Label::Ptr m_pMetalLabel;
	sfg::Label::Ptr m_pWaterCLabel;
	//
	sfg::Label::Ptr m_pAtmosDensityLabel;
	sfg::Label::Ptr m_pHydroLabel;
	sfg::Label::Ptr m_pOxyLabel;
	//trace gases
	
	//colony data
	sfg::Table::Ptr m_pColonyTable;
	//
	sfg::Label::Ptr m_pPowerLabel;
	sfg::Label::Ptr m_pAtmosLabel;
	sfg::Label::Ptr m_pStorageLabel;
	//
	sfg::Label::Ptr m_pMonthlyFuelLabel;
	sfg::Label::Ptr m_pMonthlyOxyLabel;
	sfg::Label::Ptr m_pYearlyProdLabel;
	//
	sfg::Label::Ptr m_pObjpopLabel;
	sfg::Label::Ptr m_pEmployLabel;
	sfg::Label::Ptr m_pCommLabel;
	
	//raw materials
	sfg::Table::Ptr m_pRawResTable;
	//
	sfg::Label::Ptr m_pMiningInfLabel;
	sfg::Label::Ptr m_pResCarbLabel;
	sfg::Label::Ptr m_pResSiliLabel;
	sfg::Label::Ptr m_pResMetalLabel;
	//
	sfg::Label::Ptr m_pGasInfLabel;
	sfg::Label::Ptr m_pResOxyLabel;
	sfg::Label::Ptr m_pResHydroLabel;
	sfg::Label::Ptr m_pResWaterCLabel;
	//
	sfg::Label::Ptr m_pWasteInfLabel;
	sfg::Label::Ptr m_pResWasteLabel;
	sfg::Label::Ptr m_pScrapInfLabel;
	sfg::Label::Ptr m_pResScrapLabel;

	//produced goods
	sfg::Table::Ptr m_pFinishedResTable;
	//
	sfg::Label::Ptr m_pElecInfLabel;
	sfg::Label::Ptr m_pResCompLabel;
	sfg::Label::Ptr m_pResCircLabel;
	//
	sfg::Label::Ptr m_pMatInfLabel;
	sfg::Label::Ptr m_pResSheetLabel;
	sfg::Label::Ptr m_pResGirderLabel;
	//
	sfg::Label::Ptr m_pDomGInfLabel;
	sfg::Label::Ptr m_pResDomGLabel;
	sfg::Label::Ptr m_pLuxGInfLabel;
	sfg::Label::Ptr m_pResLuxGLabel;

	//consumable goods
	sfg::Table::Ptr m_pConsumableResTable;
	//
	sfg::Label::Ptr m_pFoodInfLabel;
	sfg::Label::Ptr m_pResFoodLabel;
	sfg::Label::Ptr m_pSoilLabel;
	//
	sfg::Label::Ptr m_pFuelInfLabel;
	sfg::Label::Ptr m_pResFuelLabel;
	//
	sfg::Label::Ptr m_pWaterInfLabel;
	sfg::Label::Ptr m_pResWaterLabel;
	
	//ship production
	sfg::Table::Ptr m_pShipProdTable;
	//
	
	//docked traders
	sfg::Table::Ptr m_pDockedTradersTable;
	//
};

#endif SCENE_GAME_HPP