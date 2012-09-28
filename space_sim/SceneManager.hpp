#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "SceneTypes.h"
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
	Scene* GetCurrentScene();
	//
private:
	SceneManager();
	//
	bool m_NeedsClearing;
	Scene* m_pScene;
	//
};

#endif SCENE_MANAGER_HPP