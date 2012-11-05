#include "Scene_Game.hpp"

#include "AppManager.hpp"
#include "SFGManager.hpp"
#include "SceneManager.hpp"

#include <SFML\Graphics\Image.hpp>
#include <sfml\Graphics\Sprite.hpp>

Game::Game()
:	Scene()
{
	m_SceneType = SIM;
	//
	
	sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();

	m_pWidgets.push_back(sfg::Button::Create("Main Menu"));
	m_pWidgets.back()->SetPosition(sf::Vector2f(windowDims.x / 6.f, windowDims.y / 6.f));
	m_pWidgets.back()->GetSignal(sfg::Widget::OnLeftClick).Connect(&Game::LaunchMainMenu, this);
	AddWidget(m_pWidgets.back());
	
	//background
	sf::Texture* pTexture = new sf::Texture();
	pTexture->loadFromFile("../media/starry.jpg");
	m_pTextures.push_back(pTexture);

	sf::Sprite* pSprite = new sf::Sprite(*pTexture);
	sf::Vector2u texSize = pTexture->getSize();
	sf::Vector2f newScale(windowDims.y / texSize.y, windowDims.y / texSize.y);
	pSprite->setScale(newScale);
	m_pSprites.push_back(pSprite);
}

void Game::LaunchMainMenu()
{
	SceneManager::GetSingleton().LaunchScene(MAIN_MENU);
}
