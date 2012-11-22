#include "DisplayableObject.hpp"

#include "GameManager.hpp"
#include "SFGManager.hpp"
#include "AppManager.hpp"

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <iostream>

static sf::Sprite* g_pStellarGroupSprite = NULL;

DisplayableObject::DisplayableObject(DisplayableType a_Type, DisplayableObject* a_pParent)
:	mMyDisplayableType(a_Type)
,	mGeneratedContents(false)
,	mGeneratedButtons(false)
,	m_pParentObject(a_pParent)
,	m_pButtonImage(NULL)
,	mIsHabitableObject(false)
{
	switch(mMyDisplayableType)
	{
	case(DisplayableObject::STELLARGROUP):
		{
			m_ImageName = "../media/group.png";
			m_BGImageName = "../media/stellargroup_bg.png";
			break;
		}
	case(DisplayableObject::STARSYSTEM):
		{
			m_ImageName = "../media/system.png";
			m_BGImageName = "../media/starsystem_bg.png";
			break;
		}
	case(DisplayableObject::STAR):
		{
			m_ImageName = "../media/star.png";
			m_BGImageName = "../media/star2.png";
			break;
		}
	case(DisplayableObject::ORIONSPUR):
		{
			m_ImageName = "../media/broke.png";
			m_BGImageName = "../media/orionspur_bg.png";
			break;
		}
	default:
		{
			m_ImageName = "../media/broke.png";
			m_BGImageName = "../media/starry.jpg";
			break;
		}
	}
}

DisplayableObject::~DisplayableObject()
{
	if(m_pButton.get())
	{
		ClearWidget(m_pButton->GetImage());
		ClearWidget(m_pButton);
	}
	if(m_pSFGImage.get())
	{
		ClearWidget(m_pSFGImage);
	}
}

sf::Vector2f DisplayableObject::GetRelPosition()
{
	return mRelPosition;
}

void DisplayableObject::OnClick()
{
	//std::cout << "DisplayableObject::OnClick()" << std::endl;
	GameManager::GetSingleton().ClickDisplayableObject(this);
}

DisplayableObject::DisplayableType DisplayableObject::GetDisplayableType()
{
	return mMyDisplayableType;
}

void DisplayableObject::ShowContents(bool a_Visible)
{
	if(!mGeneratedContents && a_Visible)
		GenerateContents();
	//
	for(auto it = mContents.begin(); it != mContents.end(); ++it)
	{
		(*it)->ShowButton(a_Visible);
	}
}

DisplayableObject* DisplayableObject::GetParent()
{
	return m_pParentObject;
}

#define SPRITE_DIM 32

void DisplayableObject::CreateButton()
{
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	windowDims.x = windowDims.x * (5.f/6.f) - SPRITE_DIM;
	windowDims.y = windowDims.y * (5.f/6.f) - SPRITE_DIM;
	
	//gl canvas
	/*if(!g_pStellarGroupSprite)
	{
		sf::Texture* pTexture = new sf::Texture();
		pTexture->loadFromFile("../media/group.png");
		g_pStellarGroupSprite = new sf::Sprite(*pTexture);
	}

	m_pGLCanvasButton = sfg::GLCanvas::Create();
	m_pGLCanvasButton->GetCustomDrawCallbackSignal().Connect(&DisplayableObject::Render, this);
	m_pGLCanvasButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, this);
	
	m_pGLCanvasButton->Show(false);
	AddWidget(m_pGLCanvasButton);*/

	//image
	m_pButtonImage = new sf::Image();
	m_pButtonImage->loadFromFile(m_ImageName);

	m_pSFGImage = sfg::Image::Create(*m_pButtonImage);
	m_pSFGImage->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)this);
	//
	sf::FloatRect allocation;
	allocation.top = windowDims.y * mRelPosition.y;
	allocation.height = SPRITE_DIM;
	allocation.left = windowDims.x * mRelPosition.x;
	allocation.width = SPRITE_DIM;
	m_pSFGImage->SetAllocation(allocation);
	m_pSFGImage->Show(false);
	AddWidget(m_pSFGImage);

	//buttons
	/*m_pButton = sfg::Button::Create("");
	m_pButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&DisplayableObject::OnClick, (DisplayableObject*)this);
	
	m_pButtonImage = new sf::Image();
	m_pButtonImage->loadFromFile(m_ImageName);
	sfg::Image::Ptr pSFGImage = sfg::Image::Create(*m_pButtonImage);
	pSFGImage->SetImage(*m_pButtonImage);
	m_pButton->SetImage(pSFGImage);

	sf::FloatRect allocation;
	allocation.top = windowDims.y * mRelPosition.y;
	allocation.height = 12;
	allocation.left = windowDims.x * mRelPosition.x;
	allocation.width = 12;
	m_pButton->SetAllocation(allocation);
	//
	//mContentsButtons.push_back(m_pButton);
	AddWidget(m_pButton);
	m_pButton->Show(false);*/
}

void DisplayableObject::ShowButton(bool a_Visible)
{
	if(!m_pSFGImage.get())
		CreateButton();
	m_pSFGImage->Show(a_Visible);
}

void DisplayableObject::GenerateButtons()
{
	#pragma omp for
	for(auto it = mContents.begin(); it != mContents.end(); ++it)
	{
		#pragma omp atomic
		(*it)->CreateButton();
	}
	//
	mGeneratedButtons = true;
}

void DisplayableObject::SelectThis()
{
	/*if(m_pButton.get())
	{
		m_pButtonImage->loadFromFile(m_SelectedImageName);
		m_pButton->GetImage()->SetImage(*m_pButtonImage);
		//m_pButton->GetImage()->GetImage().loadFromFile(m_SelectedImageName);
	}*/
}

void DisplayableObject::UnselectThis()
{
	/*if(m_pButton.get())
	{
		m_pButtonImage->loadFromFile(m_ImageName);
		m_pButton->GetImage()->SetImage(*m_pButtonImage);
		//const_cast<sf::Image&>(m_pButton->GetImage()->GetImage()).loadFromFile(m_ImageName);
	}*/
}

void DisplayableObject::Render()
{
	sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
	windowDims.x *= 5.f/6.f;
	windowDims.y *= 5.f/6.f;
	//
	g_pStellarGroupSprite->setPosition(mRelPosition.x * windowDims.x, mRelPosition.y * windowDims.y);
	AppManager::GetSingleton().GetRenderTarget().draw(*g_pStellarGroupSprite);
}

sfg::Image::Ptr DisplayableObject::GetClickableWidget()
{
	return m_pSFGImage;
}

bool DisplayableObject::IsAlsoHabitableObject()
{
	return mIsHabitableObject;
}

std::string DisplayableObject::GetBGName()
{
	return m_BGImageName;
}
