#ifndef ORION_SPUR_HPP
#define ORION_SPUR_HPP

#include <vector>
#include <SFGUI\Widget.hpp>
#include "DisplayableObject.hpp"
class StellarGroup;

class OrionSpur
:	public DisplayableObject
{
public:
	OrionSpur();
	~OrionSpur();
	//
	virtual void DisplayContents();
	//virtual void HideContents();
	//
protected:
	void GenerateContents();
	//
private:
	int mNumStellarGroups;
	//
};

#endif	//ORION_SPUR_HPP