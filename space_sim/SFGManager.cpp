#include "SFGManager.hpp"
#include "AppManager.hpp"

#include <SFGUI\SFGUI.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

SFGManager::SFGManager()
:	m_Initialised(false)
{
	//sfg::Desktop* pInstance = new sfg::Desktop();
	//m_pSFGDesktop = sfg::SharedPtr<sfg::Desktop>(pInstance);
	//pInstance->SetProperty("Button", "BorderWidth", 0.f);
}

bool SFGManager::Initialise()
{
	if(m_Initialised)
		return false;
	
	//sfg::Selector::Ptr pSelector = sfg::Selector::Create("test");

	//m_SFGDesktop.SetProperty("Button", "BorderWidth", 0.f);
	//int derp = m_SFGDesktop.GetProperty<int>("test", sfg::Label::Create(""));

	m_Initialised = true;
	return true;
}

void SFGManager::Update(float a_DeltaT)
{
	if(m_Initialised)
	{
		m_SFGDesktop.Update(a_DeltaT);
	}
}

void SFGManager::Render(sf::RenderTarget& a_RenderTarget)
{
	if(m_Initialised)
	{
		// Draw the GUI
		m_sfgui.Display(a_RenderTarget);
	}
}

void SFGManager::HandleEvent(sf::Event a_Event)
{
	if( a_Event.type == sf::Event::Resized )
	{
		sf::Vector2f windowDims =- AppManager::GetSingleton().GetWindowDimensions();
		m_SFGDesktop.UpdateViewRect( sf::FloatRect(0, 0, windowDims.x, windowDims.y) );
	}
	else
	{
		m_SFGDesktop.HandleEvent(a_Event);
	}
}

bool SFGManager::CheckInitialised()
{
	return m_Initialised;
}

//sfg::SharedPtr<sfg::Desktop>
sfg::Desktop& SFGManager::GetSFGDesktop()
{
	return m_SFGDesktop;
}

bool AddWidget(sfg::SharedPtr<sfg::Widget> a_Widget)
{
	if(SFGManager::GetSingleton().CheckInitialised())
	{
		SFGManager::GetSingleton().GetSFGDesktop().Add(a_Widget);
		return true;
	}
	return false;
}

bool ClearWidget(sfg::SharedPtr<sfg::Widget> a_Widget)
{
	if(SFGManager::GetSingleton().CheckInitialised())
	{
		SFGManager::GetSingleton().GetSFGDesktop().Remove(a_Widget);
		return true;
	}
	return false;
}

sf::Vector2f SFGManager::GetWindowDimensions()
{
	return AppManager::GetSingleton().GetWindowDimensions();
}
