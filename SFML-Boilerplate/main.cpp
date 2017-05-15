#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "noise\noise.h"
#include <string>
#include <iostream>
#include "VehicleSystem.h"

int main();
void drawUI(sf::RenderWindow *window);

//functions;
void update();

//Variables
sf::RenderWindow *window;
sf::Clock gameTime;
sf::Font font;
VehicleSystem vSystem;
sf::Vector2i windowSize(1440, 960);
sf::CircleShape targetShape;

//Main
int main()
{	
	using namespace std;

	int a = 0;
	int*b = &a;
	vSystem = VehicleSystem();
	targetShape = sf::CircleShape(10);
	targetShape.setFillColor(sf::Color::Red);
	targetShape.setPosition(200, 200);
	cout << "A: " << a << " B: " << b << endl;

	window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Terrain");
	if (!font.loadFromFile("pixeled.ttf"))
	{

	}
	update();

	return 0;
}

//Update
void update()
{
	while (window->isOpen())
	{
		sf::Time elapsed = gameTime.restart();
		std::cout << elapsed.asSeconds() << std::endl;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		//Start or stop mutation.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			vSystem.target = sf::Mouse::getPosition(*window);
			targetShape.setPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Equal))
		{
			vSystem.IncreaseVehicles(rand() % (windowSize.x - 200) + 200, rand() % (windowSize.y - 200) + 200);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Dash))
		{
			vSystem.DecreaseVehicles();
		}

		//ALIGNMENT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			vSystem.hasAlignment = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			vSystem.hasAlignment = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			vSystem.IncreaseAlignment();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			vSystem.DecreaseAlignment();
		}
		//COHESION
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			vSystem.hasCohesion = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			vSystem.hasCohesion = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			vSystem.IncreaseCohesion();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			vSystem.DecreaseCohesion();
		}

		//SEPARATION
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			vSystem.hasSeparation = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		{
			vSystem.hasSeparation = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
		{
			vSystem.IncreaseSeparation();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		{
			vSystem.DecreaseSeparation();
		}

		//RADIUS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
		{
			vSystem.DecreaseNeighborhood();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
		{
			vSystem.IncreaseNeighborhood();
		}

		window->clear();
		vSystem.Update(elapsed);
		vSystem.Draw(window);
		drawUI(window);
		window->draw(targetShape);
		window->display();
	}
}


void drawUI(sf::RenderWindow *window)
{
	
	using namespace std;
	sf::Text label;
	string text;
	text = std::to_string(vSystem.vehicles.size());
	text += " Number of Boids\n[-] - Decrease | [+] - Increase \n\n";
	text += vSystem.hasAlignment? "ACTIVE" : "INACTIVE";
	text += " Aligment: ";
	text += std::to_string(vSystem.aligmentScale);
	text += "\n[Q] - Deactivate | [W] - Activate | [E] - Decrease | [R] - Increase \n\n";
	text += vSystem.hasCohesion ? "ACTIVE" : "INACTIVE";
	text += " Cohesion: ";
	text += std::to_string(vSystem.cohesionScale);
	text += "\n[A] - Deactivate | [S] - Activate | [D] - Decrease | [F] - Increase \n\n";
	text += vSystem.hasSeparation ? "ACTIVE" : "INACTIVE";
	text += " Separation: ";
	text += std::to_string(vSystem.separationScale);
	text += "\n[Z] - Deactivate | [X] - Activate | [C] - Decrease | [V] - Increase \n\n";
	text += " Neighbor Radius: ";
	text += std::to_string(vSystem.neighborhoodRadius);
	text += "\n[T] - Decrease | [Y] - Increase | \n\n";

	label.setString(text);
	label.setCharacterSize(16);
	label.setFont(font);
	label.setFillColor(sf::Color::White);
	label.setPosition(windowSize.x - 650, 24);

	window->draw(label);
}