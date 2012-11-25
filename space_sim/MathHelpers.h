#ifndef DEFINES_MATH_H
#define DEFINES_MATH_H

#define PI 3.14159265f

//helper functions
float fRand();
int iRand();
float fRand(float a_Min, float a_Max);
int iRand(int a_Min, int a_Max);
float fRand(float a_Max);
int iRand(int a_Max);

bool prob(int a_PercentChance);

float max(float a_ValueOne, float a_ValueTwo);
float min(float a_ValueOne, float a_ValueTwo);

float AverageWeight(float a_WeightOne, float a_QuantityOne, float a_WeightTwo, float a_QuantityTwo);

double round(double a_InitialValue, int a_MaxNumDecimals);

//cube root
float curt(float input);

#endif	//DEFINES_MATH_H