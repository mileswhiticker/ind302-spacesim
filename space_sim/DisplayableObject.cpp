#include "DisplayableObject.hpp"

#include "GameManager.hpp"
#include <iostream>

DisplayableObject::DisplayableObject(DisplayableType a_Type, DisplayableObject* a_pParent)
:	mMyDisplayableType(a_Type)
,	mGeneratedContents(false)
,	m_pParentObject(a_pParent)
{
	//
}

DisplayableObject::~DisplayableObject()
{
	//
}

sf::Vector2f DisplayableObject::GetRelPosition()
{
	return mRelPosition;
}

void DisplayableObject::OnClick()
{
	//std::cout << mRelPosition.x << "x, " << mRelPosition.x << "y" << std::endl;
	GameManager::GetSingleton().ViewDisplayableObject(this);
}

DisplayableObject::DisplayableType DisplayableObject::GetDisplayableType()
{
	return mMyDisplayableType;
}

void DisplayableObject::DisplayContents()
{
	for(auto it = mContentsButtons.begin(); it != mContentsButtons.end(); ++it)
	{
		(*it)->Show(true);
	}
}

void DisplayableObject::HideContents()
{
	for(auto it = mContentsButtons.begin(); it != mContentsButtons.end(); ++it)
	{
		(*it)->Show(false);
	}
}

DisplayableObject* DisplayableObject::GetParent()
{
	return m_pParentObject;
}
