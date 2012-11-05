#include "SceneManager.hpp"
#include "Scene_MainMenu.hpp"
#include "Scene_Game.hpp"

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>

SceneManager::SceneManager()
:	m_NeedsClearing(false)
,	m_pScene(0)
{
	//
}

bool SceneManager::LaunchScene(SceneType a_SceneType)
{
	switch(a_SceneType)
	{
	default:
		{
			//
			return false;
		};
	case(MAIN_MENU):
		{
			if(m_NeedsClearing)
			{
				ClearScene();
			}

			m_pScene = new MainMenu();
			m_NeedsClearing = true;
			break;
		};
	case(SIM):
		{
			if(m_NeedsClearing)
			{
				ClearScene();
			}

			m_pScene = new Game();
			m_NeedsClearing = true;
			break;
		};
	}

	m_pSprites = m_pScene->GetSprites();
	return true;
}

void SceneManager::ClearScene()
{
	if(m_pScene)
	{
		delete m_pScene;
		m_pScene = 0;
	}
	m_NeedsClearing = false;
}

Scene* SceneManager::GetCurrentScene()
{
	return m_pScene;
}

void SceneManager::Update(float a_DeltaT)
{
	return;
}

void SceneManager::Render(sf::RenderTarget& a_RenderTarget)
{
	m_pScene->Render(a_RenderTarget);
}
