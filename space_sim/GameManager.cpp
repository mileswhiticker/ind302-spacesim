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
,	m_CurTimeRate(HOURLY)
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

void GameManager::UpdateStoredResource(Resource::ResourceType a_ResType, float a_Quantity, float a_Quality)
{
	GameManager::GetSingleton().GetGameScene()->mResourceValueLabels[a_ResType]->SetText(num2string( round(a_Quantity, 2) ) + " (Q " + num2string( round(a_Quality, 2) ) + ")");
}

Game* GameManager::GetGameScene()
{
	return m_pGameScene;
}

void GameManager::GameUpdate(float a_DeltaT)
{
	if(m_pOrionSpur)
	{
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
