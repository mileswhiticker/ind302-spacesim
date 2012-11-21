#ifndef HABITABLE_OBJECT_HPP
#define HABITABLE_OBJECT_HPP

class StarSystem;

//abstract base class for all colonisable entities in space (including space stations)
class HabitableObject
{
public:
	enum HabitableType
	{
		INVALID = 0,
		//
		PLANET_TERRAN,
		PLANET_GAIAN,
		PLANET_ICE,
		PLANET_GASGIANT,
		//
		ASTEROID_CARBONACEOUS,
		ASTEROID_SILICACEOUS,
		ASTEROID_METALLIC,
		ASTEROID_BELT,
		//
		SPACESTATION,
		//
		MAXVAL
	};
	HabitableObject();
	virtual ~HabitableObject()=0;
	//
	StarSystem* GetOrbitingStarSystem();
	HabitableObject* GetOrbitingObject();
	HabitableType GetHabitableType();
	//
protected:
	//sample vars - NYI
	HabitableType mMyHabitableType;
	int mPopulation;
	//
	StarSystem* m_pOrbitingStarSystem;
	HabitableObject* m_pOrbitingObject;
};

#endif	//HABITABLE_OBJECT_HPP