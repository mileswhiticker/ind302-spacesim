#ifndef APP_MANAGER_HPP
#define APP_MANAGER_HPP

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace sf
{
	class RenderWindow;
	//
};

class AppManager
{
public:
	static AppManager& GetSingleton()
	{
		static AppManager instance;
		return instance;
	}
	static AppManager* GetSingletonPtr()
	{
		return &AppManager::GetSingleton();
	}
	bool Initialise();
	//
	void Update(float a_DeltaT);
	void PollEvents();
	bool Render();
	//
	sf::Vector2f GetWindowDimensions();
	//
	bool CheckQuitting();
	//
private:
	AppManager();
	//
	sf::RenderWindow* m_pRenderWindow;
	//
	bool m_Initialised;
	bool m_QuitNextUpdate;
	//
	sf::Texture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;
	//
};

#endif APP_MANAGER_HPP