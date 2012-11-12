#ifndef ORION_SPUR_HPP
#define ORION_SPUR_HPP

#include <vector>
class StellarGroup;

class OrionSpur
{
public:
	//two very powerful functions, be careful
	static bool Generate();
	static bool Clear();
	//
	static std::vector<StellarGroup*> GetStellarGroups();
	//
private:
	OrionSpur();
	//
};

#endif	//ORION_SPUR_HPP