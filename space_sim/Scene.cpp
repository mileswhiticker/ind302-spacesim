#include "Scene.hpp"

#include "SFGManager.hpp"
#include <iostream>

Scene::Scene()
:	m_SceneType(INVALID)
{
	//
}

Scene::~Scene()
{
	while(m_pButtons.size())
	{
		sfg::Button::Ptr pButton = m_pButtons.front();
		ClearWidget(pButton);
		m_pButtons.erase(m_pButtons.begin());
	}
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
