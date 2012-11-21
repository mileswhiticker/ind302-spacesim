#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "SceneManager.hpp"
#include "GameManager.hpp"

#include "GameHelpers.hpp"

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <SFGUI\Notebook.hpp>

Game::Game()
:	Scene()
{
	m_SceneType = SIM;
	//
	
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
	sfg::Table::Ptr pTable3 = sfg::Table::Create();
	pTable3->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable3->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,1,1,1));
	pRightPanel->AppendPage(pTable3, sfg::Label::Create("Panel3"));
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
	sfg::Table::Ptr pTable4 = sfg::Table::Create();
	pTable4->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable4->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(0,1,1,1));
	pTable4->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,2,1,1));
	pBottomPanel->AppendPage(pTable4, sfg::Label::Create("Panel2"));
	//
	sfg::Table::Ptr pTable5 = sfg::Table::Create();
	pTable5->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable5->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable5->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(0,1,1,1));
	pBottomPanel->AppendPage(pTable5, sfg::Label::Create("Panel3"));
	//
	sfg::Table::Ptr pTable6 = sfg::Table::Create();
	pTable6->Attach(sfg::Label::Create("Test1"), sf::Rect<sf::Uint32>(0,0,1,1));
	pTable6->Attach(sfg::Label::Create("Test2"), sf::Rect<sf::Uint32>(1,0,1,1));
	pTable6->Attach(sfg::Label::Create("Test3"), sf::Rect<sf::Uint32>(2,0,1,1));
	pBottomPanel->AppendPage(pTable6, sfg::Label::Create("Panel1"));
	//
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
	sf::Texture* pTexture = new sf::Texture();
	pTexture->loadFromFile("../media/starry.jpg");
	m_pTextures.push_back(pTexture);

	sf::Sprite* pSprite = new sf::Sprite(*pTexture);
	sf::Vector2u texSize = pTexture->getSize();
	sf::Vector2f newScale(windowDims.y / texSize.y, windowDims.y / texSize.y);
	pSprite->setScale(newScale);
	m_pSprites.push_back(pSprite);

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
}
