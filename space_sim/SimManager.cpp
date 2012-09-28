#include "SimManager.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>

SimManager::SimManager()
:	m_Initialised(false)
,	m_QuitNextUpdate(false)
{
	//
}

bool SimManager::Initialise()
{
	if(m_Initialised)
		return false;
	//
	SceneManager::GetSingleton().LaunchScene(MAIN_MENU);
	m_pSprites = SceneManager::GetSingleton().GetCurrentScene()->GetSprites();
	//
	m_Initialised = true;
	return true;
}

void SimManager::Update(float a_DeltaT)
{
	//
}

bool SimManager::CheckQuitting()
{
	return m_QuitNextUpdate;
}

void SimManager::Render(sf::RenderTarget& a_RenderTarget)
{
	//draw any sprites
	for(auto it = m_pSprites.begin(); it != m_pSprites.end(); ++it)
	{
		a_RenderTarget.draw(**it);
	}
}
