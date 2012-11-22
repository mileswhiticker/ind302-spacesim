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

	//lay out the stellar groups
	std::vector<StellarGroup*> stellarGroups = OrionSpur::GetStellarGroups();
	sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();
	windowDims.x *= 5.f/6.f;
	windowDims.x -= 32;
	windowDims.y *= 5.f/6.f;
	windowDims.y -= 32;
	for(auto it = stellarGroups.begin(); it != stellarGroups.end(); ++it)
	{
		StellarGroup* pStellarGroup = *it;
		sf::Vector2f relPos = pStellarGroup->GetRelPosition();
		sfg::Button::Ptr pButton = sfg::Button::Create("");
		pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)pStellarGroup);

		/*sf::Image* pSFImage = new sf::Image();
		pSFImage->loadFromFile("../media/group.png");
		sfg::Image::Ptr pSFGImage = sfg::Image::Create();
		pSFGImage->SetImage(*pSFImage);
		pButton->SetImage(pSFGImage);*/

		sf::FloatRect allocation;
		allocation.top = windowDims.y * relPos.y;
		allocation.height = 32;
		allocation.left = windowDims.x * relPos.x;
		allocation.width = 32;
		pButton->SetAllocation(allocation);
		//
		m_StellarGroupButtons.push_back(pButton);
		AddWidget(pButton);
	}

	//lay out the other displayable objects
	//todo

	ShowView(ORIONSPUR);
}

void GameManager::Uninitialise()
{
	//clear out gamey things
	for(auto it = m_StellarGroupButtons.begin(); it != m_StellarGroupButtons.end(); it)
	{
		ClearWidget(*it);
		it = m_StellarGroupButtons.erase(it);
	}
	OrionSpur::Clear();

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
				/*std::vector<StellarGroup*> stellarGroups = OrionSpur::GetStellarGroups();
				sf::Vector2f windowDims = AppManager::GetSingleton().GetWindowDimensions();
				windowDims.x *= 5.f/6.f;
				windowDims.x -= 32;
				windowDims.y *= 5.f/6.f;
				windowDims.y -= 32;
				for(auto it = stellarGroups.begin(); it != stellarGroups.end(); ++it)
				{
					StellarGroup* pStellarGroup = *it;
					sf::Vector2f relPos = pStellarGroup->GetRelPosition();
					sfg::Button::Ptr pButton = sfg::Button::Create("");
					pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)pStellarGroup);

					/*sf::Image* pSFImage = new sf::Image();
					pSFImage->loadFromFile("../media/group.png");
					sfg::Image::Ptr pSFGImage = sfg::Image::Create();
					pSFGImage->SetImage(*pSFImage);
					pButton->SetImage(pSFGImage);*

					sf::FloatRect allocation;
					allocation.top = windowDims.y * relPos.y;
					allocation.height = 32;
					allocation.left = windowDims.x * relPos.x;
					allocation.width = 32;
					pButton->SetAllocation(allocation);
					//
					m_StellarGroupButtons.push_back(pButton);
					AddWidget(pButton);
				}*/
				for(auto it = m_StellarGroupButtons.begin(); it != m_StellarGroupButtons.end(); ++it)
				{
					(*it)->Show(true);
				}
				break;
			}
		};
		m_CurView = a_NewView;
	}
}

void GameManager::ClearCurView()
{
	switch(m_CurView)
	{
	case(ORIONSPUR):
		{
			for(auto it = m_StellarGroupButtons.begin(); it != m_StellarGroupButtons.end(); it)
			{
				(*it)->Show(false);
			}
			break;
		}
	}
}
