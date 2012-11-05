#include "Scene_MainMenu.hpp"

#include "SceneManager.hpp"
#include "AppManager.hpp"
#include "SFGManager.hpp"

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <windows.h>

MainMenu::MainMenu()
:	Scene()
{
	m_SceneType = MAIN_MENU;
	//
	
	sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();
	
	m_pWidgets.push_back(sfg::Button::Create("Start"));
	m_pWidgets.back()->SetPosition(sf::Vector2f(windowDims.x / 5, 2.f * (windowDims.y / 5.f)));
	m_pWidgets.back()->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::LaunchGame, this);
	
	m_pWidgets.push_back(sfg::Button::Create("About"));
	m_pWidgets.back()->SetPosition(sf::Vector2f(windowDims.x / 5, 3.f * (windowDims.y / 5.f)));
	m_pWidgets.back()->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::About, this);

	m_pWidgets.push_back(sfg::Button::Create("Quit"));
	m_pWidgets.back()->SetPosition(sf::Vector2f(windowDims.x / 5, 4.f * (windowDims.y / 5.f)));
	m_pWidgets.back()->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::Quit, this);
	
	//background
	sf::Texture* pTexture = new sf::Texture();
	pTexture->loadFromFile("../media/background.jpg");
	m_pTextures.push_back(pTexture);

	sf::Sprite* pSprite = new sf::Sprite(*pTexture);
	sf::Vector2u texSize = pTexture->getSize();
	sf::Vector2f newScale(windowDims.y / texSize.y, windowDims.y / texSize.y);
	pSprite->setScale(newScale);
	m_pSprites.push_back(pSprite);

	//menu title
	pTexture = new sf::Texture();
	pTexture->loadFromFile("../media/menutitle.png");
	m_pTextures.push_back(pTexture);

	pSprite = new sf::Sprite(*pTexture);
	texSize = pTexture->getSize();
	m_pSprites.push_back(pSprite);
	
	Initialise();
}

void MainMenu::LaunchGame()
{
	SceneManager::GetSingleton().LaunchScene(SIM);
}

void MainMenu::About()
{
	MessageBox(0, "About dialog will go here.", "About", 0);
}

void MainMenu::Quit()
{
	//yeeee
	exit(0);
}
