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
	StarSystem(StellarGroup* a_pParent, bool a_IsHomeSystem = false);
	~StarSystem();
	//
	//virtual void HideContents();
	//
protected:
	void GenerateContents();
	//
private:
	//AsteroidBelt& mAsteroidBelt;
	bool mIsNebula;
};

#endif	//STAR_SYSTEM_HPP