#include "SFGManager.hpp"
#include "AppManager.hpp"

#include <SFML\Graphics\RenderTarget.hpp>

SFGManager::SFGManager()
:	m_Initialised(false)
{
	sfg::Desktop* pInstance = new sfg::Desktop();
	m_pSFGDesktop = sfg::SharedPtr<sfg::Desktop>(pInstance);
}

bool SFGManager::Initialise()
{
	if(m_Initialised)
		return false;
	
	m_Initialised = true;
	return true;
}

bool SFGManager::Update(float a_DeltaT)
{
	if(m_Initialised)
	{
		m_pSFGDesktop->Update(a_DeltaT);
		return true;
	}
	return false;
}

bool SFGManager::Render(sf::RenderTarget& a_RenderTarget)
{
	if(m_Initialised)
	{
		// Draw the GUI
		m_sfgui.Display(a_RenderTarget);
		return true;
	}
	return false;
}

void SFGManager::HandleEvent(sf::Event a_Event)
{
	if( a_Event.type == sf::Event::Resized )
	{
		sf::Vector2f windowDims =- AppManager::GetSingleton().GetWindowDimensions();
		m_pSFGDesktop->UpdateViewRect( sf::FloatRect(0, 0, windowDims.x, windowDims.y) );
	}
	else
	{
		m_pSFGDesktop->HandleEvent(a_Event);
	}
}

bool SFGManager::CheckInitialised()
{
	return m_Initialised;
}

sfg::SharedPtr<sfg::Desktop> SFGManager::GetSFGDesktop()
{
	return m_pSFGDesktop;
}

bool AddWidget(sfg::SharedPtr<sfg::Widget> a_Widget)
{
	if(SFGManager::GetSingleton().CheckInitialised())
	{
		SFGManager::GetSingleton().GetSFGDesktop()->Add(a_Widget);
		return true;
	}
	return false;
}
