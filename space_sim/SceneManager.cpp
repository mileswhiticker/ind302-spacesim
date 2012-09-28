#include "SceneManager.hpp"
#include "Scene.hpp"

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
			return true;
		};
	}
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
