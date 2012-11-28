#include "Traders.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

Trader::Trader()
:	m_pCurrentLocation(NULL)
,	m_Coords(sf::Vector2f())
{
	//
}

void Trader::JumpToLocation(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords)
{
	m_Coords = a_Coords;
	m_pCurrentLocation = a_pNewLocation;
}
