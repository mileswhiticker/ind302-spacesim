#include "GameManager.hpp"

#include "Planet.hpp"

#define NULL 0

static Planet* m_pHomePlanet = NULL;

GameManager::GameManager()
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
