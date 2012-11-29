#ifndef GAME_HELPERS_HPP
#define GAME_HELPERS_HPP

#include "DisplayableObject.hpp"
#include "HabitableObject.hpp"

std::string GetDisplayStringname(DisplayableObject::DisplayableType a_DisplayType);
std::string GetHabitableStringname(HabitableObject::HabitableType a_HabitableType);

std::string GetResourceStringname(Resource::ResourceType a_ResourceType);
std::string GetInfrastructureStringname(Infrastructure::InfrastructureType a_InfType);

Infrastructure::InfrastructureType GetIndustryFromResource(Resource::ResourceType a_ResType);

std::string GetRandomName(DisplayableObject::DisplayableType a_DispType);

std::string GetRandomTraderName();

#endif	//GAME_HELPERS_HPP