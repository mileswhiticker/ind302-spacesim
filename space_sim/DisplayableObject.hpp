#ifndef DISPLAYABLE_OBJECT_HPP
#define DISPLAYABLE_OBJECT_HPP

#include <SFML\System\Vector2.hpp>

class DisplayableObject
{
public:
	sf::Vector2f GetRelPosition();
	//
protected:
	sf::Vector2f mRelPosition;
	//
private:
	//
};

#endif	//DISPLAYABLE_OBJECT_HPP