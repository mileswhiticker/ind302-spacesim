#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "SceneManager.hpp"
#include "GameManager.hpp"

#include "HabitableObject.hpp"

#include "Num2StringHelper.h"
#include "GameHelpers.hpp"

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <SFGUI\Notebook.hpp>

Game::Game()
:	Scene()
,	m_pBGTexture(NULL)
,	m_pBGSprite(NULL)
{
	m_SceneType = SIM;
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	sf::FloatRect allocation;

	//right panel
	sfg::Notebook::Ptr pRightPanel = sfg::Notebook::Create();
	allocation.top = 0;
	allocation.height = 5 * windowDims.y / 6;
	allocation.left = 5 * windowDims.x / 6;
	allocation.width = windowDims.x / 6;
	pRightPanel->SetAllocation(allocation);
	pRightPanel->SetScrollable(true);
	//
	sfg::Table::Ptr pTable1 = sfg::Table::Create();
	pTable1->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable1->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable1->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(2,0,1,1));
	pRightPanel->AppendPage(pTable1, sfg::Label::Create("Panel1"));
	//
	sfg::Table::Ptr pTable2 = sfg::Table::Create();
	pTable2->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable2->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(0,1,1,1));
	pTable2->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,2,1,1));
	pRightPanel->AppendPage(pTable2, sfg::Label::Create("Panel2"));
	//
	/*sfg::Table::Ptr pTable3 = sfg::Table::Create();
	pTable3->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,1,1,1));
	pRightPanel->AppendPage(pTable3, sfg::Label::Create("Panel3"));*/
	//
	m_pWidgets.push_back(pRightPanel);

	//bottom panel
	sfg::Notebook::Ptr pBottomPanel = sfg::Notebook::Create();
	allocation.top = 5 * windowDims.y / 6;
	allocation.height = windowDims.y / 6;
	allocation.left = 0;
	allocation.width = 5 * windowDims.x / 6;
	pBottomPanel->SetAllocation(allocation);
	pBottomPanel->SetScrollable(true);
	//
	m_pObjectDataTable = sfg::Table::Create();
	pBottomPanel->AppendPage(m_pObjectDataTable, sfg::Label::Create("Object Data"));
	m_pObjnameLabel = sfg::Label::Create("Object name");
	m_pObjectDataTable->Attach(m_pObjnameLabel, sf::Rect<sf::Uint32>(0,0,1,1));
	m_pObjtypeLabel = sfg::Label::Create("Object type");
	m_pObjectDataTable->Attach(m_pObjtypeLabel, sf::Rect<sf::Uint32>(0,1,1,1));
	m_pObjpopLabel = sfg::Label::Create("Object population");
	m_pObjectDataTable->Attach(m_pObjpopLabel, sf::Rect<sf::Uint32>(0,2,1,1));
	m_pObjcoordsLabel = sfg::Label::Create("Object coords");
	m_pObjectDataTable->Attach(m_pObjcoordsLabel, sf::Rect<sf::Uint32>(0,3,1,1));
	m_pObjdiameterLabel = sfg::Label::Create("Object diameter");
	m_pObjectDataTable->Attach(m_pObjdiameterLabel, sf::Rect<sf::Uint32>(0,4,1,1));
	m_pObjmassLabel = sfg::Label::Create("Object mass");
	m_pObjectDataTable->Attach(m_pObjmassLabel, sf::Rect<sf::Uint32>(0,5,1,1));
	//
	m_pCarbNumLabel = sfg::Label::Create("m_pCarbNumLabel");
	m_pObjectDataTable->Attach(m_pCarbNumLabel, sf::Rect<sf::Uint32>(1,0,1,1));
	m_pSiliNumLabel = sfg::Label::Create("m_pSiliNumLabel");
	m_pObjectDataTable->Attach(m_pSiliNumLabel, sf::Rect<sf::Uint32>(1,1,1,1));
	m_pMetalNumLabel = sfg::Label::Create("m_pMetalNumLabel");
	m_pObjectDataTable->Attach(m_pMetalNumLabel, sf::Rect<sf::Uint32>(1,2,1,1));
	m_pHydroNumLabel = sfg::Label::Create("m_pHydroNumLabel");
	m_pObjectDataTable->Attach(m_pHydroNumLabel, sf::Rect<sf::Uint32>(1,3,1,1));
	//
	m_pCarbQLabel = sfg::Label::Create("m_pCarbQLabel");
	m_pObjectDataTable->Attach(m_pCarbQLabel, sf::Rect<sf::Uint32>(2,0,1,1));
	m_pSiliQLabel = sfg::Label::Create("m_pSiliQLabel");
	m_pObjectDataTable->Attach(m_pSiliQLabel, sf::Rect<sf::Uint32>(2,1,1,1));
	m_pMetalQLabel = sfg::Label::Create("m_pMetalQLabel");
	m_pObjectDataTable->Attach(m_pMetalQLabel, sf::Rect<sf::Uint32>(2,2,1,1));
	m_pHydroQLabel = sfg::Label::Create("m_pHydroQLabel");
	m_pObjectDataTable->Attach(m_pHydroQLabel, sf::Rect<sf::Uint32>(2,3,1,1));
	//
	m_pAtmosDensityLabel = sfg::Label::Create("m_pAtmosDensityLabel");
	m_pObjectDataTable->Attach(m_pAtmosDensityLabel, sf::Rect<sf::Uint32>(3,0,1,1));
	m_pAtmosCompPlaceholderLabel = sfg::Label::Create("m_pAtmosCompPlaceholderLabel");
	m_pObjectDataTable->Attach(m_pAtmosCompPlaceholderLabel, sf::Rect<sf::Uint32>(3,1,1,1));
	
	sfg::Table::Ptr pTable5 = sfg::Table::Create();
	pTable5->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable5->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable5->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,1,1,1));
	pBottomPanel->AppendPage(pTable5, sfg::Label::Create("Infrastructure"));
	
	//resource storage
	//
	m_pRawResStoreTable = sfg::Table::Create();
	for(int ind = 0; ind < NUM_RAW_MATERIALS; ++ind)
	{
		sfg::Label::Ptr pNameLabel = sfg::Label::Create(GetResourceStringname(Resource::ResourceType(ind)));
		//pNameLabel->SetRequisition(sf::Vector2f(85, 20));
		sfg::Label::Ptr pValueLabel = sfg::Label::Create("0 (Q ?)");
		//pValueLabel->SetRequisition(sf::Vector2f(85, 20));

		mResourceNameLabels.insert(std::pair<Resource::ResourceType, sfg::Label::Ptr>(Resource::ResourceType(ind), pNameLabel));
		mResourceValueLabels.insert(std::pair<Resource::ResourceType, sfg::Label::Ptr>(Resource::ResourceType(ind), pValueLabel));
		//
		int xOffset = ind;
		int yOffset = 0;
		if(ind >= NUM_RAW_MATERIALS / 2)
		{
			xOffset = ind - NUM_RAW_MATERIALS / 2;
			yOffset = 2;
		}

		m_pRawResStoreTable->Attach(pNameLabel, sf::Rect<sf::Uint32>(xOffset, yOffset + 0, 1, 1));
		m_pRawResStoreTable->Attach(pValueLabel, sf::Rect<sf::Uint32>(xOffset, yOffset + 1 ,1, 1));
	}
	pBottomPanel->AppendPage(m_pRawResStoreTable, sfg::Label::Create("Raw materials Storage"));
	//
	m_pFinishedResStoreTable = sfg::Table::Create();
	for(int ind = NUM_RAW_MATERIALS; ind < Resource::MAXVAL; ++ind)
	{
		sfg::Label::Ptr pNameLabel = sfg::Label::Create(GetResourceStringname(Resource::ResourceType(ind)));
		//pNameLabel->SetRequisition(sf::Vector2f(85, 20));
		sfg::Label::Ptr pValueLabel = sfg::Label::Create("0 (Q ?)");
		//pValueLabel->SetRequisition(sf::Vector2f(85, 20));

		mResourceNameLabels.insert(std::pair<Resource::ResourceType, sfg::Label::Ptr>(Resource::ResourceType(ind), pNameLabel));
		mResourceValueLabels.insert(std::pair<Resource::ResourceType, sfg::Label::Ptr>(Resource::ResourceType(ind), pValueLabel));
		//
		int xOffset = ind - NUM_RAW_MATERIALS;
		int yOffset = 0;
		if(xOffset >= NUM_PRODUCED_GOODS / 2)
		{
			xOffset -= NUM_PRODUCED_GOODS / 2;
			yOffset = 2;
		}

		m_pFinishedResStoreTable->Attach(pNameLabel, sf::Rect<sf::Uint32>(xOffset, yOffset + 0, 1, 1));
		m_pFinishedResStoreTable->Attach(pValueLabel, sf::Rect<sf::Uint32>(xOffset, yOffset + 1 ,1, 1));
	}
	pBottomPanel->AppendPage(m_pFinishedResStoreTable, sfg::Label::Create("Produced goods Storage"));

	sfg::Table::Ptr pTable7 = sfg::Table::Create();
	pTable7->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable7->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable7->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(2,0,1,1));
	pBottomPanel->AppendPage(pTable7, sfg::Label::Create("Docked Traders"));

	m_pWidgets.push_back(pBottomPanel);

	//bottom right status panel
	m_pStatusTable = sfg::Table::Create();
	allocation.top = 5 * windowDims.y / 6;
	allocation.height = windowDims.y / 6;
	allocation.left = 5 * windowDims.x / 6;
	allocation.width = windowDims.x / 6;
	m_pStatusTable->Attach(sfg::Label::Create("The current date is X/Y/ZWVU"), sf::Rect<sf::Uint32>(0,0,1,1));
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

	//std::cout << "Game::ChangeView()" << std::endl;
	if(a_pNewFocus->GetParent())
		m_pMainMenuButton->SetLabel(GetDisplayStringname(a_pNewFocus->GetParent()->GetDisplayableType()));
	else
		m_pMainMenuButton->SetLabel("Main Menu");
	m_pTitleLabel->SetText( GetDisplayStringname(a_pNewFocus->GetDisplayableType()) );
	
	//
	m_pBGTexture->loadFromFile(a_pNewFocus->GetBGName());
	/*switch(GameManager::GetSingleton().GetCurrentlyViewedType())
	{
	default:
	case(DisplayableObject::ORIONSPUR):
		{
			m_pBGTexture->loadFromFile("../media/orionspur_bg.png");
			break;
		}
	case(DisplayableObject::STELLARGROUP):
		{
			m_pBGTexture->loadFromFile("../media/stellargroup_bg.png");
			break;
		}
	case(DisplayableObject::STARSYSTEM):
		{
			m_pBGTexture->loadFromFile("../media/starsystem_bg.png");
			break;
		}
	case(DisplayableObject::STAR):
		{
			m_pBGTexture->loadFromFile("../media/star_bg.png");
			break;
		}
	case(DisplayableObject::PLANET):
		{
			m_pBGTexture->loadFromFile("../media/planet_bg.png");
			break;
		}
	}*/
}

