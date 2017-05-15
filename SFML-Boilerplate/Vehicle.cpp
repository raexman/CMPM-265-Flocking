#include "Vehicle.h"



Vehicle::Vehicle(float x, float y, float speed)
{
	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	location = sf::Vector2f(x, y);
	body = sf::CircleShape(radius, 3);
	body.setOrigin(radius,radius);
	body.setPosition(location);
	body.setScale(0.5f, 1);
	maxSpeed = speed;
}

void Vehicle::Update(sf::Time elapsed)
{
	velocity += acceleration;
	velocity = VectorUtils::LimitVector(velocity, maxSpeed);
	velocity.x *= elapsed.asSeconds() * 100;
	velocity.y *= elapsed.asSeconds() * 100;
	location += velocity;
	acceleration = sf::Vector2f(0,0);
	body.setPosition(location);
	body.setRotation(((atan2f(velocity.y, velocity.x) * 180.0) / 3.14159265) + 90);
	//std::cout << velocity.x << " | " << velocity.y << std::endl;
}

void Vehicle::ApplyForce(sf::Vector2f force)
{
	acceleration += force;
}

Vehicle::~Vehicle()
{
}

void Vehicle::AddVelocity(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}


