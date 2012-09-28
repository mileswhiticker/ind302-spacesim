#ifndef SCENE_HPP
#define SCENE_HPP

#include "SceneTypes.h"
#include <vector>

namespace sf
{
	class Sprite;
	class Texture;
};

class Scene
{
public:
	Scene();
	//
	virtual void ToggleDisplayScene();
	SceneType GetSceneType();
	//
	std::vector<sf::Sprite*> GetSprites();
	//
protected:
	bool m_Displayed;
	SceneType m_SceneType;
	//
	std::vector<sf::Sprite*> m_pSprites;
	std::vector<sf::Texture*> m_pTextures;
	//
};

class MainMenu
:	public Scene
{
public:
	MainMenu();
	//
	virtual void ToggleDisplayScene();
	//
private:
	//
};

#endif SCENE_HPP