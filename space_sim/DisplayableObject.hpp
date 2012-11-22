#ifndef DISPLAYABLE_OBJECT_HPP
#define DISPLAYABLE_OBJECT_HPP

#include <SFGUI\Widget.hpp>
#include <SFGUI\Button.hpp>
#include <SFGUI\GLCanvas.hpp>
#include <SFGUI\Image.hpp>
#include <SFML\System\Vector2.hpp>

#include "Defines_Time.h"

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
		STAR,
		//
		MAXVAL
	};
	DisplayableObject(DisplayableType a_Type, DisplayableObject* a_pParent);
	~DisplayableObject();
	//
	virtual void OnClick();
	virtual void GenerateContents()=0;
	virtual void GenerateButtons();
	virtual void ShowContents(bool a_Visible = true);
	//
	virtual void CreateButton();
	virtual void ShowButton(bool a_Visible = true);
	//
	DisplayableType GetDisplayableType();
	sf::Vector2f GetRelPosition();
	//
	virtual void SelectThis();
	virtual void UnselectThis();
	//
	DisplayableObject* GetParent();
	sfg::Image::Ptr GetClickableWidget();
	std::string GetBGName();
	//
	void Render();
	bool IsAlsoHabitableObject();
	//
protected:
	sf::Vector2f mRelPosition;
	bool mGeneratedContents;
	std::vector<DisplayableObject*> mContents;
	bool mGeneratedButtons;
	std::vector<sfg::Widget::Ptr> mContentsButtons;
	std::string m_ImageName;
	std::string m_BGImageName;
	//
	bool mIsHabitableObject;
	bool mIsSelected;
	DisplayableObject* m_pParentObject;
	//
private:
	DisplayableType mMyDisplayableType;
	sfg::Button::Ptr m_pButton;
	sfg::Image::Ptr m_pSFGImage;
	//
	sf::Image* m_pButtonImage;
	//
	sfg::GLCanvas::Ptr m_pGLCanvasButton;
};

#endif	//DISPLAYABLE_OBJECT_HPP