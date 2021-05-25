#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

#include"Generation.h"
#include"StaticRandom.h"

class Population {
public:
	std::shared_ptr<std::vector<std::shared_ptr<Generation>>> generations;
	int bestGenerationNo = 0;
	int bestScore = 0;
	bool allDead = false;
	int asteroidsAmount;
	int genCounter = 0;

	Population(int size, std::shared_ptr<sf::RenderWindow> window, int asteroidsAmount);

	void updateAlive();
	void naturalSelection();
	int getRandomGenByFitness();

	void calculateFitness();

	bool areAllDead();
};