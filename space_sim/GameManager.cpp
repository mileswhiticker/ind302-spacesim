#include "GameManager.hpp"

#include "StellarGroup.hpp"
#include "OrionSpur.hpp"
#include "Planet.hpp"
#include "StarSystem.hpp"

#include "Scene_Game.hpp"

#include "SFGManager.hpp"
#include "GameHelpers.hpp"
#include "SceneManager.hpp"
#include <iostream>

static Planet* m_pHomePlanet = NULL;

GameManager::GameManager()
:	m_CurView(DisplayableObject::MAXVAL)
,	m_pCurViewedObject(NULL)
,	m_pOrionSpur(NULL)
,	m_pGameScene(NULL)
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

void GameManager::Initialise(Game* a_pGameScene)
{
	//lay out the other displayable objects
	m_pOrionSpur = new OrionSpur();
	m_pGameScene = a_pGameScene;
	ViewDisplayableObject(m_pOrionSpur);

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

	//clear out the previous view
	ClearCurView();
	
	DisplayableObject::DisplayableType newType = a_pDisplayObject->GetDisplayableType();
	switch(newType)
	{
	default:
	case(DisplayableObject::ORIONSPUR):
		{
			newType = DisplayableObject::ORIONSPUR;
			m_pOrionSpur->DisplayContents();
			a_pDisplayObject = m_pOrionSpur;
			break;
		}
	case(DisplayableObject::STELLARGROUP):
		{
			StellarGroup* pStellarGroup = (StellarGroup*)a_pDisplayObject;
			pStellarGroup->DisplayContents();
			break;
		}
	case(DisplayableObject::STARSYSTEM):
		{
			StarSystem* pStarSystem = (StarSystem*)a_pDisplayObject;
			pStarSystem->DisplayContents();
			break;
		}
	}
	m_pCurViewedObject = a_pDisplayObject;
	std::cout << "	" << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " displaying contents" << std::endl;
	m_CurView = newType;
	m_pGameScene->ChangeView(m_pCurViewedObject);
}

void GameManager::ClearCurView()
{
	if(!m_pCurViewedObject)
		return;
	std::cout << GetDisplayStringname(m_pCurViewedObject->GetDisplayableType()) << " hiding contents" << std::endl;
	//setup special cases here
	/*switch(m_pCurViewedObject->GetDisplayableType())
	{
	default:
		{
			m_pCurViewedObject->HideContents();
			break;
		}
	}*/
	m_pCurViewedObject->HideContents();
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
