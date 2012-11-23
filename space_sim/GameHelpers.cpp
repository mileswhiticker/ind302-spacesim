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
	case(DisplayableObject::STAR):
		{
			return "STAR";
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

std::string GetHabitableStringname(HabitableObject::HabitableType a_HabitableType)
{
	switch(a_HabitableType)
	{
	case(HabitableObject::MAXVAL):
		{
			return "uninitialised";
			break;
		}
	case(HabitableObject::ASTEROID_BELT):
		{
			return "asteroid belt";
			break;
		}
	case(HabitableObject::ASTEROID_CARBONACEOUS):
		{
			return "ASTEROID_CARBONACEOUS";
			break;
		}
	case(HabitableObject::ASTEROID_METALLIC):
		{
			return "ASTEROID_METALLIC";
			break;
		}
	case(HabitableObject::ASTEROID_SILICACEOUS):
		{
			return "ASTEROID_SILICACEOUS";
			break;
		}
	case(HabitableObject::PLANET_DEAD):
		{
			return "PLANET_DEAD";
			break;
		}
	case(HabitableObject::PLANET_GASGIANT):
		{
			return "PLANET_GASGIANT";
			break;
		}
	case(HabitableObject::PLANET_ICE):
		{
			return "PLANET_ICE";
			break;
		}
	case(HabitableObject::PLANET_TERRAN):
		{
			return "PLANET_TERRAN";
			break;
		}
	case(HabitableObject::SPACESTATION):
		{
			return "SPACESTATION";
			break;
		}
	case(HabitableObject::STAR):
		{
			return "STAR";
			break;
		}
	default:
		{
			return "unknown";
			break;
		}
	}
}

std::string GetResourceStringname(Resource::ResourceType a_ResourceType)
{
	switch(a_ResourceType)
	{
	default:
		{
			return "unknown";
			break;
		}
	case(Resource::MAXVAL):
		{
			return "uninitialised";
			break;
		}
	case(Resource::CARBONACEOUS):
		{
			return "CARBONACEOUS";
			break;
		}
	case(Resource::CIRCUITRY):
		{
			return "CIRCUITRY";
			break;
		}
	case(Resource::COMPONENTS):
		{
			return "COMPONENTS";
			break;
		}
	case(Resource::DOMESTICGOODS):
		{
			return "DOMESTICGOODS";
			break;
		}
	case(Resource::FOOD):
		{
			return "FOOD";
			break;
		}
	case(Resource::FUEL):
		{
			return "FUEL";
			break;
		}
	case(Resource::GIRDERS):
		{
			return "GIRDERS";
			break;
		}
	case(Resource::HYDROCARBON):
		{
			return "HYDROCARBON";
			break;
		}
	case(Resource::HYDROGEN):
		{
			return "HYDROGEN";
			break;
		}
	case(Resource::LUXURYGOODS):
		{
			return "LUXURYGOODS";
			break;
		}
	case(Resource::MACHINERY):
		{
			return "MACHINERY";
			break;
		}
	case(Resource::METALLIC):
		{
			return "METALLIC";
			break;
		}
	case(Resource::ORGANICWASTE):
		{
			return "ORGANICWASTE";
			break;
		}
	case(Resource::OXYGEN):
		{
			return "OXYGEN";
			break;
		}
	case(Resource::PERFLUOROCARBONS):
		{
			return "PERFLUOROCARBONS";
			break;
		}
	case(Resource::SCRAPWASTE):
		{
			return "SCRAPWASTE";
			break;
		}
	case(Resource::SILICACEOUS):
		{
			return "SILICACEOUS";
			break;
		}
	case(Resource::SHEETMETAL):
		{
			return "SHEETMETAL";
			break;
		}
	case(Resource::WATER):
		{
			return "WATER";
			break;
		}
	}
}
