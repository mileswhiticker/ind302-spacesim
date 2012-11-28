#ifndef TRADERS_HPP
#define TRADERS_HPP

class DisplayableObject;
#include <SFML\System\Vector2.hpp>
namespace sf
{
	class Sprite;
	class Texture;
};

class Trader
{
public:
	Trader();
	void JumpToLocation(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords = sf::Vector2f());
	//
private:
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTexture;
	//
	DisplayableObject* m_pCurrentLocation;
	sf::Vector2f m_Coords;
	//
};

#endif	//TRADERS_HPP