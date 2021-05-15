#pragma once

#include<SFML/Graphics.hpp>

#include"Population.h"

class AiGame {
public:
	sf::RenderWindow* window;

	int windowX = 1280;
	int windowY = 720;

	Population population;

	AiGame();

	void run();
	void updatePollEvents();

	void update();
};