#include "Planet.hpp"

#include "StarSystem.hpp"
#include "MathHelpers.h"
#include "GameHelpers.hpp"

Planet::Planet(StarSystem* a_pParent, HabitableObject::HabitableType a_NewType)
//:	DisplayableObject(DisplayableObject::PLANET, a_pParent)
:	HabitableObject(a_NewType, a_pParent)
{
	mMyHabitableType = a_NewType;
	DisplayableObject::mIsHabitableObject = true;
	//
	mRelPosition.x = fRand();
	mRelPosition.y = fRand();
	//
	switch(a_NewType)
	{
	case(HabitableObject::PLANET_DEAD):
		{
			m_ImageName = "../media/planet_d.png";
			m_BGImageName = "../media/planet_d2.png";
			break;
		}
	case(HabitableObject::PLANET_GASGIANT):
		{
			m_ImageName = "../media/planet_g.png";
			m_BGImageName = "../media/planet_g2.png";
			break;
		}
	case(HabitableObject::PLANET_ICE):
		{
			m_ImageName = "../media/planet_i.png";
			m_BGImageName = "../media/planet_i2.png";
			break;
		}
	case(HabitableObject::PLANET_TERRAN):
		{
			m_ImageName = "../media/planet_t.png";
			m_BGImageName = "../media/planet_t2.png";
			break;
		}
	case(HabitableObject::ASTEROID_CARBONACEOUS):
	case(HabitableObject::ASTEROID_METALLIC):
	case(HabitableObject::ASTEROID_SILICACEOUS):
	default:
		{
			//don't need these yet?
			m_ImageName = "../media/broke.png";
			m_BGImageName = "../media/starry.jpg";
			break;
		}
	}
	//
	GenerateData();
	mObjName = GetRandomName(DisplayableObject::PLANET);
}

void Planet::GenerateContents()
{
	//GenerateData();
}

Star::Star(StarSystem* a_pParent)
:	DisplayableObject(DisplayableObject::STAR, a_pParent)
{
	//mMyHabitableType = HabitableObject::STAR;
	//
	mRelPosition.x = 0.5f;
	mRelPosition.y = 0.5f;
	//
	m_ImageName = "../media/star.png";
	m_BGImageName = "../media/star_bg.png";
}

void Star::GenerateContents()
{
	//
}
