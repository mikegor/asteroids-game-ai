#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<memory>

#include"Asteroid.h"
#include"Player.h"
#include"Bullet.h"
#include"Helpers.h"
#include"Collisions.h"
#include"Random.h"

#include<windows.h>


class Game
{
private:
	sf::RenderWindow* window;
	std::shared_ptr<std::vector<std::shared_ptr<Asteroid>>> asteroids = std::make_shared<std::vector<std::shared_ptr<Asteroid>>>();
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> bullets = std::make_shared<std::vector<std::shared_ptr<Bullet>>>();

	std::shared_ptr<Player> player;

	Collisions collisions;
	Random random = Random(2, 2);

	int points = 0;
	int asteroidTimer=0;

	int windowX = 1280;
	int windowY = 720;

	void initWindow();
	void initAsteroids();
	void initPlayer();

	void spawnAsteroid();

public:
	Game();
	~Game();

	void run();

	void updatePollEvents();
	void updateInput();
	void updateAsteroids();
	void updateBullets();
	void updatePlayer();
	void update();

	void render();
};