#include "AppManager.hpp"

#include "GameManager.hpp"
#include "SimManager.hpp"
#include "SFGManager.hpp"
#include "SceneManager.hpp"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <SFGUI\Button.hpp>

AppManager::AppManager()
:	m_pRenderWindow(0)
,	m_Initialised(false)
,	m_QuitNextUpdate(false)
{
	//
}

bool AppManager::Initialise()
{
	sf::Clock timer;
	//
	if(m_Initialised)
		return false;
	//
	sf::VideoMode mode(1024, 768);
	m_pRenderWindow = new sf::RenderWindow(mode, "IND302 Miles Whiticker - Space Sim");
	m_pRenderWindow->resetGLStates();
	m_Initialised = true;
	//
	SFGManager::GetSingleton().Initialise();
	SimManager::GetSingleton().Initialise();
	SceneManager::GetSingleton().LaunchScene(MAIN_MENU);

	srand(timer.getElapsedTime().asMilliseconds());
	//
	return true;
}

void AppManager::Update(float a_DeltaT)
{
	//todo: delete this
	//SimManager::GetSingleton().Update(a_DeltaT);

	GameManager::GetSingleton().Update(a_DeltaT);
	SceneManager::GetSingleton().Update(a_DeltaT);
	SFGManager::GetSingleton().Update(a_DeltaT);
}

void AppManager::PollEvents()
{
	sf::Event curEvent;
	while(m_pRenderWindow->pollEvent(curEvent))
	{
		bool handled = false;

		if(curEvent.type == sf::Event::Closed || (curEvent.type == sf::Event::KeyPressed && curEvent.key.code == sf::Keyboard::Escape))
		{
			m_QuitNextUpdate = true;
		}
		else
		{
			GameManager::GetSingleton().HandleEvent(curEvent);
			SFGManager::GetSingleton().HandleEvent(curEvent);
		}
	}
}

bool AppManager::Render()
{
	if(m_Initialised)
	{
		// Clear screen
		m_pRenderWindow->clear();
		//why does appmanager have a bg?
		m_pRenderWindow->draw(m_BackgroundSprite);

		SimManager::GetSingleton().Render(*m_pRenderWindow);
		SceneManager::GetSingleton().Render(*m_pRenderWindow);
		SFGManager::GetSingleton().Render(*m_pRenderWindow);

		//draw the renderwindow
		m_pRenderWindow->display();

		return true;
	}
	return false;
}

bool AppManager::CheckQuitting()
{
	if(!m_QuitNextUpdate)
		m_QuitNextUpdate = !m_pRenderWindow->isOpen();

	if(!m_QuitNextUpdate)
		m_QuitNextUpdate = SimManager::GetSingleton().CheckQuitting();
	//
	return m_QuitNextUpdate;
}

sf::Vector2f AppManager::GetWindowDimensions()
{
	if(m_Initialised)
		return sf::Vector2f( static_cast<float>( m_pRenderWindow->getSize().x ), static_cast<float>( m_pRenderWindow->getSize().y) );
	//
	return sf::Vector2f();
}

sf::RenderTarget& AppManager::GetRenderTarget()
{
	return *m_pRenderWindow;
}

