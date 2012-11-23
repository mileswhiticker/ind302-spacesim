#ifndef INDUSTRY_H
#define INDUSTRY_H

namespace Industry
{
	enum IndustryType
	{
		//utility infrastructure
		ATMOSPHERICS = 0,
		POWER_GENERATION,
		STORAGE,

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
		MACHINERY_PRODUCTION,
		LUXURYGOODS_PRODUCTION,

		//ships (yearly)
		SHIP_PRODUCTION,

		MAXVAL
	};
};

#endif	//INDUSTRY_H