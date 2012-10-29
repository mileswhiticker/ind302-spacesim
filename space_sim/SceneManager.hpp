#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "SceneTypes.h"
#include <vector>

namespace sf
{
	class RenderTarget;
	class Sprite;
};
class Scene;

class SceneManager
{
public:
	static SceneManager& GetSingleton()
	{
		static SceneManager instance;
		return instance;
	}
	static SceneManager* GetSingletonPtr()
	{
		return &SceneManager::GetSingleton();
	}
	//
	bool LaunchScene(SceneType a_SceneType);
	void ClearScene();
	//
	void Update(float a_DeltaT);
	void Render(sf::RenderTarget& a_RenderTarget);
	//
	Scene* GetCurrentScene();
	//
private:
	SceneManager();
	//
	bool m_NeedsClearing;
	Scene* m_pScene;
	std::vector<sf::Sprite*> m_pSprites;
	//
};

#endif SCENE_MANAGER_HPP