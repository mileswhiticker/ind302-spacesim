#ifndef STELLAR_GROUP_HPP
#define STELLAR_GROUP_HPP

#include <vector>
#include <SFML\System\Vector2.hpp>

#include "DisplayableObject.hpp"

class StarSystem;
class OrionSpur;

class StellarGroup
:	public DisplayableObject
{
public:
	StellarGroup(OrionSpur* a_pParent, bool a_IsLocalGroup = false);
	~StellarGroup();
	//
	virtual void GenerateContents();
	//
private:
	float mDiameter;
	int mNumStarSystems;
	//
};

#endif	//STELLAR_GROUP_HPP