void Game::SelectObject(HabitableObject* a_pNewSelect)
{
	m_pObjnameLabel->SetText(a_pNewSelect->GetName());
	m_pObjtypeLabel->SetText(GetHabitableStringname(a_pNewSelect->GetHabitableType()));
	m_pObjpopLabel->SetText("Population: " + num2string(a_pNewSelect->Population()));
	m_pObjcoordsLabel->SetText("Coords (AU): " + a_pNewSelect->GetCoordsString());
	m_pObjdiameterLabel->SetText("Diameter: " + num2string(a_pNewSelect->Diameter()));
	m_pObjmassLabel->SetText("Mass: " + num2string(a_pNewSelect->ObjectMass()));
	//
	m_pCarbNumLabel->SetText("Carb#: " + num2string(a_pNewSelect->GetResNum(Resource::CARBONACEOUS)));
	m_pSiliNumLabel->SetText("Sili#: " + num2string(a_pNewSelect->GetResNum(Resource::SILICACEOUS)));
	m_pMetalNumLabel->SetText("Metal#: " + num2string(a_pNewSelect->GetResNum(Resource::METALLIC)));
	m_pHydroNumLabel->SetText("Hydrocarbs#: " + num2string(a_pNewSelect->GetResNum(Resource::HYDROCARBON)));
	//
	m_pCarbQLabel->SetText("CarbQ: " + num2string(a_pNewSelect->GetResQ(Resource::CARBONACEOUS)));
	m_pSiliQLabel->SetText("SiliQ: " + num2string(a_pNewSelect->GetResQ(Resource::SILICACEOUS)));
	m_pMetalQLabel->SetText("MetalQ: " + num2string(a_pNewSelect->GetResQ(Resource::METALLIC)));
	m_pHydroQLabel->SetText("HydrocarbsQ: " + num2string(a_pNewSelect->GetResQ(Resource::HYDROCARBON)));
	//
	m_pAtmosDensityLabel->SetText("Atmosphere density: " + num2string(a_pNewSelect->AtmosDensity()));
	m_pAtmosCompPlaceholderLabel->SetText("---");
}
