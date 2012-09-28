#ifndef SIM_MANAGER_HPP
#define SIM_MANAGER_HPP

#include <vector>

namespace sf
{
	class RenderTarget;
	class Sprite;
};

class SimManager
{
public:
	static SimManager& GetSingleton()
	{
		static SimManager instance;
		return instance;
	}
	static SimManager* GetSingletonPtr()
	{
		return &SimManager::GetSingleton();
	}
	bool Initialise();
	//
	void Update(float a_DeltaT);
	void Render(sf::RenderTarget& a_RenderTarget);
	//
	bool CheckQuitting();
	//
private:
	SimManager();
	//
	bool m_Initialised;
	bool m_QuitNextUpdate;
	//
	std::vector<sf::Sprite*> m_pSprites;
	//
};

#endif SIM_MANAGER_HPP