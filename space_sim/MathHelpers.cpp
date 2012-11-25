#include "MathHelpers.h"

#include <stdlib.h>
#include <math.h>

float fRand()
{
	return float(rand()) / RAND_MAX;
}

int iRand()
{
	return rand() % 100;
}

float fRand(float a_Min, float a_Max)
{
	return a_Min + fRand() * (a_Max - a_Min);
}

int iRand(int a_Min, int a_Max)
{
	return a_Min + rand() % (a_Max - a_Min);
}

float fRand(float a_Max)
{
	return fRand() * a_Max;
}

int iRand(int a_Max)
{
	return int(fRand() * a_Max);
}

bool prob(int a_PercentChance)
{
	if(a_PercentChance >= 100)
		return true;
	//
	if(fRand() < float(a_PercentChance) / 100.f)
		return true;
	return false;
}

float curt(float input)
{
	return pow(input, 1.f/3.f);
}

float AverageWeight(float a_WeightOne, float a_QuantityOne, float a_WeightTwo, float a_QuantityTwo)
{
	if(!a_WeightOne || !a_QuantityOne)
		return a_WeightTwo;
	//
	float weightTowardsOne = a_QuantityOne / (a_QuantityOne + a_QuantityTwo);
	return weightTowardsOne * a_WeightOne + (1 - weightTowardsOne) * a_WeightTwo;
}

double round(double a_InitialValue, int a_MaxNumDecimals)
{
	double power = pow(10.f, a_MaxNumDecimals);
	double modValue = a_InitialValue * power;
	modValue = double(int(modValue));
	return modValue / power;
}

float max(float a_ValueOne, float a_ValueTwo)
{
	return a_ValueOne > a_ValueTwo ? a_ValueOne : a_ValueTwo;
}

float min(float a_ValueOne, float a_ValueTwo)
{
	return a_ValueOne < a_ValueTwo ? a_ValueOne : a_ValueTwo;
}
