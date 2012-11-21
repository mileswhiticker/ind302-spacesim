#ifndef DISPLAYABLE_OBJECT_HPP
#define DISPLAYABLE_OBJECT_HPP

#include <SFGUI\Widget.hpp>
#include <SFML\System\Vector2.hpp>

class DisplayableObject
{
public:
	enum DisplayableType
	{
		ORIONSPUR,
		STELLARGROUP,
		STARSYSTEM,
		PLANET,
		ASTEROIDBELT,
		//
		MAXVAL
	};
	DisplayableObject(DisplayableType a_Type, DisplayableObject* a_pParent);
	~DisplayableObject();
	//
	void OnClick();
	virtual void DisplayContents();
	virtual void HideContents();
	DisplayableType GetDisplayableType();
	sf::Vector2f GetRelPosition();
	//
	DisplayableObject* GetParent();
protected:
	sf::Vector2f mRelPosition;
	virtual void GenerateContents()=0;
	bool mGeneratedContents;
	std::vector<DisplayableObject*> mContents;
	std::vector<sfg::Widget::Ptr> mContentsButtons;
	//
	DisplayableObject* m_pParentObject;
	//
private:
	DisplayableType mMyDisplayableType;
	//
};

#endif	//DISPLAYABLE_OBJECT_HPP