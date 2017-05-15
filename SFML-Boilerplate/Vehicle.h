#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "noise\noise.h"
#include "VectorUtils.h"

class Vehicle : public sf::Transformable
{
public:
	//Properties.
	sf::CircleShape body;
	sf::Vector2f location;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float radius = 15;
	float maxSpeed = 1;
	float maxForce = 1;

	sf::Vector2f seeking;
	sf::Vector2f alignment;
	sf::Vector2f cohesion;
	sf::Vector2f separation;

	//Functions
	Vehicle() {};
	Vehicle(float x, float y, float speed = 1);
	~Vehicle();
	void AddVelocity(float x, float y);
	void Update(sf::Time elapsed);
	void ApplyForce(sf::Vector2f force);

private:
	//Vars

	//Functions
};