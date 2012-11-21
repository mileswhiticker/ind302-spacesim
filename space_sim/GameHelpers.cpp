#include "GameHelpers.hpp"

std::string GetDisplayStringname(DisplayableObject::DisplayableType a_DisplayType)
{
	switch(a_DisplayType)
	{
	case(DisplayableObject::ORIONSPUR):
		{
			return "ORIONSPUR";
			break;
		}
	case(DisplayableObject::STELLARGROUP):
		{
			return "STELLARGROUP";
			break;
		}
	case(DisplayableObject::STARSYSTEM):
		{
			return "STARSYSTEM";
			break;
		}
	case(DisplayableObject::PLANET):
		{
			return "PLANET";
			break;
		}
	case(DisplayableObject::ASTEROIDBELT):
		{
			return "ASTEROIDBELT";
			break;
		}
	case(DisplayableObject::MAXVAL):
		{
			return "uninitialised";
			break;
		}
	default:
		{
			return "unknown";
			break;
		}
	}
}
