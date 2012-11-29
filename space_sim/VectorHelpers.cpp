#include "VectorHelpers.hpp"

#include <math.h>

float SquaredLength(sf::Vector2f a_Vector)
{
	return a_Vector.x * a_Vector.x + a_Vector.y * a_Vector.y;
}

float Length(sf::Vector2f a_Vector)
{
	return sqrt(a_Vector.x * a_Vector.x + a_Vector.y * a_Vector.y);
}

float Distance(sf::Vector2f a_VectorOne, sf::Vector2f a_VectorTwo)
{
	return Length(a_VectorTwo - a_VectorOne);
}

float SquaredDistance(sf::Vector2f a_VectorOne, sf::Vector2f a_VectorTwo)
{
	return SquaredLength(a_VectorTwo - a_VectorOne);
}

void Normalise(sf::Vector2f& a_StartVector)
{
	a_StartVector = NormaliseCopy(a_StartVector);
}

sf::Vector2f NormaliseCopy(sf::Vector2f a_StartVector)
{
	float length = Length(a_StartVector);
	a_StartVector.x /= length;
	a_StartVector.y /= length;
	return a_StartVector;
}
