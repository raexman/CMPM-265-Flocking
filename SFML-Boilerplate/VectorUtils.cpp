#include "VectorUtils.h"



VectorUtils::VectorUtils()
{
}


VectorUtils::~VectorUtils()
{
}
sf::Vector2f VectorUtils::LimitVector(sf::Vector2f v, float limit)
{
	float magnitude = sqrtf(v.x*v.x + v.y*v.y);
	sf::Vector2f limited(0, 0);

	if (magnitude != 0)
	{
		limited = sf::Vector2f((limit * v.x) / magnitude, (limit * v.y) / magnitude);
	}
	//std::cout << limited.x << " | " << limited.y << std::endl;

	return limited;
}

sf::Vector2f VectorUtils::NormalizeVector(sf::Vector2f v)
{
	
	return v / GetMagnitude(v);
}

float VectorUtils::GetDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	sf::Vector2f vr(0, 0);
	vr.x = v1.x - v2.x;
	vr.y = v1.y - v2.y;
	
	float distance = sqrtf(vr.x*vr.x + vr.y*vr.y);

	return distance;
}

float VectorUtils::GetMagnitude(sf::Vector2f v)
{
	float magnitude = sqrtf(v.x * v.x + v.y * v.y);

	return magnitude;
}