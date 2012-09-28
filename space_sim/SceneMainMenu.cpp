#include "Scene.hpp"
#include "SFGManager.hpp"
#include "AppManager.hpp"

#include <SFML\Graphics\Image.hpp>
#include <sfml\Graphics\Sprite.hpp>

MainMenu::MainMenu()
:	Scene()
{
	m_SceneType = MAIN_MENU;
	//
	
	sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();

	sfg::Button::Ptr pStartButton = sfg::Button::Create("Start");
	pStartButton->SetPosition(sf::Vector2f(windowDims.x / 5, 2.f * (windowDims.y / 5.f)));
	/*sf::Image startButtonImage;
	startButtonImage.loadFromFile("../media/startbutton.png");
	sfg::Image::Ptr pstartButtonImage = sfg::Image::Create(startButtonImage);
	pStartButton->SetImage(pstartButtonImage);*/
	AddWidget(pStartButton);
	
	sfg::Button::Ptr pAboutButton = sfg::Button::Create("About");
	pAboutButton->SetPosition(sf::Vector2f(windowDims.x / 5, 3.f * (windowDims.y / 5.f)));
	/*sf::Image aboutButtonImage;
	aboutButtonImage.loadFromFile("../media/aboutbutton.png");
	sfg::Image::Ptr paboutButtonImage = sfg::Image::Create(aboutButtonImage);
	pAboutButton->SetImage(paboutButtonImage);*/
	AddWidget(pAboutButton);

	sfg::Button::Ptr pQuitButton = sfg::Button::Create("Quit");
	pQuitButton->SetPosition(sf::Vector2f(windowDims.x / 5, 4.f * (windowDims.y / 5.f)));
	/*sf::Image quitButtonImage;
	quitButtonImage.loadFromFile("../media/aboutbutton.png");
	sfg::Image::Ptr pquitButtonImage = sfg::Image::Create(quitButtonImage);
	pQuitButton->SetImage(pquitButtonImage);*/
	AddWidget(pQuitButton);
	
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
	//pSprite->setScale( sf::Vector2f(windowDims.x / texSize.x, windowDims.y / texSize.y) );
	m_pSprites.push_back(pSprite);

	//create a test window
	/*sfg::Box::Ptr box( sfg::Box::Create( sfg::Box::VERTICAL, 5.f ) );
	box->Pack( sfg::Label::Create( "This is a test window." ), false );
	sfg::Window::Ptr pWindow = sfg::Window::Create();
	pWindow->SetTitle("test window title");
	pWindow->Add(box);*/
}

void MainMenu::ToggleDisplayScene()
{
	Scene::ToggleDisplayScene();

	if(m_Displayed)
	{
		//
	}
	else
	{
		//
	}
}
