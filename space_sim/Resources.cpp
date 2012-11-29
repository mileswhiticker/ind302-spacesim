#include "Resources.h"

bool IsCriticalResource(Resource::ResourceType a_ResType)
{
	if(a_ResType == Resource::FUEL)
		return true;
	if(a_ResType == Resource::WATER)
		return true;
	if(a_ResType == Resource::FOOD)
		return true;
	if(a_ResType == Resource::OXYGEN)
		return true;
	//
	return false;
}

bool IsImportantResource(Resource::ResourceType a_ResType)
{
	if(a_ResType == Resource::COMPONENTS)
		return true;
	if(a_ResType == Resource::CIRCUITRY)
		return true;
	if(a_ResType == Resource::SHEETMETAL)
		return true;
	if(a_ResType == Resource::GIRDERS)
		return true;
	//
	return false;
}
