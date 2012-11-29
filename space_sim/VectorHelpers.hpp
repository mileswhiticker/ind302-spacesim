#ifndef VECTOR_HELPERS_HPP
#define VECTOR_HELPERS_HPP

#include <SFML\System\Vector2.hpp>

float SquaredLength(sf::Vector2f a_Vector);
float Length(sf::Vector2f a_Vector);
float Distance(sf::Vector2f a_VectorOne, sf::Vector2f a_VectorTwo);
float SquaredDistance(sf::Vector2f a_VectorOne, sf::Vector2f a_VectorTwo);
void Normalise(sf::Vector2f& a_StartVector);
sf::Vector2f NormaliseCopy(sf::Vector2f a_StartVector);

#endif	//VECTOR_HELPERS_HPP