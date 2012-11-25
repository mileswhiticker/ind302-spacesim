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

	struct ResRequirement
	{
		ResRequirement(ResourceType a_MyType, float a_Amount)
		:	resType(a_MyType)
		,	amount(a_Amount)
		{
			//
		}
		ResourceType resType;
		float amount;
	};

	static std::map<ResourceType, std::vector<ResRequirement>> Requirements;
};

#define NUM_RAW_MATERIALS int(Resource::FOOD)
#define NUM_PRODUCED_GOODS (int(Resource::MAXVAL) - NUM_RAW_MATERIALS)

#endif	//RESOURCES_HPP