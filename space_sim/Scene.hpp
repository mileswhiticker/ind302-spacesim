#ifndef SCENE_HPP
#define SCENE_HPP

#include "SceneTypes.h"
#include <vector>
#include <SFGUI\Widget.hpp>

namespace sf
{
	class Sprite;
	class Texture;
};

class Scene
{
public:
	Scene();
	virtual ~Scene();
	//
	virtual void ToggleDisplayScene();
	SceneType GetSceneType();
	//
	std::vector<sf::Sprite*> GetSprites();
	void Render(sf::RenderTarget& a_RenderTarget);
	//
protected:
	bool m_Displayed;
	SceneType m_SceneType;
	//
	std::vector<sf::Sprite*> m_pSprites;
	std::vector<sf::Texture*> m_pTextures;
	//
	std::vector<sfg::Widget::Ptr> m_pWidgets;
};

#endif //SCENE_HPP