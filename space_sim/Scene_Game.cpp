#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "SceneManager.hpp"
#include "GameManager.hpp"

#include "HabitableObject.hpp"

#include "Num2StringHelper.h"
#include "GameHelpers.hpp"
#include "MathHelpers.h"

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <SFGUI\Notebook.hpp>

Game::Game()
:	Scene()
,	m_pBGTexture(NULL)
,	m_pBGSprite(NULL)
,	m_pCurSelect(NULL)
{
	m_SceneType = SIM;
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	sf::FloatRect allocation;

	//right panel
	m_pRightPanel = sfg::Notebook::Create();
	allocation.top = 0;
	allocation.height = 5 * windowDims.y / 6;
	allocation.left = 5 * windowDims.x / 6;
	allocation.width = windowDims.x / 6;
	m_pRightPanel->SetAllocation(allocation);
	m_pRightPanel->SetScrollable(true);
	//
	sfg::Table::Ptr pTable1 = sfg::Table::Create();
	pTable1->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable1->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable1->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(2,0,1,1));
	m_pRightPanel->AppendPage(pTable1, sfg::Label::Create("Panel1"));
	//
	sfg::Table::Ptr pTable2 = sfg::Table::Create();
	pTable2->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable2->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(0,1,1,1));
	pTable2->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,2,1,1));
	m_pRightPanel->AppendPage(pTable2, sfg::Label::Create("Panel2"));
	//
	/*sfg::Table::Ptr pTable3 = sfg::Table::Create();
	pTable3->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,1,1,1));
	pRightPanel->AppendPage(pTable3, sfg::Label::Create("Panel3"));*/
	//
	m_pWidgets.push_back(m_pRightPanel);

	//bottom panel
	m_pBottomPanel = sfg::Notebook::Create();
	allocation.top = 5 * windowDims.y / 6;
	allocation.height = windowDims.y / 6;
	allocation.left = 0;
	allocation.width = 5 * windowDims.x / 6;
	m_pBottomPanel->SetAllocation(allocation);
	m_pBottomPanel->GetSignal(sfg::Widget::OnLeftClick).Connect(&Game::BottomPanelClick, this);
	m_pWidgets.push_back(m_pBottomPanel);
	
	//planetary info
	m_pObjectDataTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pObjectDataTable, sfg::Label::Create("Object info"));
	m_pObjectDataTable->SetId("m_pObjectDataTable");
	//
	m_pObjnameLabel = sfg::Label::Create("Object name");
	m_pObjectDataTable->Attach(m_pObjnameLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pObjtypeLabel = sfg::Label::Create("Object type");
	m_pObjectDataTable->Attach(m_pObjtypeLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pObjlocLabel = sfg::Label::Create("Object location");
	m_pObjectDataTable->Attach(m_pObjlocLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	m_pObjinfLabel = sfg::Label::Create("total inf level");
	m_pObjectDataTable->Attach(m_pObjinfLabel, sf::Rect<sf::Uint32>(0,3,1,1));
	//
	m_pObjcoordsLabel = sfg::Label::Create("Object coords");
	m_pObjectDataTable->Attach(m_pObjcoordsLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pObjmassLabel = sfg::Label::Create("Object mass");
	m_pObjectDataTable->Attach(m_pObjmassLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	m_pObjdiameterLabel = sfg::Label::Create("Object diameter");
	m_pObjectDataTable->Attach(m_pObjdiameterLabel, sf::Rect<sf::Uint32>(1,2,1,1));
	//
	m_pCarbLabel = sfg::Label::Create("m_pCarbLabel");
	m_pObjectDataTable->Attach(m_pCarbLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pSiliLabel = sfg::Label::Create("m_pSiliLabel");
	m_pObjectDataTable->Attach(m_pSiliLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	m_pMetalLabel = sfg::Label::Create("m_pMetalLabel");
	m_pObjectDataTable->Attach(m_pMetalLabel, sf::Rect<sf::Uint32>(2,2,1,1));
	m_pWaterCLabel = sfg::Label::Create("m_pWaterCLabel");
	m_pObjectDataTable->Attach(m_pWaterCLabel, sf::Rect<sf::Uint32>(2,3,1,1));
	//
	m_pAtmosDensityLabel = sfg::Label::Create("m_pAtmosDensityLabel");
	m_pObjectDataTable->Attach(m_pAtmosDensityLabel, sf::Rect<sf::Uint32>(3,0,1,1));
	m_pHydroLabel = sfg::Label::Create("m_pHydroLabel");
	m_pObjectDataTable->Attach(m_pHydroLabel, sf::Rect<sf::Uint32>(3,1,1,1));
	m_pOxyLabel = sfg::Label::Create("m_pOxyLabel");
	m_pObjectDataTable->Attach(m_pOxyLabel, sf::Rect<sf::Uint32>(3,2,1,1));
	m_pObjectDataTable->Attach(sfg::Label::Create("Miscellaneous trace gases"), sf::Rect<sf::Uint32>(3,3,1,1));
	
	//colony data
	m_pColonyTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pColonyTable, sfg::Label::Create("Colony info"));
	m_pColonyTable->SetId("m_pColonyTable");
	//
	m_pPowerLabel = sfg::Label::Create("m_pPowerLabel");
	m_pColonyTable->Attach(m_pPowerLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pAtmosLabel = sfg::Label::Create("m_pAtmosLabel");
	m_pColonyTable->Attach(m_pAtmosLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pStorageLabel = sfg::Label::Create("m_pStorageLabel");
	m_pColonyTable->Attach(m_pStorageLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	//
	m_pMonthlyFuelLabel = sfg::Label::Create("m_pMonthlyFuelLabel");
	m_pColonyTable->Attach(m_pMonthlyFuelLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pMonthlyOxyLabel = sfg::Label::Create("m_pMonthlyOxyLabel");
	m_pColonyTable->Attach(m_pMonthlyOxyLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	m_pYearlyProdLabel = sfg::Label::Create("m_pYearlyProdLabel");
	m_pColonyTable->Attach(m_pYearlyProdLabel, sf::Rect<sf::Uint32>(1,2,1,1));
	//
	m_pObjpopLabel = sfg::Label::Create("m_pObjpopLabel");
	m_pColonyTable->Attach(m_pObjpopLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pEmployLabel = sfg::Label::Create("m_pEmployLabel");
	m_pColonyTable->Attach(m_pEmployLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	m_pCommLabel = sfg::Label::Create("m_pCommLabel");
	m_pColonyTable->Attach(m_pCommLabel, sf::Rect<sf::Uint32>(2,2,1,1));

	//raw materials
	m_pRawResTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pRawResTable, sfg::Label::Create("Raw Materials"));
	m_pRawResTable->SetId("m_pRawResTable");
	//
	m_pMiningInfLabel = sfg::Label::Create("m_pMiningInfLabel");
	m_pRawResTable->Attach(m_pMiningInfLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pResCarbLabel = sfg::Label::Create("m_pResCarbLabel");
	m_pRawResTable->Attach(m_pResCarbLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pResSiliLabel = sfg::Label::Create("m_pResSiliLabel");
	m_pRawResTable->Attach(m_pResSiliLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	m_pResMetalLabel = sfg::Label::Create("m_pResMetalLabel");
	m_pRawResTable->Attach(m_pResMetalLabel, sf::Rect<sf::Uint32>(0,3,1,1));
	//
	m_pGasInfLabel = sfg::Label::Create("m_pGasInfLabel");
	m_pRawResTable->Attach(m_pGasInfLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pResOxyLabel = sfg::Label::Create("m_pResOxyLabel");
	m_pRawResTable->Attach(m_pResOxyLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	m_pResHydroLabel = sfg::Label::Create("m_pResHydroLabel");
	m_pRawResTable->Attach(m_pResHydroLabel, sf::Rect<sf::Uint32>(1,2,1,1));
	m_pResWaterCLabel = sfg::Label::Create("m_pResWaterCLabel");
	m_pRawResTable->Attach(m_pResWaterCLabel, sf::Rect<sf::Uint32>(1,3,1,1));
	//
	m_pWasteInfLabel = sfg::Label::Create("m_pWasteInfLabel");
	m_pRawResTable->Attach(m_pWasteInfLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pResWasteLabel = sfg::Label::Create("m_pResWasteLabel");
	m_pRawResTable->Attach(m_pResWasteLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	m_pScrapInfLabel = sfg::Label::Create("m_pScrapInfLabel");
	m_pRawResTable->Attach(m_pScrapInfLabel, sf::Rect<sf::Uint32>(2,2,1,1));
	m_pResScrapLabel = sfg::Label::Create("m_pResScrapLabel");
	m_pRawResTable->Attach(m_pResScrapLabel, sf::Rect<sf::Uint32>(2,3,1,1));
	
	//produced goods
	m_pFinishedResTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pFinishedResTable, sfg::Label::Create("Finished Goods"));
	m_pFinishedResTable->SetId("m_pFinishedResTable");
	//
	m_pElecInfLabel = sfg::Label::Create("m_pElecInfLabel");
	m_pFinishedResTable->Attach(m_pElecInfLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pResCompLabel = sfg::Label::Create("m_pResCompLabel");
	m_pFinishedResTable->Attach(m_pResCompLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pResCircLabel = sfg::Label::Create("m_pResCircLabel");
	m_pFinishedResTable->Attach(m_pResCircLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	//
	m_pMatInfLabel = sfg::Label::Create("m_pMatInfLabel");
	m_pFinishedResTable->Attach(m_pMatInfLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pResSheetLabel = sfg::Label::Create("m_pResSheetLabel");
	m_pFinishedResTable->Attach(m_pResSheetLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	m_pResGirderLabel = sfg::Label::Create("m_pResGirderLabel");
	m_pFinishedResTable->Attach(m_pResGirderLabel, sf::Rect<sf::Uint32>(1,2,1,1));
	//
	m_pDomGInfLabel = sfg::Label::Create("m_pDomGInfLabel");
	m_pFinishedResTable->Attach(m_pDomGInfLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pResDomGLabel = sfg::Label::Create("m_pResDomGLabel");
	m_pFinishedResTable->Attach(m_pResDomGLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	m_pLuxGInfLabel = sfg::Label::Create("m_pLuxGInfLabel");
	m_pFinishedResTable->Attach(m_pLuxGInfLabel, sf::Rect<sf::Uint32>(2,2,1,1));
	m_pResLuxGLabel = sfg::Label::Create("m_pResLuxGLabel");
	m_pFinishedResTable->Attach(m_pResLuxGLabel, sf::Rect<sf::Uint32>(2,3,1,1));
	
	//consumables
	m_pConsumableResTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pConsumableResTable, sfg::Label::Create("Consumable Goods"));
	m_pConsumableResTable->SetId("m_pConsumableResTable");
	//
	m_pFoodInfLabel = sfg::Label::Create("m_pFoodInfLabel");
	m_pConsumableResTable->Attach(m_pFoodInfLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pResFoodLabel = sfg::Label::Create("m_pResFoodLabel");
	m_pConsumableResTable->Attach(m_pResFoodLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pSoilLabel = sfg::Label::Create("m_pSoilLabel");
	m_pConsumableResTable->Attach(m_pSoilLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	//
	m_pFuelInfLabel = sfg::Label::Create("m_pFuelInfLabel");
	m_pConsumableResTable->Attach(m_pFuelInfLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pResFuelLabel = sfg::Label::Create("m_pResFuelLabel");
	m_pConsumableResTable->Attach(m_pResFuelLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	//
	m_pWaterInfLabel = sfg::Label::Create("m_pWaterInfLabel");
	m_pConsumableResTable->Attach(m_pWaterInfLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pResWaterLabel = sfg::Label::Create("m_pResWaterLabel");
	m_pConsumableResTable->Attach(m_pResWaterLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	
	//ship production
	m_pShipProdTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pShipProdTable, sfg::Label::Create("Ship production"));
	m_pShipProdTable->SetId("m_pShipProdTable");
	//todo
	
	//docked traders
	m_pDockedTradersTable = sfg::Table::Create();
	m_pBottomPanel->AppendPage(m_pDockedTradersTable, sfg::Label::Create("Docked traders"));
	m_pShipProdTable->SetId("m_pDockedTradersTable");
	//todo

	//bottom right status panel
	m_pStatusTable = sfg::Table::Create();
	allocation.top = 5 * windowDims.y / 6;
	allocation.height = windowDims.y / 6;
	allocation.left = 5 * windowDims.x / 6;
	allocation.width = windowDims.x / 6;
	m_pDateLabel = sfg::Label::Create("The current date is X/Y/ZWVU");
	m_pStatusTable->Attach(m_pDateLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pTitleLabel = sfg::Label::Create("Orion Spur");
	m_pStatusTable->Attach(m_pTitleLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pStatusTable->SetAllocation(allocation);
	m_pWidgets.push_back(m_pStatusTable);
	
	//return to main menu button
	m_pMainMenuButton = sfg::Button::Create("Main Menu");
	m_pWidgets.push_back(m_pMainMenuButton);
	m_pMainMenuButton->SetPosition(sf::Vector2f(0, 0));
	m_pMainMenuButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&Game::UpOneLevel, this);
	
	//background
	m_pBGTexture = new sf::Texture();
	m_pBGTexture->loadFromFile("../media/orionspur_bg.png");
	m_pTextures.push_back(m_pBGTexture);
	
	windowDims.x *= 5.f/6.f;
	windowDims.y *= 5.f/6.f;

	m_pBGSprite = new sf::Sprite(*m_pBGTexture);
	sf::Vector2u texSize = m_pBGTexture->getSize();
	sf::Vector2f newScale(windowDims.y / texSize.y, windowDims.y / texSize.y);
	m_pBGSprite->setScale(newScale);
	m_pSprites.push_back(m_pBGSprite);

	Initialise();
	GameManager::GetSingleton().Initialise(this);
}

void Game::UpOneLevel()
{
	GameManager::GetSingleton().UpOneLevel();
}

void Game::ChangeView(DisplayableObject* a_pNewFocus)
{
	if(!a_pNewFocus)
		return;

	if(a_pNewFocus->GetParent())
		m_pMainMenuButton->SetLabel(GetDisplayStringname(a_pNewFocus->GetParent()->GetDisplayableType()));
	else
		m_pMainMenuButton->SetLabel("Main Menu");
	m_pTitleLabel->SetText( GetDisplayStringname(a_pNewFocus->GetDisplayableType()) );
	
	//
	m_pBGTexture->loadFromFile(a_pNewFocus->GetBGName());
}

void Game::SelectObject(HabitableObject* a_pNewSelect)
{
	m_pCurSelect = a_pNewSelect;

	//OBJECT INFO
	m_pObjnameLabel->SetText(a_pNewSelect->GetName());
	m_pObjtypeLabel->SetText(GetHabitableStringname(a_pNewSelect->GetHabitableType()));
	m_pObjlocLabel->SetText("obj location");
	m_pObjinfLabel->SetText("Total infrastructure: " + num2string( round(a_pNewSelect->GetInfrastructureLevel(), 2) ));
	//
	m_pObjcoordsLabel->SetText("Coords: " + a_pNewSelect->GetCoordsString());
	m_pObjmassLabel->SetText("Mass: " + num2string(a_pNewSelect->ObjectMass()));
	m_pObjdiameterLabel->SetText("Diameter: " + num2string(a_pNewSelect->Diameter()));
	//
	m_pCarbLabel->SetText("Carbon matter: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::CARBONACEOUS), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::CARBONACEOUS), 2)) + ")");
	m_pSiliLabel->SetText("Silicon matter: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::SILICACEOUS), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::SILICACEOUS), 2)) + ")");
	m_pMetalLabel->SetText("Metallic matter: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::METALLIC), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::METALLIC), 2)) + ")");
	m_pWaterCLabel->SetText("Water: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::WATERCRYSTALS), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::WATERCRYSTALS), 2)) + ")");
	//
	m_pAtmosDensityLabel->SetText("Atmo density: " + num2string( round(a_pNewSelect->AtmosDensity(), 2)));
	m_pOxyLabel->SetText("Oxygen: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::OXYGEN), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::OXYGEN), 2)) + ")");
	m_pHydroLabel->SetText("Hydrogen: " + num2string( round(a_pNewSelect->GetPlanetResNum(Resource::HYDROGEN), 2)) + " (" + num2string( round(a_pNewSelect->GetPlanetResQ(Resource::HYDROGEN), 2)) + ")");

	//COLONY DATA
	m_pPowerLabel->SetText("Power generation: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::POWER_GENERATION), 2)) );
	if(a_pNewSelect->GetHabitableType() == HabitableObject::PLANET_TERRAN)
	{
		m_pAtmosLabel->SetText("Atmos circulation: NA");
		m_pMonthlyOxyLabel->SetText("NA oxy/month");
	}
	else
	{
		m_pAtmosLabel->SetText("Atmos circulation: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::ATMOSPHERICS), 2)) );
		m_pMonthlyOxyLabel->SetText(num2string(round(a_pNewSelect->GetMonthlyOxyUsage(), 2)) + " oxy/month");
	}
	if(a_pNewSelect->GetInfrastructureLevel(Infrastructure::STORAGE))
	{
		m_pStorageLabel->SetText("Storage: " + num2string(round(a_pNewSelect->GetUsedStorageSpace(), 2)) + " (" + num2string(100 * round( a_pNewSelect->GetUsedStorageSpace() / (a_pNewSelect->GetInfrastructureLevel(Infrastructure::STORAGE) * SPACE_PER_STORAGE), 2)) + "%)");
	}
	else
	{
		m_pStorageLabel->SetText("Storage: " + num2string(round(a_pNewSelect->GetUsedStorageSpace(), 2)) + " (NA%)");
	}
	//
	//oxy consumption is calculated above
	m_pMonthlyFuelLabel->SetText(num2string(round(a_pNewSelect->GetMonthlyFuelUsage(), 0)) + " fuel/month");
	m_pYearlyProdLabel->SetText("Yearly production: " + num2string(round(a_pNewSelect->GetYearlyProduction(), 0)));
	//
	if(a_pNewSelect->GetInfrastructureLevel(Infrastructure::RESIDENTIAL))
	{
		m_pObjpopLabel->SetText("Population: " + num2string(a_pNewSelect->Population()) + " (" + num2string(100 * round( a_pNewSelect->Population() / (a_pNewSelect->GetInfrastructureLevel(Infrastructure::RESIDENTIAL) * POP_PER_RESIDENTIAL), 2)) + "%)");
	}
	else
	{
		m_pObjpopLabel->SetText("Population: " + num2string(a_pNewSelect->Population()) + " (NA%)");
	}
	if(!a_pNewSelect->GetNumJobs() || !a_pNewSelect->Population())
		m_pEmployLabel->SetText("Jobs filled: NA%");
	else
		m_pEmployLabel->SetText("Jobs filled: " + num2string(100 * round(float(a_pNewSelect->Population()) / float(a_pNewSelect->GetNumJobs()), 2) ) + "%");
	m_pCommLabel->SetText("Commercial infrastructure: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::COMMERCIAL), 2)) );

	//RAW MATERIALS
	m_pMiningInfLabel->SetText("Mining operations: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::MINING)));
	m_pResCarbLabel->SetText("Carbon matter: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::CARBONACEOUS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::CARBONACEOUS), 2)));
	m_pResSiliLabel->SetText("Silicon matter: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SILICACEOUS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SILICACEOUS), 2)));
	m_pResMetalLabel->SetText("Metal ore: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::METALLIC), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::METALLIC), 2)));
	//
	m_pGasInfLabel->SetText("Gas collection: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::GAS_PROCESSING)));
	m_pResOxyLabel->SetText("Oxygen: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::OXYGEN), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::OXYGEN), 2)));
	m_pResHydroLabel->SetText("Hydrogen: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::HYDROGEN), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::HYDROGEN), 2)));
	m_pResWaterCLabel->SetText("H20: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::WATERCRYSTALS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::WATERCRYSTALS), 2)));
	//
	m_pWasteInfLabel->SetText("Waste recycling: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::WASTE_RECYCLING)));
	m_pResWasteLabel->SetText("Organic waste: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::ORGANICWASTE), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::ORGANICWASTE), 2)));
	m_pScrapInfLabel->SetText("Scrap recycling: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::SCRAP_RECYCLING)));
	m_pResScrapLabel->SetText("Scrap waste: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SCRAPWASTE), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SCRAPWASTE), 2)));

	//PRODUCED GOODS
	//
	m_pElecInfLabel->SetText("Electronics production: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::ELECTRONICS_PRODUCTION)));
	m_pResCompLabel->SetText("Circuitry: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::CIRCUITRY), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::CIRCUITRY), 2)));
	m_pResCircLabel->SetText("Components: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::COMPONENTS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::COMPONENTS), 2)));
	//
	m_pMatInfLabel->SetText("Materials production: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::MATERIALS_PRODUCTION)));
	m_pResSheetLabel->SetText("Sheet metal: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SHEETMETAL), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SHEETMETAL), 2)));
	m_pResGirderLabel->SetText("Girders: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::GIRDERS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::GIRDERS), 2)));
	//
	m_pDomGInfLabel->SetText("Domestic production: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::DOMESTICGOODS_PRODUCTION)));
	m_pResDomGLabel->SetText("Domestic goods: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::DOMESTICGOODS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::DOMESTICGOODS), 2)));
	m_pLuxGInfLabel->SetText("Luxury production: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::LUXURYGOODS_PRODUCTION)));
	m_pResLuxGLabel->SetText("Luxury goods: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::LUXURYGOODS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::LUXURYGOODS), 2)));

	//CONSUMABLE GOODS
	//
	m_pFoodInfLabel->SetText("Farming: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING)));
	m_pResFoodLabel->SetText("Food: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::FOOD), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::FOOD), 2)));
	if(!a_pNewSelect->GetSoilAmount() || !a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING))
	{
		m_pSoilLabel->SetText("Soil: 0% 0Q");
	}
	else
	{
		m_pSoilLabel->SetText("Soil: " + num2string(100 * round(a_pNewSelect->GetSoilAmount() / a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING), 2)) + "% Q" + num2string(round(a_pNewSelect->GetSoilQ(), 2)));
	}
	//
	m_pFuelInfLabel->SetText("Fuel processing: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::FUEL_PROCESSING)));
	m_pResFuelLabel->SetText("Fuel: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::FUEL), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::FUEL), 2)));
	//
	m_pWaterInfLabel->SetText("Water purifying: " + num2string(a_pNewSelect->GetInfrastructureLevel(Infrastructure::WATER_PURIFICATION)));
	m_pResWaterLabel->SetText("Water: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::WATER), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::WATER), 2)));
}

void Game::SetDate(std::string a_NewDate)
{
	m_pDateLabel->SetText(a_NewDate);
}

void Game::DisplayPower(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pColonyTable"))
	{
		m_pPowerLabel->SetText("Power generation: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::POWER_GENERATION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::POWER_GENERATION), 2)) + "%employ)");
		m_pMonthlyFuelLabel->SetText(num2string(round(a_pNewSelect->GetMonthlyFuelUsage(), 0)) + " fuel/month");
	}
}

void Game::DisplayAtmos(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pColonyTable"))
	{
		if(a_pNewSelect->GetHabitableType() == HabitableObject::PLANET_TERRAN)
		{
			m_pAtmosLabel->SetText("Atmos circulation: NA");
			m_pMonthlyOxyLabel->SetText("NA oxy/month");
		}
		else
		{
			m_pAtmosLabel->SetText("Atmos circulation: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::ATMOSPHERICS), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::ATMOSPHERICS), 2)) + "%employ)" );
			m_pMonthlyOxyLabel->SetText(num2string(round(a_pNewSelect->GetMonthlyOxyUsage(), 2)) + " oxy/month");
		}
	}
}

void Game::DisplayResidential(HabitableObject* a_pNewSelect)
{
	if(a_pNewSelect->GetInfrastructureLevel(Infrastructure::RESIDENTIAL))
	{
		m_pObjpopLabel->SetText("Population: " + num2string(a_pNewSelect->Population()) + " (" + num2string(100 * round( a_pNewSelect->Population() / (a_pNewSelect->GetInfrastructureLevel(Infrastructure::RESIDENTIAL) * POP_PER_RESIDENTIAL), 2)) + "%housed) (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::RESIDENTIAL), 2)) + "%employ)");
	}
	else
	{
		m_pObjpopLabel->SetText("Population: " + num2string(a_pNewSelect->Population()) + " (NA%)");
	}
}

void Game::DisplayStorage(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pColonyTable"))
	{
		if(a_pNewSelect->GetInfrastructureLevel(Infrastructure::STORAGE))
		{
			m_pStorageLabel->SetText("Storage: " + num2string(round(a_pNewSelect->GetUsedStorageSpace(), 2)) + " (" + num2string(100 * round( a_pNewSelect->GetUsedStorageSpace() / (a_pNewSelect->GetInfrastructureLevel(Infrastructure::STORAGE) * SPACE_PER_STORAGE), 2)) + "%stored) (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::STORAGE), 2)) + "%employ)");
		}
		else
		{
			m_pStorageLabel->SetText("Storage: " + num2string(round(a_pNewSelect->GetUsedStorageSpace(), 2)) + " (NA%)");
		}
	}
}

void Game::DisplayInf(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pObjectDataTable"))
	{
		m_pObjinfLabel->SetText("Total infrastructure: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(), 2)));
	}
}

void Game::DisplayYearlyProd(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pColonyTable"))
	{
		m_pYearlyProdLabel->SetText("Yearly production: " + num2string(round(a_pNewSelect->GetYearlyProduction(), 0)));
	}
}

void Game::DisplayEmploy(HabitableObject* a_pNewSelect)
{
	if(!a_pNewSelect->GetNumJobs() || !a_pNewSelect->Population())
		m_pEmployLabel->SetText("Jobs filled: NA%");
	else
		m_pEmployLabel->SetText("Jobs filled: " + num2string(100 * round(float(a_pNewSelect->Population()) / float(a_pNewSelect->GetNumJobs()), 2) ) + "%");
}

void Game::DisplayComm(HabitableObject* a_pNewSelect)
{
	m_pCommLabel->SetText("Commercial development: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::COMMERCIAL), 2)) + "(" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::COMMERCIAL), 2)) + "%employ)");
}

void Game::DisplayMining(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pRawResTable"))
	{
		m_pMiningInfLabel->SetText("Mining operations: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::MINING), 2)) + "(" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::MINING), 2)) + "%employ)");
		m_pResCarbLabel->SetText("Carbon matter: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::CARBONACEOUS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::CARBONACEOUS), 2)));
		m_pResSiliLabel->SetText("Silicon matter: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SILICACEOUS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SILICACEOUS), 2)));
		m_pResMetalLabel->SetText("Metal ore: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::METALLIC), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::METALLIC), 2)));
	}
}

void Game::DisplayGasCollection(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pRawResTable"))
	{
		m_pGasInfLabel->SetText("Gas collection: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::GAS_PROCESSING), 2)) + "(" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::GAS_PROCESSING), 2)) + "%employ)");
		m_pResOxyLabel->SetText("Oxygen: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::OXYGEN), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::OXYGEN), 2)));
		m_pResHydroLabel->SetText("Hydrogen: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::HYDROGEN), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::HYDROGEN), 2)));
		m_pResWaterCLabel->SetText("H20: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::WATERCRYSTALS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::WATERCRYSTALS), 2)));
	}
}

void Game::DisplayWasteRec(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pRawResTable"))
	{
		m_pWasteInfLabel->SetText("Waste recycling: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::WASTE_RECYCLING), 2)) + "(" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::WASTE_RECYCLING), 2)) + "%employ)");
		m_pResWasteLabel->SetText("Organic waste: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::ORGANICWASTE), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::ORGANICWASTE), 2)));
	}
}

void Game::DisplayScrapRec(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pRawResTable"))
	{
		m_pScrapInfLabel->SetText("Scrap recycling: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::SCRAP_RECYCLING), 2)) + "(" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::SCRAP_RECYCLING), 2)) + "%employ)");
		m_pResScrapLabel->SetText("Scrap waste: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SCRAPWASTE), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SCRAPWASTE), 2)));
	}
}

void Game::DisplayElectronic(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pFinishedResTable"))
	{
		m_pElecInfLabel->SetText("Electronics production: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::ELECTRONICS_PRODUCTION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::ELECTRONICS_PRODUCTION), 2)) + "%employ)");
		m_pResCompLabel->SetText("Circuitry: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::CIRCUITRY), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::CIRCUITRY), 2)));
		m_pResCircLabel->SetText("Components: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::COMPONENTS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::COMPONENTS), 2)));
	}
}

void Game::DisplayMaterials(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pFinishedResTable"))
	{
		m_pMatInfLabel->SetText("Materials production: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::MATERIALS_PRODUCTION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::MATERIALS_PRODUCTION), 2)) + "%employ)");
		m_pResSheetLabel->SetText("Sheet metal: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::SHEETMETAL), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::SHEETMETAL), 2)));
		m_pResGirderLabel->SetText("Girders: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::GIRDERS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::GIRDERS), 2)));
	}
}

void Game::DisplayDomesticG(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pFinishedResTable"))
	{
		m_pDomGInfLabel->SetText("Domestic production: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::DOMESTICGOODS_PRODUCTION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::DOMESTICGOODS_PRODUCTION), 2)) + "%employ)");
		m_pResDomGLabel->SetText("Domestic goods: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::DOMESTICGOODS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::DOMESTICGOODS), 2)));
	}
}

void Game::DisplayLuxuryG(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pFinishedResTable"))
	{
		m_pLuxGInfLabel->SetText("Luxury production: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::LUXURYGOODS_PRODUCTION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::LUXURYGOODS_PRODUCTION), 2)) + "%employ)");
		m_pResLuxGLabel->SetText("Luxury goods: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::LUXURYGOODS), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::LUXURYGOODS), 2)));
	}
}

void Game::DisplayFood(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pConsumableResTable"))
	{
		m_pFoodInfLabel->SetText("Farming: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::FOOD_PROCESSING), 2)) + "%employ)");
		m_pResFoodLabel->SetText("Food: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::FOOD), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::FOOD), 2)));
		if(!a_pNewSelect->GetSoilAmount() || !a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING))
		{
			m_pSoilLabel->SetText("Soil: 0% 0Q");
		}
		else
		{
			m_pSoilLabel->SetText("Soil: " + num2string(100 * round(a_pNewSelect->GetSoilAmount() / a_pNewSelect->GetInfrastructureLevel(Infrastructure::FOOD_PROCESSING), 2)) + "% Q" + num2string(round(a_pNewSelect->GetSoilQ(), 2)));
		}
	}
}

void Game::DisplayWater(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pConsumableResTable"))
	{
		m_pWaterInfLabel->SetText("Water purifying: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::WATER_PURIFICATION), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::WATER_PURIFICATION), 2)) + "%employ)");
		m_pResWaterLabel->SetText("Water: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::WATER), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::WATER), 2)));
	}
}

void Game::DisplayFuel(HabitableObject* a_pNewSelect)
{
	if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pConsumableResTable"))
	{
		m_pFuelInfLabel->SetText("Fuel processing: " + num2string(round(a_pNewSelect->GetInfrastructureLevel(Infrastructure::FUEL_PROCESSING), 2)) + " (" + num2string(round(100 * a_pNewSelect->GetPersonnelMultiplier(Infrastructure::FUEL_PROCESSING), 2)) + "%employ)");
		m_pResFuelLabel->SetText("Fuel: " + num2string(round(a_pNewSelect->GetStoredResNum(Resource::FUEL), 2)) + " Q" + num2string(round(a_pNewSelect->GetStoredResQ(Resource::FUEL), 2)));
	}
}

void Game::BottomPanelClick()
{
	if(m_pCurSelect)
	{
		if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pObjectDataTable"))
		{
			DisplayInf(m_pCurSelect);
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pColonyTable"))
		{
			DisplayPower(m_pCurSelect);
			DisplayAtmos(m_pCurSelect);
			DisplayStorage(m_pCurSelect);
			DisplayYearlyProd(m_pCurSelect);
			DisplayEmploy(m_pCurSelect);
			DisplayComm(m_pCurSelect);
			DisplayResidential(m_pCurSelect);
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pRawResTable"))
		{
			DisplayMining(m_pCurSelect);
			DisplayGasCollection(m_pCurSelect);
			DisplayWasteRec(m_pCurSelect);
			DisplayScrapRec(m_pCurSelect);
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pFinishedResTable"))
		{
			DisplayElectronic(m_pCurSelect);
			DisplayMaterials(m_pCurSelect);
			DisplayDomesticG(m_pCurSelect);
			DisplayLuxuryG(m_pCurSelect);
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pConsumableResTable"))
		{
			DisplayFood(m_pCurSelect);
			DisplayWater(m_pCurSelect);
			DisplayFuel(m_pCurSelect);
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pShipProdTable"))
		{
			//
		}
		else if(!m_pBottomPanel->GetNthPage(m_pBottomPanel->GetCurrentPage())->GetId().compare("m_pDockedTradersTable"))
		{
			//
		}
	}
}
