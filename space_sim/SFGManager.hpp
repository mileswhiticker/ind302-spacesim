#ifndef SFG_MANAGER_HPP
#define SFG_MANAGER_HPP

#include <SFGUI\SFGUI.hpp>
#include <SFML\Window\Event.hpp>

class SFGManager
{
public:
	static SFGManager& GetSingleton()
	{
		static SFGManager instance;
		return instance;
	}
	static SFGManager* GetSingletonPtr()
	{
		return &SFGManager::GetSingleton();
	}
	bool Initialise();
	bool CheckInitialised();
	//
	void Update(float a_DeltaT);
	void Render(sf::RenderTarget& a_RenderTarget);
	void HandleEvent(sf::Event a_Event);
	sf::Vector2f GetWindowDimensions();
	//
	sfg::Desktop& GetSFGDesktop();
	//
private:
	SFGManager();
	bool m_Initialised;
	//
	//sfg::SharedPtr<sfg::Desktop> m_pSFGDesktop;
	sfg::Desktop m_SFGDesktop;
	sfg::SFGUI m_sfgui;
};

bool AddWidget(sfg::SharedPtr<sfg::Widget> a_Widget);
bool ClearWidget(sfg::SharedPtr<sfg::Widget> a_Widget);

#endif SFG_MANAGER_HPP