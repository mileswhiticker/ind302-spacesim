#include "Scene.hpp"

Scene::Scene()
:	m_SceneType(INVALID)
{
	//
}

void Scene::ToggleDisplayScene()
{
	m_Displayed = !m_Displayed;

	if(m_Displayed)
	{
		//
	}
	else
	{
		//
	}
}

SceneType Scene::GetSceneType()
{
	return m_SceneType;
}

std::vector<sf::Sprite*> Scene::GetSprites()
{
	return m_pSprites;
}
