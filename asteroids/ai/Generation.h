#pragma once

#include<vector>
#include<memory>

#include"Player.h"
#include"Asteroid.h"
#include"Bullet.h"
#include"Collisions.h"
#include"Random.h"

class Generation {
	std::shared_ptr<sf::RenderWindow> window = nullptr;

	std::shared_ptr<std::vector<std::shared_ptr<Asteroid>>> asteroids =  std::make_shared<std::vector<std::shared_ptr<Asteroid>>>();
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> bullets = std::make_shared<std::vector<std::shared_ptr<Bullet>>>();
	std::shared_ptr<Player> player;

	std::shared_ptr<Collisions> collisions;
	Random random = Random(2, 2);

	int asteroidTimer = 200;

	int windowX = 1280;
	int windowY = 720;

	bool playerDead = false;

	//AI properties
	std::shared_ptr<NeuralNet> ai;
	std::vector<float> input;
	std::vector<float> output;

	float fitness;
	float mutationRate = 0.2;

	int shotsFired = 1;
	int shotsHit = 1;

	int lifeSpan = 0;

	int score = 0;
	
	void initWindow(std::shared_ptr<sf::RenderWindow> window);
	void initAsteroids(int asteroidsAmount);
	void initPlayer();

	void spawnAsteroid();

public:
	Generation() {};
	Generation(std::shared_ptr<sf::RenderWindow> window, int asteroidsAmount);

	void updateAsteroids();
	void updateBullets();
	void updatePlayer();
	void updatePlayerAction();
	void updateTimers();
	void update();

	bool isPlayerDead();

	void calculateFitness();
	float getFitness();
	void mutate();
	std::shared_ptr<Generation> clone(int asteroidsAmount);
	std::shared_ptr<Generation> crossover(std::shared_ptr<Generation> pair, int asteroidsAmount);

	void scan();
	float scanDir(float dir, sf::Vector2f position);
	void actualizeOutput();

	void render();
};