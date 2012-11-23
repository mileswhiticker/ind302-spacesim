#include "HabitableObject.hpp"

void HabitableObject::YearlyUpdate(int a_PropogationDir, int a_Quantity)
{
	//yearly logic here
	//annual financial transactions (tax, salaries etc)
	
	//two-way recursion
	//can not go any higher than this
	if(a_PropogationDir & DOWNWARD)
	{
		MonthlyUpdate(DOWNWARD, a_Quantity * MONTHS_YEAR);
	}
}
