#ifndef STELLAR_GROUP_HPP
#define STELLAR_GROUP_HPP

#include <vector>
#include <SFML\System\Vector2.hpp>

class StarSystem;

class StellarGroup
{
public:
	StellarGroup(bool a_IsLocalGroup = false);
	~StellarGroup();
	void Generate();
	//
private:
	float mDiameter;
	sf::Vector2f mRelPosition;
	int mNumStarSystems;
	//
	std::vector<StarSystem*> mStarSystems;
};

#endif	//STELLAR_GROUP_HPP