#include "DisplayableObject.hpp"

#include <iostream>

sf::Vector2f DisplayableObject::GetRelPosition()
{
	return mRelPosition;
}

void DisplayableObject::OnClick()
{
	std::cout << mRelPosition.x << "x, " << mRelPosition.x << "y" << std::endl;
}

DisplayableObject::DisplayableType DisplayableObject::GetDisplayableType()
{
	return mMyDisplayableType;
}
