#include "GameManager.hpp"

#include "SFGManager.hpp"
#include "AppManager.hpp"

#include <SFGUI\Button.hpp>
#include <SFGUI\Image.hpp>

#include "StellarGroup.hpp"
#include "OrionSpur.hpp"
#include "Planet.hpp"

#define NULL 0

static Planet* m_pHomePlanet = NULL;

GameManager::GameManager()
:	m_CurView(MAXVAL)
{
	//
}

void GameManager::SetHomePlanet(Planet* a_pNewHomePlanet)
{
	m_pHomePlanet = a_pNewHomePlanet;
}

Planet* GameManager::GetHomePlanet()
{
	return m_pHomePlanet;
}

void GameManager::Initialise()
{
	OrionSpur::Generate();
	ShowView(ORIONSPUR);
}

void GameManager::Uninitialise()
{
	ShowView(MAXVAL);
}

void GameManager::ShowView(View a_NewView)
{
	if(a_NewView == m_CurView)
		return;
	
	//clear out the previous view
	ClearCurView();

	if(a_NewView != MAXVAL)
	{
		switch(a_NewView)
		{
		case(ORIONSPUR):
			{
				std::vector<StellarGroup*> stellarGroups = OrionSpur::GetStellarGroups();
				sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();
				windowDims.x *= 5.f/6.f;
				windowDims.y *= 5.f/6.f;
				for(auto it = stellarGroups.begin(); it != stellarGroups.end(); ++it)
				{
					StellarGroup* pStellarGroup = *it;
					sf::Vector2f relPos = pStellarGroup->GetRelPosition();
					//relPos.x -= 1.f;
					//relPos.y -= 1.f;
					//
					sfg::Button::Ptr pButton = sfg::Button::Create("");
					sf::Image* pSFImage = new sf::Image();
					pSFImage->loadFromFile("../media/group.png");
					sfg::Image::Ptr pSFGImage = sfg::Image::Create();
					pButton->SetImage(pSFGImage);
					pButton->SetPosition( sf::Vector2f(windowDims.x * relPos.x, windowDims.y * relPos.y) );
					//
					m_ClickableObjects.push_back(pButton);
					AddWidget(pButton);
				}
				break;
			}
		};
		m_CurView = a_NewView;
	}
}

void GameManager::ClearCurView()
{
	for(auto it = m_ClickableObjects.begin(); it != m_ClickableObjects.end(); it)
	{
		ClearWidget(*it);
		it = m_ClickableObjects.erase(it);
	}
}
