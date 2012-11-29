#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <vector>
#include <map>

namespace Resource
{
	enum ResourceType
	{
		CARBONACEOUS = 0,
		SILICACEOUS,
		METALLIC,
		WATERCRYSTALS,
		//
		HYDROGEN,
		//PERFLUOROCARBONS,
		OXYGEN,
		//
		ORGANICWASTE,
		SCRAPWASTE,
		//
		FOOD,
		WATER,
		FUEL,
		//
		GIRDERS,
		SHEETMETAL,
		COMPONENTS,
		CIRCUITRY,
		//
		//MACHINERY,
		DOMESTICGOODS,
		LUXURYGOODS,
		//
		MAXVAL
	};
};

bool IsCriticalResource(Resource::ResourceType a_ResType);
bool IsImportantResource(Resource::ResourceType a_ResType);

#define NUM_RAW_MATERIALS int(Resource::FOOD)
#define NUM_PRODUCED_GOODS (int(Resource::MAXVAL) - NUM_RAW_MATERIALS)

#endif	//RESOURCES_HPP