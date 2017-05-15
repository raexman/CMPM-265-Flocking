#include "VehicleSystem.h"



VehicleSystem::VehicleSystem()
{
	target = sf::Vector2i(200, 200);
	vehicles = { Vehicle(0,0) };
}


VehicleSystem::~VehicleSystem()
{
}

void VehicleSystem::IncreaseVehicles(float x, float y)
{
	vehicles.push_back(Vehicle(x,y));
}

void VehicleSystem::DecreaseVehicles()
{
	if(vehicles.size() > 2)
		vehicles.pop_back();
}

void VehicleSystem::ResetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle

}

void VehicleSystem::Update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < vehicles.size(); i++)
	{
		Vehicle &v = vehicles[i];
		
		GetSeeking(v, (sf::Vector2f) target);
		GetAligment(v, i);

		if (isSeeking) {
			v.ApplyForce(v.seeking * seekScale);
		}
		if (hasAlignment){
			v.ApplyForce(v.alignment * aligmentScale);
		}
		
		if (hasCohesion){
			v.ApplyForce(v.cohesion * cohesionScale);
		}

		if (hasSeparation) {
			v.ApplyForce(v.separation * separationScale);
		}

		for (std::size_t j = 0; j < vehicles.size(); j++){
		}

		v.Update(elapsed);
	}
}

void VehicleSystem::Draw(sf::RenderWindow *window)
{
	for (std::size_t i = 0; i < vehicles.size(); i++)
	{
		Vehicle &v = vehicles[i];
		window->draw(v.body);
	}

}

sf::Vector2f VehicleSystem::GetSeeking(Vehicle &v, sf::Vector2f target)
{
	sf::Vector2f desired = target - v.location;
	float desiredDist = VectorUtils::GetMagnitude(desired);
	desired = VectorUtils::NormalizeVector(desired);
	float speedFactor = (desiredDist / desiredRange) * v.maxSpeed;
	/*if (desiredDist < desiredRange)
	{
		desired *= speedFactor;
	}
	else
	{
		desired *= v.maxSpeed;
	}
	std::cout << "Mag: " << desiredDist << " | SpeedFactor: " << speedFactor << " | Desired: " << desired.x << ", " << desired.y << std::endl;
	*/
	sf::Vector2f steer = desired - v.velocity;
	steer = VectorUtils::LimitVector(steer, v.maxForce);
	v.seeking = steer;

	return steer;
}

sf::Vector2f VehicleSystem::GetAligment(Vehicle & v, std::size_t index)
{
	sf::Vector2f aligmentVector(0, 0);
	sf::Vector2f cohesionVector(0, 0);
	sf::Vector2f separationVector(0, 0);

	int neighbors = 0;

	for (std::size_t i = 0; i < vehicles.size(); i++)
	{
		if (index != i)
		{
			if (VectorUtils::GetDistance(vehicles[i].location, v.location) < neighborhoodRadius)
			{
				aligmentVector.x += vehicles[i].velocity.x;
				aligmentVector.y += vehicles[i].velocity.y;
				cohesionVector.x += vehicles[i].location.x;
				cohesionVector.y += vehicles[i].location.y;
				separationVector.x += vehicles[i].location.x - v.location.x;
				separationVector.y += vehicles[i].location.y - v.location.y;

				neighbors++;
			}
		}
	}

	if (neighbors == 0)
	{
		v.alignment = sf::Vector2f(0,0);
		v.cohesion = sf::Vector2f(0, 0);
		v.separation = sf::Vector2f(0, 0);
		return aligmentVector;
	}

	//Average Direction.
	aligmentVector.x /= neighbors;
	aligmentVector.y /= neighbors;
	aligmentVector = VectorUtils::NormalizeVector(aligmentVector);

	//Average Position.
	cohesionVector.x /= neighbors;
	cohesionVector.y /= neighbors;
	cohesionVector.x -= v.location.x;
	cohesionVector.y -= v.location.y;
	cohesionVector = VectorUtils::NormalizeVector(cohesionVector);

	//Average Distance.
	separationVector.x *= -1;
	separationVector.y *= -1;

	v.alignment = aligmentVector;
	v.cohesion = cohesionVector;
	v.separation = separationVector;

	return aligmentVector;
}

sf::Vector2f VehicleSystem::GetCohesion(Vehicle & v, std::size_t index)
{
	return sf::Vector2f();
}

sf::Vector2f VehicleSystem::GetSeparation(Vehicle & v, std::size_t index)
{
	return sf::Vector2f();
}

void VehicleSystem::GetArrive(Vehicle & v, sf::Vector2f target)
{
	sf::Vector2f desired = target - v.location;
}


void VehicleSystem::IncreaseAlignment()
{
	aligmentScale += aligmentRate;
}

void VehicleSystem::IncreaseSeparation()
{
	separationScale += separationRate;
}

void VehicleSystem::IncreaseCohesion()
{
	cohesionScale += cohesionRate;
}

void VehicleSystem::DecreaseAlignment()
{
	aligmentScale -= aligmentRate;
	if (aligmentScale < 0)
		aligmentScale = 0;
}

void VehicleSystem::DecreaseSeparation()
{
	separationScale -= separationRate;
	if (separationScale < 0)
		separationScale = 0;
}

void VehicleSystem::DecreaseCohesion()
{
	cohesionScale -= cohesionRate;
	if (cohesionScale < 0)
		cohesionScale = 0;
}

void VehicleSystem::IncreaseNeighborhood()
{
	neighborhoodRadius += neighborhoodRate;
}

void VehicleSystem::DecreaseNeighborhood()
{
	neighborhoodRadius -= neighborhoodRate;
	if (neighborhoodRadius < 0)
		neighborhoodRadius = 0;
}

