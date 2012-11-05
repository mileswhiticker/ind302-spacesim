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
	while(m_pWidgets.size())
	{
		sfg::Widget::Ptr pWidget = m_pWidgets.front();
		ClearWidget(pWidget);
		m_pWidgets.erase(m_pWidgets.begin());
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

void Scene::Render(sf::RenderTarget& a_RenderTarget)
{
	//draw any sprites
	for(auto it = m_pSprites.begin(); it != m_pSprites.end(); ++it)
	{
		a_RenderTarget.draw(**it);
	}
}
