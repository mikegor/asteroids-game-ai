#include "AiGame.h"

AiGame::AiGame() : population(0, nullptr, 0)
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowX, this->windowY), "Asteroids");
	population = Population(50, window, 10);
}

void AiGame::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		this->update();
	}
}

void AiGame::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
	}
}

void AiGame::update()
{
	this->window->clear();
	if(!population.areAllDead())
		population.updateAlive();
	else {
		population.calculateFitness();
		population.naturalSelection();
	}
	window->display();
}
