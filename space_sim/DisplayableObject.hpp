#ifndef DISPLAYABLE_OBJECT_HPP
#define DISPLAYABLE_OBJECT_HPP

#include <SFML\System\Vector2.hpp>

class DisplayableObject
{
public:
	sf::Vector2f GetRelPosition();
	enum DisplayableType
	{
		STELLARGROUP,
		STARSYSTEM,
		PLANET,
		//
		MAXVAL
	};
	//
	virtual void OnClick();
	DisplayableType GetDisplayableType();
	//
protected:
	sf::Vector2f mRelPosition;
	//
private:
	DisplayableType mMyDisplayableType;
	//
};

#endif	//DISPLAYABLE_OBJECT_HPP