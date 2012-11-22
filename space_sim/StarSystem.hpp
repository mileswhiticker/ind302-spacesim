#ifndef STAR_SYSTEM_HPP
#define STAR_SYSTEM_HPP

// Includes
#include <vector>
#include <SFML\System\Vector2.hpp>

#include "DisplayableObject.hpp"

// Predeclares
class HabitableObject;
class AsteroidBelt;
class StellarGroup;

class StarSystem
:	public DisplayableObject
{
public:
	StarSystem(StellarGroup* a_pOwningGroup, bool a_IsHomeSystem = false);
	~StarSystem();
	void Generate();
	//
private:
	// All habitable objects
	std::vector<HabitableObject*> mHabitableObjects;
	sf::Vector2f mRelPosition;
	AsteroidBelt& mAsteroidBelt;
	bool mIsNebula;
	StellarGroup* m_pOwningGroup;
};

#endif	//STAR_SYSTEM_HPP