#ifndef INDUSTRY_H
#define INDUSTRY_H

#define BASICGOODS_PRODUCTION_MULTI 10.f
//#define METAL_USAGE_RATIO 0.8f

#define POWERUSE_PER_INF 0.1f		//1 unit of powergen provides for 10 units of total inf
#define ATMOSUSE_PER_INF 0.1f		//1 unit of atmos processing provides for 10 units of total inf
#define POWER_FUEL_CONSUMPTION 0.1f	//1 unit of fuel provides 10 ticks of 1 unit of power
#define CRITICAL_SAFETY_MARGIN 0.1f	//extra breathing room for infrastructure and planning

#define	SPACE_PER_STORAGE 100000		//number of units storable per storage unit
#define STORAGE_CAPACITY_TIME 12	//number of months until storage is at full capacity with current production rate
#define DOCKING_PER_STORE 0.1f		//units of docking per storage

#define POP_PER_RESIDENTIAL 100	//number of people per residential unit
#define POP_GROWTH_ROOM	0.1f		//extra housing room
#define FOOD_PERPERSON_PERDAY 1.f	//units of food each person consumes in a day
#define WATER_PERPERSON_PERDAY 2.f	//units of food each person consumes in a day
#define OXY_PERPERSON_PERDAY 1.f
#define POP_GROWTH_CEILING 0.05f
#define POP_GROWTH_FLOOR 0.1f
#define NATDEATH_GROWTH_CEILING 0.01f
#define NATDEATH_GROWTH_FLOOR 0.05f

#define LOWLEVEL_PRODUCTION_MULTI 100			//multiplier applied to components, circuitry, sheetmetal and girders

#define FOOD_PRODUCTION_MULTI 100.f
#define WATER_PRODUCTION_MULTI 10.f
#define FUEL_PRODUCTION_MULTI 10

#define COMMERCIAL_TO_RESIDENTIAL_RATIO 0.25f
#define SHIPBUILDING_TO_COMMERCIAL_RATIO 0.25f
#define MIN_COMMERCIAL_FOR_SHIPBUILDING 1

#define WASTE_PROCESSING_MULTIPLIER 100
#define SCRAP_PROCESSING_MULTIPLIER 100

#define LUXURYGOODS_CONSUMPTION_PPERSON 0.0001f
#define DOMESTICGOODS_CONSUMPTION_PPERSON 0.001f

#define MINING_MULTI 0.01f

namespace Infrastructure
{
	enum InfrastructureType
	{
		//utility infrastructure
		ATMOSPHERICS = 0,
		POWER_GENERATION,
		STORAGE,
		DOCKING,
		RESIDENTIAL,
		COMMERCIAL,

		//ships (yearly)
		SHIP_PRODUCTION,

		//low level infrastructure (daily processing)
		WASTE_RECYCLING,
		SCRAP_RECYCLING,
		DISPOSAL,
		//
		MINING,
		FUEL_PROCESSING,
		WATER_PURIFICATION,
		GAS_PROCESSING,

		//basic goods production (weekly)
		ELECTRONICS_PRODUCTION,
		MATERIALS_PRODUCTION,
		DOMESTICGOODS_PRODUCTION,

		//advanced goods production (monthly)
		FOOD_PROCESSING,
		//MACHINERY_PRODUCTION,
		LUXURYGOODS_PRODUCTION,

		MAXVAL
	};
};

#define CRITICAL_INF_START int(Infrastructure::ATMOSPHERICS)
#define CRITICAL_INF_END int(Infrastructure::POWER_GENERATION)

#define UTILITY_INF_START int(Infrastructure::STORAGE)
#define UTILITY_INF_END int(Infrastructure::SHIP_PRODUCTION)

#define LOWLEVEL_INF_START int(Infrastructure::WASTE_RECYCLING)
#define LOWLEVEL_INF_END int(Infrastructure::GAS_PROCESSING)

#define BASIC_INF_START int(Infrastructure::ELECTRONICS_PRODUCTION)
#define BASIC_INF_END int(Infrastructure::DOMESTICGOODS_PRODUCTION)

#define ADV_INF_START int(Infrastructure::FOOD_PROCESSING)
#define ADV_INF_END int(Infrastructure::LUXURYGOODS_PRODUCTION)

#endif	//INDUSTRY_H