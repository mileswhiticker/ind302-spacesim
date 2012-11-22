#ifndef STELLAR_GROUP_HPP
#define STELLAR_GROUP_HPP

#include <vector>
#include <SFML\System\Vector2.hpp>

#include "DisplayableObject.hpp"

class StarSystem;

class StellarGroup
:	public DisplayableObject
{
public:
	StellarGroup(bool a_IsLocalGroup = false);
	~StellarGroup();
	void Generate();
	//
private:
	float mDiameter;
	int mNumStarSystems;
	//
	std::vector<StarSystem*> mStarSystems;
};

#endif	//STELLAR_GROUP_HPP