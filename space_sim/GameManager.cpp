#include "GameManager.hpp"

#include "StellarGroup.hpp"
#include "OrionSpur.hpp"
#include "Planet.hpp"
#include "StarSystem.hpp"

#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "SceneManager.hpp"

#include "MathHelpers.h"
#include "Num2StringHelper.h"
#include "GameHelpers.hpp"

#include <iostream>

static Planet* m_pHomePlanet = NULL;

GameManager::GameManager()
:	m_pCurViewedObject(NULL)
,	m_pOrionSpur(NULL)
,	m_pGameScene(NULL)
,	m_pCurSelectedObject(NULL)
	//
,	m_CurTimeRate(HOURLY)
,	mHours(0)
,	mDays(0)
,	mMonths(0)
,	mYears(2020)
,	m_tLeftTimeTick(1)
{
	//
}

void GameManager::SetHomePlanet(Planet* a_pNewHomePlanet)
{
	m_pHomePlanet = a_pNewHomePlanet;
	AddHabitableObject(a_pNewHomePlanet);
}

Planet* GameManager::GetHomePlanet()
{
	return m_pHomePlanet;
}

void GameManager::Initialise(Game* a_pGameScene)
{
	//lay out the other displayable objects
	if(!m_pSelectCircle.get())
	{
		sf::Image* pSelectImage = new sf::Image();
		pSelectImage->loadFromFile("../media/select_circle.png");
		m_pSelectCircle = sfg::Image::Create(*pSelectImage);
		m_pSelectCircle->Show(false);
		AddWidget(m_pSelectCircle);
	}
	//
	m_pOrionSpur = new OrionSpur();
	m_pGameScene = a_pGameScene;
	ViewDisplayableObject(m_pOrionSpur);
	//

	//SFGManager::GetSingleton().GetSFGDesktop()->SetProperty("Button", "BorderWidth", 0.f);
}

void GameManager::Uninitialise()
{
	//clear out gamey things
	delete m_pOrionSpur;
	m_pOrionSpur = NULL;
	m_pCurViewedObject = NULL;
	m_pGameScene = NULL;

	//ShowView(MAXVAL);
}

void GameManager::ViewDisplayableObject(DisplayableObject* a_pDisplayObject)
{
	if(!a_pDisplayObject)
	{
		std::cout << "Unable to view NULL object!" << std::endl;
		return;
	}
	
	//std::cout << "GameManager::ViewDisplayableObject()" << std::endl;
	//clear out the previous view
	ClearCurView();
	
	a_pDisplayObject->ShowContents();
	m_pCurViewedObject = a_pDisplayObject;
	//std::cout << "	" << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " displaying contents" << std::endl;
	m_pGameScene->ChangeView(m_pCurViewedObject);
	m_pSelectCircle->Show(false);
}

void GameManager::ClearCurView()
{
	if(!m_pCurViewedObject)
		return;
	//std::cout << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " hiding contents" << std::endl;
	//setup special cases here
	/*switch(m_pCurViewedObject->GetDisplayableType())
	{
	default:
		{
			m_pCurViewedObject->HideContents();
			break;
		}
	}*/
	m_pCurViewedObject->ShowContents(false);
}

void GameManager::UpOneLevel()
{
	DisplayableObject* pParent = m_pCurViewedObject->GetParent();
	if(pParent)
	{
		ViewDisplayableObject(pParent);
	}
	else
	{
		SceneManager::GetSingleton().LaunchScene(MAIN_MENU);
	}
}

DisplayableObject::DisplayableType GameManager::GetCurrentlyViewedType()
{
	return m_pCurViewedObject->GetDisplayableType();
}

void GameManager::ClickDisplayableObject(DisplayableObject* a_pDisplayObject)
{
	if(m_pCurSelectedObject)
	{
		if(m_pCurSelectedObject == a_pDisplayObject)
		{
			ViewDisplayableObject(m_pCurSelectedObject);
			return;
		}
		m_pCurSelectedObject->UnselectThis();
	}
	//
	a_pDisplayObject->SelectThis();
	m_pCurSelectedObject = a_pDisplayObject;
	//
	m_pSelectCircle->Show(true);
	m_pSelectCircle->SetPosition(a_pDisplayObject->GetClickableWidget()->GetAbsolutePosition());
	//
}

void GameManager::ClickHabitableObject(HabitableObject* a_pHabObject)
{
	ClickDisplayableObject((DisplayableObject*)a_pHabObject);
	//
	m_pGameScene->SelectObject(a_pHabObject);
}

Game* GameManager::GetGameScene()
{
	return m_pGameScene;
}

void GameManager::GameUpdate(float a_DeltaT)
{
	if(m_pOrionSpur)
	{
		//increase the current date
		m_tLeftTimeTick -= a_DeltaT;

		if(m_tLeftTimeTick <= 0)
		{
			m_tLeftTimeTick = 1;
			//
			switch(m_CurTimeRate)
			{
			case(HOURLY):
				{
					mHours++;
					break;
				}
			case(DAILY):
				{
					mDays++;
					break;
				}
			case(WEEKLY):
				{
					mDays += 7;
					break;
				}
			case(MONTHLY):
				{
					mMonths++;
					break;
				}
			default:
				{
					std::cout << "Unknown time rate!" << std::endl;
					break;
				}
			}
			while(mHours >= HOURS_DAY)
			{
				mHours -= HOURS_DAY;
				mDays++;
			}
			while(mDays >= DAYS_WEEK * WEEKS_MONTH)
			{
				mDays -= DAYS_WEEK * WEEKS_MONTH;
				mMonths++;
			}
			while(mMonths >= MONTHS_YEAR)
			{
				mMonths -= MONTHS_YEAR;
				mYears++;
			}
			m_pGameScene->SetDate( num2string(mHours) + ":00, " + num2string(mDays) + "/" + num2string(mMonths) + "/" + num2string(mYears) );
		}

		for(auto it = m_HabitableObjects.begin(); it != m_HabitableObjects.end(); ++it)
		{
			(*it)->Update(a_DeltaT, m_CurTimeRate);
		}
	}
}

void GameManager::AddHabitableObject(HabitableObject* a_pNewHabObject)
{
	m_HabitableObjects.push_back(a_pNewHabObject);
}

void GameManager::HandleEvent(sf::Event& a_NewEvent)
{
	if(a_NewEvent.type == sf::Event::KeyPressed)
	{
		if(a_NewEvent.key.code == sf::Keyboard::Left || a_NewEvent.key.code == sf::Keyboard::Down)
		{
			if(int(m_CurTimeRate) - 1 >= PAUSED)
				m_CurTimeRate = TimeRate(int(m_CurTimeRate) - 1);
		}
		else if(a_NewEvent.key.code == sf::Keyboard::Right || a_NewEvent.key.code == sf::Keyboard::Up)
		{
			if(int(m_CurTimeRate) + 1 < int(MAXTIMEVAL))
				m_CurTimeRate = TimeRate(int(m_CurTimeRate) + 1);
		}
	}
}

void GameManager::UpdateStoredResource(Resource::ResourceType a_ResType, float a_Quantity, float a_Quality)
{
	GameManager::GetSingleton().GetGameScene()->mResourceValueLabels[a_ResType]->SetText(num2string( round(a_Quantity, 2) ) + " (Q " + num2string( round(a_Quality, 2) ) + ")");
}

void GameManager::UpdateSelectedInfrastructure(float a_NewInf)
{
	GameManager::GetSingleton().GetGameScene()->SetInf(a_NewInf);
}
