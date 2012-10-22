#include "Defines_Math.h"

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
	return a_Min + int(fRand() * (a_Max - a_Min));
}

float fRand(float a_Max)
{
	return fRand() * a_Max;
}

int iRand(int a_Max)
{
	return int(fRand() * a_Max);
}

float curt(float input)
{
	return pow(input, 1.f/3.f);
}
