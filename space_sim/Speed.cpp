#include "Speed.hpp"

#include <map>

std::map<TimeRate, std::map<DisplayableObject::DisplayableType, float>> SpeedMap;

void Init()
{
	if(!SpeedMap.size())
	{
		SpeedMap.insert( std::pair<TimeRate, std::map<DisplayableObject::DisplayableType, float>>(PAUSED, std::map<DisplayableObject::DisplayableType, float>()) );
		//
		SpeedMap[PAUSED].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::ORIONSPUR, 0.f) );
		SpeedMap[PAUSED].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STELLARGROUP, 0.f) );
		SpeedMap[PAUSED].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STARSYSTEM, 0.f) );
		SpeedMap[PAUSED].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::PLANET, 0.f) );

		SpeedMap.insert( std::pair<TimeRate, std::map<DisplayableObject::DisplayableType, float>>(HOURLY, std::map<DisplayableObject::DisplayableType, float>()) );
		//
		SpeedMap[HOURLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::ORIONSPUR, MONTHS_ORIONSPUR * WEEKS_MONTH * DAYS_WEEK * HOURS_DAY) );
		SpeedMap[HOURLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STELLARGROUP, WEEKS_STELLARGROUP * DAYS_WEEK * HOURS_DAY) );
		SpeedMap[HOURLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STARSYSTEM, DAYS_STARSYSTEM * HOURS_DAY) );
		SpeedMap[HOURLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::PLANET, HOURS_PLANET) );

		SpeedMap.insert( std::pair<TimeRate, std::map<DisplayableObject::DisplayableType, float>>(DAILY, std::map<DisplayableObject::DisplayableType, float>()) );
		//
		SpeedMap[DAILY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::ORIONSPUR, MONTHS_ORIONSPUR * WEEKS_MONTH * DAYS_WEEK) );
		SpeedMap[DAILY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STELLARGROUP, WEEKS_STELLARGROUP * DAYS_WEEK) );
		SpeedMap[DAILY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STARSYSTEM, DAYS_STARSYSTEM) );
		SpeedMap[DAILY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::PLANET, HOURS_PLANET / float(HOURS_DAY)) );

		SpeedMap.insert( std::pair<TimeRate, std::map<DisplayableObject::DisplayableType, float>>(WEEKLY, std::map<DisplayableObject::DisplayableType, float>()) );
		//
		SpeedMap[WEEKLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::ORIONSPUR, MONTHS_ORIONSPUR * WEEKS_MONTH) );
		SpeedMap[WEEKLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STELLARGROUP, WEEKS_STELLARGROUP) );
		SpeedMap[WEEKLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STARSYSTEM, DAYS_STARSYSTEM / float(DAYS_WEEK)) );
		SpeedMap[WEEKLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::PLANET, HOURS_PLANET / float(HOURS_DAY * DAYS_WEEK)) );

		SpeedMap.insert( std::pair<TimeRate, std::map<DisplayableObject::DisplayableType, float>>(MONTHLY, std::map<DisplayableObject::DisplayableType, float>()) );
		//
		SpeedMap[MONTHLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::ORIONSPUR, MONTHS_ORIONSPUR) );
		SpeedMap[MONTHLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STELLARGROUP, WEEKS_STELLARGROUP / float(WEEKS_MONTH)) );
		SpeedMap[MONTHLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::STARSYSTEM, DAYS_STARSYSTEM / float(WEEKS_MONTH * DAYS_WEEK)) );
		SpeedMap[MONTHLY].insert( std::pair<DisplayableObject::DisplayableType, float>(DisplayableObject::PLANET, HOURS_PLANET / float(HOURS_DAY * WEEKS_MONTH * DAYS_WEEK)) );
	}
}

float GetRealtimeToCross(TimeRate a_TimeRate, DisplayableObject::DisplayableType a_DispType)
{
	if(!SpeedMap.size())
		Init();
	//
	return SpeedMap[a_TimeRate][a_DispType];
}
