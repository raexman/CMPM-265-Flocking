#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define PI 3.14159265

class VectorUtils
{
public:
	static sf::Vector2f LimitVector(sf::Vector2f v, float limit);
	static sf::Vector2f NormalizeVector(sf::Vector2f v);
	static float GetDistance(sf::Vector2f v1, sf::Vector2f v2);
	static float GetMagnitude(sf::Vector2f v);
	VectorUtils();
	~VectorUtils();
};

