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
	case(Resource::WATERCRYSTALS):
		{
			return "WATERCRYSTALS";
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
	/*case(Resource::MACHINERY):
		{
			return "MACHINERY";
			break;
		}*/
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
	/*case(Resource::PERFLUOROCARBONS):
		{
			return "PERFLUOROCARBONS";
			break;
		}*/
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

std::string GetInfrastructureStringname(Infrastructure::InfrastructureType a_InfType)
{
	switch(a_InfType)
	{
	default:
		{
			return "unknown";
			break;
		}
	case(Infrastructure::MAXVAL):
		{
			return "uninitialised";
			break;
		}
	case(Infrastructure::ATMOSPHERICS):
		{
			return "ATMOSPHERICS";
			break;
		}
	case(Infrastructure::COMMERCIAL):
		{
			return "COMMERCIAL";
			break;
		}
	/*case(Infrastructure::DISPOSAL):
		{
			return "DISPOSAL";
			break;
		}*/
	case(Infrastructure::DOCKING):
		{
			return "DOCKING";
			break;
		}
	case(Infrastructure::DOMESTICGOODS_PRODUCTION):
		{
			return "DOMESTICGOODS_PRODUCTION";
			break;
		}
	case(Infrastructure::ELECTRONICS_PRODUCTION):
		{
			return "ELECTRONICS_PRODUCTION";
			break;
		}
	case(Infrastructure::FOOD_PROCESSING):
		{
			return "FOOD_PROCESSING";
			break;
		}
	case(Infrastructure::FUEL_PROCESSING):
		{
			return "FUEL_PROCESSING";
			break;
		}
	case(Infrastructure::GAS_PROCESSING):
		{
			return "GAS_PROCESSING";
			break;
		}
	case(Infrastructure::LUXURYGOODS_PRODUCTION):
		{
			return "LUXURYGOODS_PRODUCTION";
			break;
		}
	/*case(Infrastructure::MACHINERY_PRODUCTION):
		{
			return "MACHINERY_PRODUCTION";
			break;
		}*/
	case(Infrastructure::MATERIALS_PRODUCTION):
		{
			return "MATERIALS_PRODUCTION";
			break;
		}
	case(Infrastructure::MINING):
		{
			return "MINING";
			break;
		}
	case(Infrastructure::POWER_GENERATION):
		{
			return "POWER_GENERATION";
			break;
		}
	case(Infrastructure::RESIDENTIAL):
		{
			return "RESIDENTIAL";
			break;
		}
	case(Infrastructure::SCRAP_RECYCLING):
		{
			return "SCRAP_RECYCLING";
			break;
		}
	case(Infrastructure::SHIP_PRODUCTION):
		{
			return "SHIP_PRODUCTION";
			break;
		}
	case(Infrastructure::STORAGE):
		{
			return "STORAGE";
			break;
		}
	case(Infrastructure::WASTE_RECYCLING):
		{
			return "WASTE_RECYCLING";
			break;
		}
	case(Infrastructure::WATER_PURIFICATION):
		{
			return "WATER_PURIFICATION";
			break;
		}
	}
}

Infrastructure::InfrastructureType GetIndustryFromResource(Resource::ResourceType a_ResType)
{
	switch(a_ResType)
	{
	default:
	case(Resource::MAXVAL):
	case(Resource::ORGANICWASTE):
	case(Resource::SCRAPWASTE):
		{
			return Infrastructure::MAXVAL;
		}
	case(Resource::WATERCRYSTALS):
	case(Resource::METALLIC):
	case(Resource::SILICACEOUS):
	case(Resource::CARBONACEOUS):
		{
			return Infrastructure::MINING;
		}
	case(Resource::CIRCUITRY):
	case(Resource::COMPONENTS):
		{
			return Infrastructure::ELECTRONICS_PRODUCTION;
		}
	case(Resource::DOMESTICGOODS):
		{
			return Infrastructure::DOMESTICGOODS_PRODUCTION;
		}
	case(Resource::FOOD):
		{
			return Infrastructure::FOOD_PROCESSING;
		}
	case(Resource::FUEL):
		{
			return Infrastructure::FUEL_PROCESSING;
		}
	case(Resource::GIRDERS):
	case(Resource::SHEETMETAL):
		{
			return Infrastructure::MATERIALS_PRODUCTION;
		}
	case(Resource::WATER):
		{
			return Infrastructure::WATER_PURIFICATION;
		}
	case(Resource::OXYGEN):
	case(Resource::HYDROGEN):
	//case(Resource::PERFLUOROCARBONS):
		{
			return Infrastructure::GAS_PROCESSING;
		}
	case(Resource::LUXURYGOODS):
		{
			return Infrastructure::LUXURYGOODS_PRODUCTION;
		}
	/*case(Resource::MACHINERY):
		{
			return Infrastructure::MACHINERY_PRODUCTION;
		}*/
	}
}
