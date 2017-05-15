#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include "VectorUtils.h"
#include "Vehicle.h"

class VehicleSystem : public sf::Transformable
{
public:
	//Properties.
	std::vector<Vehicle> vehicles;
	sf::Vector2i target;
	float neighborhoodRadius = 80;
	float neighborhoodRate = 0.01f;

	//Flags.
	bool isSeeking = true;
	bool hasAlignment = true;
	bool hasCohesion = true;
	bool hasSeparation = true;

	//Forces.
	float desiredRange = 100;
	float seekScale = 1.0f;
	float aligmentScale = 0.25f;
	float cohesionScale = 0.25f;
	float separationScale = 0.25f;

	//Rates
	float seekRate = 0.001f;
	float aligmentRate = 0.001f;
	float cohesionRate = 0.001f;
	float separationRate = 0.001f;

	//Functions.
	VehicleSystem();
	~VehicleSystem();
	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow *window);
	void IncreaseVehicles(float x, float y);
	void DecreaseVehicles();

	//Vector utilities.
	

	//Force functions;
	sf::Vector2f GetSeeking(Vehicle &v, sf::Vector2f target);
	sf::Vector2f GetAligment(Vehicle &v, std::size_t index);
	sf::Vector2f GetCohesion(Vehicle &v, std::size_t index);
	sf::Vector2f GetSeparation(Vehicle &v, std::size_t index);
	void GetArrive(Vehicle &v, sf::Vector2f target);
	void IncreaseAlignment();
	void IncreaseSeparation();
	void IncreaseCohesion();
	void DecreaseAlignment();
	void DecreaseSeparation();
	void DecreaseCohesion();
	void IncreaseNeighborhood();
	void DecreaseNeighborhood();

private:
	int size;
	void ResetParticle(std::size_t index);
};

